"""Distribution files manager tool"""

import os

from app import const
from mod import file
from mod import log
from mod import net
from mod import pack


# -----------------------------------------------------------------------------
def run(params):
    args = params['args']

    if len(args) > 0:
        action = args[0]

        if action:
            if action == 'download':
                download(params)
            elif action == 'pack':
                pack_dist_folder(params)
            else:
                show_help(params)
        else:
            show_help(params)
    else:
        show_help(params)


# -----------------------------------------------------------------------------
def download(params):
    proj_path = params['proj_path']

    log.info('Removing old file...')
    file.remove_file(const.FILE_NAME_DIST_PACKED)

    log.info('Downloading {0} file...'.format(const.FILE_NAME_DIST_PACKED))
    dst_file = os.path.join(proj_path, const.FILE_NAME_DIST_PACKED)
    net.download(const.URL_DIST_FILE_PACKED, dst_file)

    log.info('Removing old folder...')
    file.remove_dir(os.path.join(proj_path, const.DIR_NAME_DIST))

    log.info('Unpacking downloaded file...')
    pack.unpack(dst_file, proj_path)

    log.ok('')


# -----------------------------------------------------------------------------
def pack_dist_folder(params):
    proj_path = params['proj_path']

    dist_file = os.path.join(proj_path, const.FILE_NAME_DIST_PACKED)
    dist_folder = os.path.join(proj_path, const.DIR_NAME_DIST)

    if not os.path.isdir(dist_folder):
        log.error('Distribution folder not exists: {0}'.format(dist_folder))

    log.info('Removing old file...')
    file.remove_file(const.FILE_NAME_DIST_PACKED)

    log.info('Packing {0} folder...'.format(const.DIR_NAME_DIST))
    pack.make_zipfile(dist_file, dist_folder)

    log.ok('')


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored('Available actions:\n', log.PURPLE)
    log.normal('  - download')
    log.normal('  - pack')


# -----------------------------------------------------------------------------
def get_description(params):
    return 'Distribution files manager tool'
