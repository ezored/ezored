"""Install and build conan dependencies"""

import os

import ezored.app.const as const
from ezored.modules import file
from ezored.modules import log
from ezored.modules import runner
from files.config import target_windows_app as config


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params['proj_path']
    target_name = params['target_name']
    target_config = config.run(proj_path, target_name, params)

    archs = target_config['archs']
    build_types = target_config['build_types']

    if archs and len(archs) > 0:
        for arch in archs:
            for build_type in build_types:
                log.info('Building for: {0}/{1}...'.format(
                    arch['conan_arch'],
                    build_type
                ))

                # conan install
                build_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    arch['conan_arch'],
                    const.DIR_NAME_BUILD_CONAN,
                )

                file.remove_dir(build_dir)
                file.create_dir(build_dir)

                run_args = [
                    'conan',
                    'install',
                    os.path.join(
                        proj_path,
                        const.DIR_NAME_FILES,
                        const.DIR_NAME_FILES_TARGETS,
                        target_name,
                        const.DIR_NAME_FILES_TARGET_CONAN,
                        const.DIR_NAME_FILES_TARGET_CONAN_RECIPE,
                        const.FILE_NAME_FILES_TARGET_CONAN_RECIPE_CONANFILE_PY,
                    ),
                    '--profile',
                    arch['conan_profile'],
                    '-s',
                    'arch={0}'.format(arch['conan_arch']),
                    '-s',
                    'build_type={0}'.format(build_type),
                    '--build=missing',
                    '--update',
                ]

                runner.run(
                    run_args,
                    build_dir
                )
    else:
        log.error('Arch list for "{0}" is invalid or empty'.format(
            target_name
        ))
