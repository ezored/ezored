"""Create final executable"""

import os

import ezored.constants as const
import ezored.functions as fn
import ezored.logging as log


# -----------------------------------------------------------------------------
def run(params={}):
    target_name = params['target_name']
    target_config = fn.get_target_config(target_name)

    archs = target_config['archs']
    build_types = target_config['build_types']

    log.info('Packaging...')

    if archs and len(archs) > 0:
        for arch in archs:
            for build_type in build_types:
                log.info('Copying for: {0}/{1}...'.format(
                    arch['conan_arch'],
                    build_type
                ))

                # create folders
                dist_dir = os.path.join(
                    fn.root_dir(),
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    arch['conan_arch'],
                )

                fn.remove_dir(dist_dir)
                fn.create_dir(dist_dir)

                build_dir = os.path.join(
                    fn.root_dir(),
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    arch['conan_arch'],
                    const.DIR_NAME_BUILD_TARGET,
                    'bin',
                )

                # copy files
                fn.copy_all_inside(build_dir, dist_dir)
    else:
        log.error('Arch list for "{0}" is invalid or empty'.format(
            target_name
        ))
