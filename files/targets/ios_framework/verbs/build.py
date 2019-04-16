"""Build library"""

import os

import ezored.app.const as const
from ezored.modules import file, runner
from ezored.modules import log
from ezored.modules import util
from files.config import target_ios_framework as config


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params['proj_path']
    target_name = params['target_name']
    target_config = config.run(proj_path, target_name, params)

    archs = target_config['archs']
    build_types = target_config['build_types']
    install_headers = target_config['install_headers']
    param_dry_run = util.list_has_key(params['args'], '--dry-run')

    if param_dry_run:
        log.info("Running in dry mode...")

    if archs and len(archs) > 0:
        for arch in archs:
            for build_type in build_types:
                log.info('Building for: {0}/{1}...'.format(
                    arch['conan_arch'],
                    build_type
                ))

                # conan build
                build_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    arch['conan_arch'],
                    const.DIR_NAME_BUILD_TARGET,
                )

                clean_build_dir = True

                if param_dry_run and os.path.isdir(build_dir):
                    clean_build_dir = False

                if clean_build_dir:
                    file.remove_dir(build_dir)
                    file.create_dir(build_dir)

                run_args = [
                    'conan',
                    'build',
                    os.path.join(
                        proj_path,
                        const.DIR_NAME_FILES,
                        const.DIR_NAME_FILES_TARGETS,
                        target_name,
                        const.DIR_NAME_FILES_TARGET_CONAN,
                        const.DIR_NAME_FILES_TARGET_CONAN_RECIPE,
                        const.FILE_NAME_FILES_TARGET_CONAN_RECIPE_CONANFILE_PY,
                    ),
                    '--source-folder',
                    os.path.join(
                        proj_path,
                        const.DIR_NAME_FILES,
                        const.DIR_NAME_FILES_TARGETS,
                        target_name,
                        const.DIR_NAME_FILES_TARGET_CMAKE,
                    ),
                    '--build-folder',
                    os.path.join(
                        proj_path,
                        const.DIR_NAME_BUILD,
                        target_name,
                        build_type,
                        arch['conan_arch'],
                        const.DIR_NAME_BUILD_TARGET,
                    ),
                    '--install-folder',
                    os.path.join(
                        proj_path,
                        const.DIR_NAME_BUILD,
                        target_name,
                        build_type,
                        arch['conan_arch'],
                        const.DIR_NAME_BUILD_CONAN,
                    ),
                ]

                runner.run(
                    run_args,
                    build_dir
                )

                # headers
                dist_headers_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    archs[0]['conan_arch'],
                    const.DIR_NAME_BUILD_TARGET,
                    'lib',
                    '{0}.framework'.format(target_config['project_name']),
                    'Headers',
                )

                file.create_dir(dist_headers_dir)

                if install_headers:
                    for header in install_headers:
                        source_header_dir = os.path.join(
                            proj_path,
                            header['path'],
                        )

                        if header['type'] == 'dir':
                            file.copy_dir(
                                source_header_dir,
                                dist_headers_dir,
                                ignore_file=_header_ignore_list
                            )
                        else:
                            log.error('Invalid type for install header list for {0}'.format(
                                target_name
                            ))

    else:
        log.error('Arch list for "{0}" is invalid or empty'.format(
            target_name
        ))


# -----------------------------------------------------------------------------
def _header_ignore_list(filename):
    return not filename.lower().endswith('.h')
