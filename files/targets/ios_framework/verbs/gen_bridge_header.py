"""Generate bridging header"""

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

    log.info('Generating bridging header...')

    if archs and len(archs) > 0:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                log.info('Generating for: {0}...'.format(build_type))

                dist_headers_dir = os.path.join(
                    fn.root_dir(),
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    '{0}.framework'.format(target_config['project_name']),
                    'Headers',
                )

                header_files = fn.find_files(dist_headers_dir, '*.h')

                bridge_file = os.path.join(
                    fn.root_dir(),
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    'Bridging-Header.h',
                )

                content = ''

                for header_file in header_files:
                    header_file_name = os.path.basename(header_file)
                    
                    if not validate_header_file_name(header_file_name):
                        continue

                    header_file = header_file.replace(dist_headers_dir + '/', '')

                    content = content + '#include \"{0}\"\n'.format(
                        header_file,
                    )

                if len(content) > 0:
                    fn.remove_file(bridge_file)

                    fn.write_to_file(os.path.join(
                        fn.root_dir(),
                        const.DIR_NAME_DIST,
                        target_name,
                        build_type,
                    ), 'Bridging-Header.h', content)
                else:
                    log.error('{0}'.format(
                        'File not generate because framework headers is empty'
                    ))
        else:
            log.info('Build type list for "{0}" is invalid or empty'.format(
                target_name
            ))
    else:
        log.info('Arch list for "{0}" is invalid or empty'.format(
            target_name
        ))


# -----------------------------------------------------------------------------
def validate_header_file_name(header_file_name):
    if '+Private' in header_file_name:
        return False

    return True
