"""Module: Net"""

import os

from pygemstones.io import file as f
from pygemstones.io import net as n
from pygemstones.io import pack as pack
from pygemstones.util import log as l

from files.core import const


# -----------------------------------------------------------------------------
def download_dist_file(
    proj_path, version, dist_file_path, dist_file_name, dist_folder, dist_file_url
):
    # version
    if not version or len(version) == 0:
        l.e("You need define version name (parameter: --version)")

    l.i("Version defined: {0}".format(version))

    # remove file
    l.i("Removing old file...")
    f.remove_file(dist_file_path)

    # download file
    l.i("Downloading {0} file...".format(dist_file_name))

    file_url = "{0}/{1}/{2}".format(dist_file_url, version, dist_file_name)

    try:
        f.create_dir(os.path.dirname(dist_file_path))
        n.download(file_url, dist_file_path)
    except Exception as e:
        l.e("Error when download file {0}: {1}".format(file_url, e))

    # remove old files and unpack current file
    l.i("Removing old folder...")

    f.create_dir(os.path.join(proj_path, const.DIR_NAME_DIST))
    f.remove_dir(os.path.join(proj_path, const.DIR_NAME_DIST, dist_folder))

    l.i("Unpacking downloaded file...")

    pack.unpack(
        dist_file_path, os.path.join(proj_path, const.DIR_NAME_DIST, dist_folder)
    )

    l.ok()
