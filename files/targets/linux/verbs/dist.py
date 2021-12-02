"""Distribute target package"""

import os

from pygemstones.type import list as ls
from pygemstones.util import log as l
from pygemstones.vendor import aws as a

from files.config import target_linux as config
from files.core import const, net, pack, util


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

    version = util.get_version(params, config)
    dist_file_path = os.path.join(build_dir, const.FILE_NAME_DIST_PACKED)
    dist_file_name = const.FILE_NAME_DIST_PACKED
    dist_folder = target_name
    aws_s3_url = "{0}/{1}".format(const.AWS_S3_URL, target_name)

    net.download_dist_file(
        proj_path=proj_path,
        version=version,
        dist_file_path=dist_file_path,
        dist_file_name=dist_file_name,
        dist_folder=dist_folder,
        dist_file_url=aws_s3_url,
    )


# -----------------------------------------------------------------------------
def upload(params):
    proj_path = params["proj_path"]
    target_name = params["target_name"]

    build_dir = os.path.join(
        proj_path, const.DIR_NAME_BUILD, target_name, const.DIR_NAME_DIST
    )

    version = util.get_version(params, config)
    force = ls.list_has_value(params["args"], "--force")
    dist_file_path = os.path.join(build_dir, const.FILE_NAME_DIST_PACKED)
    aws_key_id = os.getenv(const.AWS_KEY_ID_ENV)
    aws_secret_key = os.getenv(const.AWS_SECRET_KEY_ENV)
    aws_bucket_name = const.AWS_S3_BUCKET_NAME
    aws_bucket_path = "{0}/{1}/{2}/{3}".format(
        const.AWS_S3_BUCKET_PATH, target_name, version, const.FILE_NAME_DIST_PACKED
    )

    a.s3_upload(
        file_path=dist_file_path,
        force=force,
        aws_bucket_name=aws_bucket_name,
        aws_bucket_key=aws_bucket_path,
        aws_key_id=aws_key_id,
        aws_secret_key=aws_secret_key,
    )


# -----------------------------------------------------------------------------
def generate(params):
    # prepare data
    proj_path = params["proj_path"]
    target_name = params["target_name"]

    target_config = config.run(proj_path, target_name, params)
    build_types = target_config["build_types"]

    version = util.get_version(params, config)
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
    l.colored("List of available verb actions:\n", l.MAGENTA)
    l.m("  - generate")
    l.m("  - download")
    l.m("  - upload")
