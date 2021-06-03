"""Documentation manager tool"""

import os
import subprocess
import mimetypes as mime

from files.core import const
from files.core import file
from files.core import log
from files.core import runner
from files.core import util
from files.core import aws
from files.config import docs as config

import boto3


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]

    if len(args) > 0:
        action = args[0]

        if action:
            if action == "generate":
                docs_generate(params)
            elif action == "serve":
                docs_serve(params)
            elif action == "publish":
                docs_publish(params)
            else:
                show_help(params)
        else:
            show_help(params)
    else:
        show_help(params)


# -----------------------------------------------------------------------------
def docs_generate(params):
    proj_path = params["proj_path"]

    docs_name = util.get_arg_value("--name", params["args"])

    if not docs_name:
        docs_name = const.DOCS_DEFAULT_NAME

    docs_path = os.path.join(
        proj_path,
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_DOCS,
        docs_name,
    )

    output_path = os.path.join(
        proj_path,
        const.DIR_NAME_BUILD,
        const.DIR_NAME_BUILD_DOCS,
        docs_name,
    )

    has_tool = check_tool_mkdocs()

    if has_tool:
        run_args = [
            "mkdocs",
            "build",
            "--clean",
            "--config-file",
            "mkdocs.yml",
            "-d",
            output_path,
        ]
        runner.run(run_args, docs_path)


# -----------------------------------------------------------------------------
def docs_serve(params):
    proj_path = params["proj_path"]

    docs_name = util.get_arg_value("--name", params["args"])

    if not docs_name:
        docs_name = const.DOCS_DEFAULT_NAME

    docs_path = os.path.join(
        proj_path,
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_DOCS,
        docs_name,
    )

    if not os.path.isdir(docs_path):
        log.error(
            "Directory not found (check documentation name parameter): {0}".format(
                docs_path,
            ),
        )

    has_tool = check_tool_mkdocs()

    if has_tool:
        run_args = [
            "mkdocs",
            "serve",
            "--config-file",
            "mkdocs.yml",
        ]
        runner.run(run_args, docs_path)


# -----------------------------------------------------------------------------
def docs_publish(params):
    proj_path = params["proj_path"]

    docs_name = util.get_arg_value("--name", params["args"])

    if not docs_name:
        docs_name = const.DOCS_DEFAULT_NAME

    docs_path = os.path.join(
        proj_path,
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_DOCS,
        docs_name,
    )

    output_path = os.path.join(
        proj_path,
        const.DIR_NAME_BUILD,
        const.DIR_NAME_BUILD_DOCS,
        docs_name,
    )

    ignore_files = [".DS_Store", "Thumbs.db"]

    config_data = config.run(proj_path, params)
    config_data = config_data[docs_name]

    has_tool = check_tool_mkdocs()

    if has_tool:
        params["target_name"] = "docs"

        # prepare data
        version = config_data["version"] if "version" in config_data else None
        append_version = (
            config_data["append_version"] if "append_version" in config_data else None
        )
        force = util.list_has_key(params["args"], "--force")

        aws_key_id = os.getenv(const.AWS_KEY_ID_ENV)
        aws_secret_key = os.getenv(const.AWS_SECRET_KEY_ENV)
        aws_bucket_name = config_data["bucket_name"]
        aws_bucket_path = "{0}".format(config_data["bucket_path"])

        if append_version:
            aws_bucket_path = "{0}/{1}".format(aws_bucket_path, version)

        # generate files
        run_args = [
            "mkdocs",
            "build",
            "--clean",
            "--config-file",
            "mkdocs.yml",
            "-d",
            output_path,
        ]

        runner.run(run_args, docs_path)

        # version
        if append_version:
            if not version or len(version) == 0:
                log.error("You need define version name (parameter: --version)")

            log.info("Version defined: {0}".format(version))

        # prepare to upload
        if not os.path.isdir(docs_path):
            log.error("Documentation output folder not exists: {0}".format(docs_path))

        # prepare aws sdk
        log.info("Initializing AWS bucket and SDK...")

        if not aws_key_id or not aws_secret_key:
            log.fail("Your AWS credentials are invalid")

        s3_client = boto3.client(
            service_name="s3",
            aws_secret_access_key=aws_secret_key,
            aws_access_key_id=aws_key_id,
        )

        # checking for existing path
        log.info(
            'Checking if remote path "{0}" exists on AWS...'.format(
                aws_bucket_path,
            )
        )

        has_remote_path = aws.s3_dir_exists(
            s3_client,
            aws_bucket_name,
            aws_bucket_path,
        )

        if has_remote_path:
            if force:
                log.info(
                    'The path "{0}" already exists on AWS, removing...'.format(
                        aws_bucket_path
                    )
                )

                aws.s3_dir_delete(
                    s3_client,
                    aws_bucket_name,
                    aws_bucket_path,
                    aws_secret_key,
                    aws_key_id,
                )
            else:
                log.error(
                    'The path "{0}" already exists on AWS'.format(aws_bucket_path)
                )

        # create path folder
        aws.s3_create_dir(
            s3_client,
            aws_bucket_name,
            aws_bucket_path,
            aws_secret_access_key=aws_secret_key,
            aws_access_key_id=aws_key_id,
        )

        # upload
        walks = os.walk(output_path)

        for source, dirs, files in walks:
            log.info("Entering directory: {0}".format(source))

            for filename in files:
                if filename in ignore_files:
                    continue

                local_file_path = os.path.join(source, filename)
                relative_path = os.path.relpath(local_file_path, output_path)

                s3_file = os.path.join(aws_bucket_path, relative_path)

                log.info(
                    'Uploading file "{0}" to S3 bucket "{1}"...'.format(
                        relative_path, aws_bucket_name
                    )
                )

                extra_args = {}

                if os.path.isdir(local_file_path):
                    extra_args = {
                        "ACL": "public-read",
                    }
                elif os.path.isfile(local_file_path):
                    mime_type = mime.guess_type(local_file_path)

                    extra_args = {
                        "ACL": "public-read",
                        "ContentType": (
                            mime_type[0]
                            if mime_type != None
                            and len(mime_type) > 0
                            and mime_type[0] != None
                            else ""
                        ),
                    }

                s3_client.upload_file(
                    local_file_path,
                    aws_bucket_name,
                    s3_file,
                    ExtraArgs=extra_args,
                    Callback=aws.ProgressPercentage(local_file_path),
                )

                log.normal("")

        if append_version:
            log.colored(
                "[DONE] You can access documentation here: {0}/{1}/index.html".format(
                    config_data["url"],
                    version,
                ),
                log.BLUE,
            )
        else:
            log.colored(
                "[DONE] You can access documentation here: {0}/index.html".format(
                    config_data["url"],
                ),
                log.BLUE,
            )

        log.ok("")


# -----------------------------------------------------------------------------
def check_tool_mkdocs():
    """Checks if invoking supplied mkdocs binary works."""
    try:
        subprocess.check_output(["mkdocs", "--version"])
        return True
    except OSError:
        log.info("Mkdocs is not installed, check: https://www.mkdocs.org/")
        return False


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored("Available actions:\n", log.PURPLE)
    log.normal("  - generate")
    log.normal("  - serve")
    log.normal("  - publish")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Documentation manager tool"
