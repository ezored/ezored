"""Module: Pack"""

import os
import platform
import tarfile
import zipfile
import gzip

from files.modules import const
from files.modules import log
from files.modules import file

# -----------------------------------------------------------------------------
def unpack(src_path, dst_path, filename=""):
    dst_path = dst_path + ("" if len(filename) == 0 else "/" + filename)

    if ".zip" in src_path:
        with zipfile.open(src_path, "r") as archive:
            archive.extractall(dst_path)
            archive.close()
    elif ".tgz" or ".bz2" or ".tar.gz" or "tbz2" or ".tar.bz2" or ".tar" in src_path:
        with tarfile.open(src_path, "r:*") as archive:
            archive.extractall(dst_path)
            archive.close()
    else:
        raise Exception("File format not supported")


# -----------------------------------------------------------------------------
def zip_dir(output_filename, source_dir):
    exclude_list = ["Thumbs.db", ".DS_Store"]

    zip_out = zipfile.ZipFile(output_filename, "w", compression=zipfile.ZIP_DEFLATED)
    root_len = len(os.path.dirname(source_dir))

    def archive_directory(parent_directory):
        contents = os.listdir(parent_directory)

        if not contents:
            archive_root = parent_directory[root_len:].replace("\\", "/").lstrip("/")
            zip_info = zipfile.ZipInfo(archive_root + "/")
            zip_out.writestr(zip_info, "")

        for item in contents:
            if item in exclude_list:
                continue

            full_path = os.path.join(parent_directory, item)

            if os.path.isdir(full_path) and not os.path.islink(full_path):
                archive_directory(full_path)
            else:
                archive_root = full_path[root_len:].replace("\\", "/").lstrip("/")

                if os.path.islink(full_path):
                    zip_info = zipfile.ZipInfo(archive_root)
                    zip_info.create_system = 3
                    zip_info.external_attr = 0xA1ED0000
                    zip_out.writestr(zip_info, os.readlink(full_path))
                else:
                    zip_out.write(full_path, archive_root, zipfile.ZIP_DEFLATED)

    archive_directory(source_dir)

    zip_out.close()


# -----------------------------------------------------------------------------
def tar_dir(output_filename, source_dir):
    exclude_list = ["Thumbs.db", ".DS_Store"]

    tar_out = tarfile.open(output_filename, "w:gz")
    tar_out.add(
        source_dir,
        arcname=os.path.basename(source_dir),
        filter=lambda x: None if x.name in exclude_list else x,
    )
    tar_out.close()


# -----------------------------------------------------------------------------
def tar_files(output_filename, source_files):
    exclude_list = ["Thumbs.db", ".DS_Store"]

    tar_out = tarfile.open(output_filename, "w:gz")

    for source_file in source_files:
        tar_out.add(
            source_file["path"],
            arcname=source_file["arcname"],
            filter=lambda x: None if x.name in exclude_list else x,
        )

    tar_out.close()


# -----------------------------------------------------------------------------
def generate(proj_path, target_name, version, source_files):
    # version
    if not version or len(version) == 0:
        log.error("You need define version name (parameter: --version)")

    log.info("Version defined: {0}".format(version))

    # build dir
    build_dir = os.path.join(
        proj_path, const.DIR_NAME_BUILD, target_name, const.DIR_NAME_DIST
    )

    log.info("Removing old files...")

    file.remove_dir(build_dir)
    file.create_dir(build_dir)

    # pack files
    log.info("Packing {0} files...".format(len(source_files)))

    dist_file = os.path.join(build_dir, const.FILE_NAME_DIST_PACKED)
    tar_files(dist_file, source_files)

    log.ok("")
