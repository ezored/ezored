"""Create AAR library"""

import os

import ezored.constants as const
from ezored.mod import file
from ezored.mod import log
from ezored.mod import runner
from ezored.mod import target


# -----------------------------------------------------------------------------
def run(params={}):
    target_name = params['target_name']
    target_config = target.get_target_config(target_name)

    archs = target_config['archs']
    build_types = target_config['build_types']
    module_name = 'library'

    log.info('Creating AAR library...')

    if archs and len(archs) > 0:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                log.info('Creating AAR library for: {0}...'.format(build_type))

                build_dir = os.path.join(
                    file.root_dir(),
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                )

                android_library_build_dir = os.path.join(
                    build_dir,
                    'aar',
                )

                file.remove_dir(android_library_build_dir)
                file.create_dir(android_library_build_dir)

                android_project_dir = os.path.join(
                    file.root_dir(),
                    const.DIR_NAME_FILES,
                    const.DIR_NAME_FILES_TARGETS,
                    target_name,
                    const.DIR_NAME_FILES_TARGET_SUPPORT,
                    'android-aar-project',
                )

                file.copy_dir(android_project_dir, android_library_build_dir)

                # copy djinni support lib files
                djinni_support_lib_dir = os.path.join(
                    file.root_dir(),
                    const.DIR_NAME_FILES,
                    'djinni',
                    'support-lib',
                )

                file.copy_all_inside(
                    os.path.join(djinni_support_lib_dir, 'java'),
                    os.path.join(
                        android_library_build_dir,
                        module_name,
                        'src',
                        'main',
                        'java'
                    )
                )

                # copy all modules djinni files
                modules_dir = os.path.join(
                    file.root_dir(),
                    const.DIR_NAME_FILES,
                    'djinni',
                )

                modules = file.find_dirs_simple(modules_dir, '*')

                for module in modules:
                    module_dir_name = os.path.basename(module)

                    if module_dir_name == 'support-lib':
                        continue

                    module_dir = os.path.join(
                        modules_dir, module_dir_name, 'generated-src', 'java'
                    )

                    if file.dir_exists(module_dir):
                        file.copy_all_inside(
                            module_dir,
                            os.path.join(
                                android_library_build_dir,
                                module_name,
                                'src',
                                'main',
                                'java'
                            )
                        )

                # copy all modules implementation files
                modules_dir = os.path.join(
                    file.root_dir(),
                    const.DIR_NAME_FILES,
                    const.DIR_NAME_FILES_SRC,
                )

                modules = file.find_dirs_simple(modules_dir, '*')

                for module in modules:
                    module_dir_name = os.path.basename(module)

                    module_dir = os.path.join(
                        modules_dir, module_dir_name, 'java'
                    )

                    if file.dir_exists(module_dir):
                        file.copy_all_inside(
                            module_dir,
                            os.path.join(
                                android_library_build_dir,
                                module_name,
                                'src',
                                'main',
                                'java'
                            )
                        )

                # copy all native libraries
                for arch in archs:
                    compiled_arch_dir = os.path.join(
                        build_dir,
                        arch['conan_arch'],
                        const.DIR_NAME_BUILD_TARGET,
                        'lib',
                    )

                    target_arch_dir = os.path.join(
                        android_library_build_dir,
                        'library',
                        'src',
                        'main',
                        'jniLibs',
                        arch['arch'],
                    )

                    file.copy_all_inside(
                        compiled_arch_dir,
                        target_arch_dir,
                    )

                # build aar
                android_module_dir = os.path.join(
                    android_library_build_dir,
                    module_name,
                )

                run_args = [
                    '../gradlew',
                    'bundle{0}Aar'.format(build_type),
                ]

                runner.run(
                    run_args,
                    android_module_dir
                )

                # copy files
                arr_dir = os.path.join(
                    android_library_build_dir,
                    module_name,
                    'build',
                    'outputs',
                    'aar',
                )

                dist_dir = os.path.join(
                    file.root_dir(),
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                )

                file.remove_dir(dist_dir)

                file.copy_all_inside(
                    arr_dir,
                    dist_dir
                )
        else:
            log.info('Build type list for "{0}" is invalid or empty'.format(
                target_name
            ))
    else:
        log.info('Arch list for "{0}" is invalid or empty'.format(target_name))
