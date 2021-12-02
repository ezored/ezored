"""Module: Pack"""

import os

from pygemstones.io import file as f
from pygemstones.io import pack as p
from pygemstones.util import log as l

from files.core import const


# -----------------------------------------------------------------------------
def generate(proj_path, target_name, version, source_files):
    # version
    if not version or len(version) == 0:
        l.e("You need define version name (parameter: --version)")

    l.i("Version defined: {0}".format(version))

    # build dir
    build_dir = os.path.join(
        proj_path, const.DIR_NAME_BUILD, target_name, const.DIR_NAME_DIST
    )

    l.i("Removing old files...")

    f.recreate_dir(build_dir)

    # pack files
    l.i("Packing {0} files...".format(len(source_files)))

    dist_file = os.path.join(build_dir, const.FILE_NAME_DIST_PACKED)
    p.tar_files(dist_file, source_files)

    l.ok()
