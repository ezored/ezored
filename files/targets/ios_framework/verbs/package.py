"""Create universal framework"""

import os

import ezored.app.const as const
from ezored.modules import file
from ezored.modules import log
from ezored.modules import runner
from files.config import target_ios_framework as config


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params['proj_path']
    target_name = params['target_name']
    target_config = config.run(proj_path, target_name, params)

    archs = target_config['archs']
    build_types = target_config['build_types']

    log.info('Packaging universal framework...')

    if archs and len(archs) > 0:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                log.info('Copying for: {0}...'.format(build_type))

                # copy first folder for base
                framework_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    archs[0]['conan_arch'],
                    const.DIR_NAME_BUILD_TARGET,
                    'lib',
                    '{0}.framework'.format(target_config['project_name']),
                )

                dist_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    '{0}.framework'.format(target_config['project_name']),
                )

                file.remove_dir(dist_dir)
                file.copy_dir(framework_dir, dist_dir)

                # lipo
                lipo_archs_args = []

                for arch in archs:
                    lipo_archs_args.append(os.path.join(
                        proj_path,
                        const.DIR_NAME_BUILD,
                        target_name,
                        build_type,
                        arch['conan_arch'],
                        const.DIR_NAME_BUILD_TARGET,
                        'lib',
                        '{0}.framework'.format(target_config['project_name']),
                        target_config['project_name'],
                    ))

                lipo_args = [
                    'lipo',
                    '-create',
                    '-output',
                    os.path.join(
                        dist_dir,
                        target_config['project_name']
                    )
                ]

                lipo_args.extend(lipo_archs_args)

                runner.run(lipo_args, proj_path)

                # check file
                log.info('Checking file for: {0}...'.format(build_type))

                runner.run([
                    'file',
                    os.path.join(
                        dist_dir,
                        target_config['project_name']
                    )
                ], proj_path)
        else:
            log.info('Build type list for "{0}" is invalid or empty'.format(
                target_name
            ))
    else:
        log.info('Arch list for "{0}" is invalid or empty'.format(target_name))
