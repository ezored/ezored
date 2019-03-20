"""Module: Net"""

import sys

from ezored.mod import log
from ezored.mod import util

if sys.version_info >= (3,):
    import urllib.request as urllib2
else:
    import urllib2


# -----------------------------------------------------------------------------
def download(url, dst_file):
    req = urllib2.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
    u = urllib2.urlopen(req)

    with open(dst_file, 'wb') as f:
        meta = u.info()
        meta_func = meta.getheaders if hasattr(meta, 'getheaders') else meta.get_all
        meta_length = meta_func('Content-Length')
        file_size = None

        if meta_length:
            file_size = int(meta_length[0])

        if file_size:
            log.info('Download file size: {0}'.format(util.readable_file_size(file_size)))

        file_size_dl = 0
        block_sz = 8192
        block_count = 0

        while True:
            dbuffer = u.read(block_sz)

            if not dbuffer:
                break

            dbuffer_len = len(dbuffer)
            file_size_dl += dbuffer_len
            block_count += 1

            f.write(dbuffer)

            download_hook(block_count, block_sz, file_size)
            sys.stdout.flush()

        log.normal('')


# -----------------------------------------------------------------------------
def download_hook(count, block_size, total_size):
    """a download progress hook for urllib"""
    percent = int(count * block_size * 100 / total_size)

    msg = '\rDownloading: {0}% - {1}'.format(
        percent,
        util.readable_file_size(count * block_size)
    ).ljust(80)

    sys.stdout.write(msg)
