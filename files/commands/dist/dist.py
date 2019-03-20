"""Distribution files manager tool"""

import os

from ezored import constants as const
from ezored.mod import file
from ezored.mod import log
from ezored.mod import net
from ezored.mod import pack


# -----------------------------------------------------------------------------
def run(params={}):
    args = params['args']

    if len(args) > 0:
        action = args[0]

        if action:
            if action == 'download':
                download(params)
            elif action == 'pack':
                pack_dist_folder(params)
            else:
                help(params)
        else:
            help(params)
    else:
        help(params)


# -----------------------------------------------------------------------------
def download(params={}):
    log.info('Removing old file...')
    file.remove_file(const.FILE_NAME_DIST_PACKED)

    log.info('Downloading {0} file...'.format(const.FILE_NAME_DIST_PACKED))
    dst_file = os.path.join(file.root_dir(), const.FILE_NAME_DIST_PACKED)
    net.download(const.URL_DIST_FILE_PACKED, dst_file)

    log.info('Removing old folder...')
    file.remove_dir(os.path.join(file.root_dir(), const.DIR_NAME_DIST))

    log.info('Unpacking downloaded file...')
    pack.unpack(dst_file, file.root_dir())

    log.ok('')


# -----------------------------------------------------------------------------
def pack_dist_folder(params={}):
    log.info('Removing old file...')
    file.remove_file(const.FILE_NAME_DIST_PACKED)

    log.info('Packing {0} folder...'.format(const.DIR_NAME_DIST))
    dst_file = os.path.join(file.root_dir(), const.FILE_NAME_DIST_PACKED)
    dst_folder = os.path.join(file.root_dir(), const.DIR_NAME_DIST)
    pack.make_zipfile(dst_file, dst_folder)

    log.ok('')


# -----------------------------------------------------------------------------
def help(params={}):
    log.colored('Available actions:\n', log.PURPLE)
    log.normal('  - download')
    log.normal('  - pack')


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'Distribution files manager tool'
