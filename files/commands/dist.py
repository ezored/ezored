"""Distribution files manager tool"""

import os
import sys
import threading

from files.modules import const
from files.modules import file
from files.modules import log
from files.modules import net
from files.modules import pack
from files.modules import util


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]

    if len(args) > 0:
        action = args[0]

        if action:
            if action == "generate":
                generate(params)
            elif action == "download":
                download(params)
            elif action == "upload":
                upload(params)
            else:
                show_help(params)
        else:
            show_help(params)
    else:
        show_help(params)


# -----------------------------------------------------------------------------
def download(params):
    # version
    sdk_version = util.get_arg_value("--version", params["args"])

    if not sdk_version or len(sdk_version) == 0:
        log.error("You need define version name (parameter: --version)")

    # remove file
    proj_path = params["proj_path"]

    log.info("Removing old file...")
    file.remove_file(const.FILE_NAME_DIST_PACKED)

    # download file
    log.info("Downloading {0} file...".format(const.FILE_NAME_DIST_PACKED))
    dst_file = os.path.join(proj_path, const.FILE_NAME_DIST_PACKED)
    net.download(
        "{0}/{1}/{2}".format(
            const.AWS_S3_URL,
            sdk_version,
            const.FILE_NAME_DIST_PACKED,
        ),
        dst_file,
    )

    # remove old files and unpack current file
    log.info("Removing old folder...")
    file.remove_dir(os.path.join(proj_path, const.DIR_NAME_DIST))

    log.info("Unpacking downloaded file...")
    pack.unpack(dst_file, proj_path)

    log.ok("")


# -----------------------------------------------------------------------------
def upload(params):
    import boto3

    # version
    sdk_version = util.get_arg_value("--version", params["args"])

    if not sdk_version or len(sdk_version) == 0:
        log.error("You need define version name (parameter: --version)")

    # prepare to upload
    proj_path = params["proj_path"]

    dist_file = os.path.join(proj_path, const.FILE_NAME_DIST_PACKED)

    if not os.path.isfile(dist_file):
        log.error("Distribution file not exists: {0}".format(dist_file))

    # prepare aws sdk
    log.info("Initializing AWS bucket and SDK...")

    aws_key = os.getenv(const.ENV_AWS_S3_KEY)
    aws_secret_key = os.getenv(const.ENV_AWS_S3_SECRET)

    if not aws_key or not aws_secret_key:
        log.fail(
            "Your AWS credentials are invalid ({0} and {1}})".format(
                const.AWS_S3_KEY_ENV,
                const.AWS_S3_SECRET_ENV,
            )
        )

    bucket_name = const.AWS_S3_BUCKET_NAME

    s3_client = boto3.client(
        service_name="s3",
        aws_secret_access_key=aws_secret_key,
        aws_access_key_id=aws_key,
    )

    # checking for existing version
    log.info("Checking if version exists...")

    object_name = "{0}/{1}/{2}".format(
        const.AWS_S3_BUCKET_PATH,
        sdk_version,
        const.FILE_NAME_DIST_PACKED,
    )

    has_version = s3_key_exists(s3_client, bucket_name, object_name)

    if has_version:
        log.error("The version {0} already exists".format(sdk_version))

    # upload
    log.info(
        'Uploading file "{0}" to S3 bucket "{1}"...'.format(dist_file, bucket_name)
    )

    s3_client.upload_file(
        dist_file,
        bucket_name,
        object_name,
        ExtraArgs={"ACL": "public-read"},
        Callback=ProgressPercentage(dist_file),
    )

    log.normal("")
    log.ok("")


# -----------------------------------------------------------------------------
def generate(params):
    proj_path = params["proj_path"]

    dist_file = os.path.join(proj_path, const.FILE_NAME_DIST_PACKED)
    dist_folder = os.path.join(proj_path, const.DIR_NAME_DIST)

    if not os.path.isdir(dist_folder):
        log.error("Distribution folder not exists: {0}".format(dist_folder))

    log.info("Removing old file...")
    file.remove_file(const.FILE_NAME_DIST_PACKED)

    log.info("Packing {0} folder...".format(const.DIR_NAME_DIST))
    pack.tar_dir(dist_file, dist_folder)

    log.ok("")


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored("Available actions:\n", log.PURPLE)
    log.normal("  - generate")
    log.normal("  - download")
    log.normal("  - upload")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Distribution files manager tool"


# -----------------------------------------------------------------------------
def s3_key_exists(s3, bucket, key):
    from botocore.exceptions import ClientError

    try:
        s3.head_object(Bucket=bucket, Key=key)
    except ClientError as e:
        error_code = int(e.response["Error"]["Code"])

        if error_code >= 400 and error_code <= 499:
            return False

    return True


# -----------------------------------------------------------------------------
class ProgressPercentage(object):
    def __init__(self, filename):
        self._filename = filename
        self._size = float(os.path.getsize(filename))
        self._seen_so_far = 0
        self._lock = threading.Lock()

    def __call__(self, bytes_amount):
        with self._lock:
            self._seen_so_far += bytes_amount
            percentage = (self._seen_so_far / self._size) * 100
            sys.stdout.write(
                "\r%s  %s / %d  (%.2f%%)"
                % (self._filename, self._seen_so_far, self._size, percentage)
            )
            sys.stdout.flush()
