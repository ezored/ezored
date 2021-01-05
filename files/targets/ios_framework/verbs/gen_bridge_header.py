"""Generate bridging header"""

import os

from files.modules import const
from files.modules import file
from files.modules import log
from files.config import target_ios_framework as config


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params["proj_path"]
    target_name = params["target_name"]
    target_config = config.run(proj_path, target_name, params)

    archs = target_config["archs"]
    build_types = target_config["build_types"]

    log.info("Generating bridging header...")

    if archs and len(archs) > 0:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                log.info("Generating for: {0}...".format(build_type))

                build_headers_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    archs[0]["group"],
                    archs[0]["conan_arch"],
                    "target",
                    "lib",
                    "{0}.framework".format(target_config["project_name"]),
                    "Headers",
                )

                header_files = file.find_files(build_headers_dir, "*.h")

                bridge_file = os.path.join(
                    proj_path,
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    "Bridging-Header.h",
                )

                content = ""

                for header_file in header_files:
                    header_file = header_file.replace(build_headers_dir + "/", "")

                    content = content + '#include "{0}"\n'.format(header_file)

                if len(content) > 0:
                    file.remove_file(bridge_file)

                    file.write_to_file(
                        os.path.join(
                            proj_path, const.DIR_NAME_DIST, target_name, build_type
                        ),
                        "Bridging-Header.h",
                        content,
                    )
                else:
                    log.error(
                        "{0}".format(
                            "File not generated because framework headers is empty"
                        )
                    )
        else:
            log.info(
                'Build type list for "{0}" is invalid or empty'.format(target_name)
            )
    else:
        log.info('Arch list for "{0}" is invalid or empty'.format(target_name))
