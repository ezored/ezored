"""Distribute target package"""

import os
import sys
import threading

from files.modules import const
from files.modules import log
from files.modules import pack
from files.modules import util
from files.modules import aws
from files.config import target_windows_app as config


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]

    if len(args) > 1:
        action = args[1]

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
    proj_path = params["proj_path"]
    target_name = params["target_name"]

    build_dir = os.path.join(
        proj_path, const.DIR_NAME_BUILD, target_name, const.DIR_NAME_DIST
    )

    version = util.get_arg_value("--version", params["args"])
    dist_file_path = os.path.join(build_dir, const.FILE_NAME_DIST_PACKED)
    dist_file_name = const.FILE_NAME_DIST_PACKED
    dist_folder = target_name
    aws_s3_url = "{0}/{1}".format(const.AWS_S3_URL, target_name)

    aws.download(
        proj_path=proj_path,
        version=version,
        dist_file_path=dist_file_path,
        dist_file_name=dist_file_name,
        dist_folder=dist_folder,
        aws_s3_url=aws_s3_url,
    )


# -----------------------------------------------------------------------------
def upload(params):
    proj_path = params["proj_path"]
    target_name = params["target_name"]

    build_dir = os.path.join(
        proj_path, const.DIR_NAME_BUILD, target_name, const.DIR_NAME_DIST
    )

    version = util.get_arg_value("--version", params["args"])
    force = util.list_has_key(params["args"], "--force")
    dist_file_path = os.path.join(build_dir, const.FILE_NAME_DIST_PACKED)
    dist_file_name = const.FILE_NAME_DIST_PACKED
    dist_folder = target_name
    aws_key_id = os.getenv(const.AWS_KEY_ID_ENV)
    aws_secret_key = os.getenv(const.AWS_SECRET_KEY_ENV)
    aws_bucket_name = const.AWS_S3_BUCKET_NAME
    aws_bucket_path = "{0}/{1}".format(const.AWS_S3_BUCKET_PATH, target_name)

    aws.upload(
        proj_path=proj_path,
        version=version,
        force=force,
        dist_file_path=dist_file_path,
        dist_file_name=dist_file_name,
        dist_folder=dist_folder,
        aws_key_id=aws_key_id,
        aws_secret_key=aws_secret_key,
        aws_bucket_name=aws_bucket_name,
        aws_bucket_path=aws_bucket_path,
    )


# -----------------------------------------------------------------------------
def generate(params):
    # prepare data
    proj_path = params["proj_path"]
    target_name = params["target_name"]

    target_config = config.run(proj_path, target_name, params)
    build_types = target_config["build_types"]

    version = util.get_arg_value("--version", params["args"])
    source_files = []

    dist_folder = os.path.join(proj_path, const.DIR_NAME_DIST, target_name)

    # add folders
    for build_type in build_types:
        source_files.append(
            {
                "path": os.path.join(dist_folder, build_type),
                "arcname": build_type,
            }
        )

    # generate
    pack.generate(
        proj_path=proj_path,
        target_name=target_name,
        version=version,
        source_files=source_files,
    )


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored("List of available verb actions:\n", log.PURPLE)
    log.normal("  - generate")
    log.normal("  - download")
    log.normal("  - upload")
