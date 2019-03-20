"""Module: Pack"""
import os
import tarfile
import zipfile


# -----------------------------------------------------------------------------
def unpack(src_path, dst_path, filename=''):
    if '.zip' in src_path:
        with zipfile.ZipFile(src_path, 'r') as archive:
            archive.extractall(dst_path + ('' if len(filename) == 0 else '/' + filename))
            archive.close()
    elif '.tgz' or '.bz2' in src_path:
        with tarfile.TarFile(src_path, 'r') as archive:
            archive.extractall(dst_path + ('' if len(filename) == 0 else '/' + filename))
            archive.close()


# -----------------------------------------------------------------------------
def make_zipfile(output_filename, source_dir):
    exclude_list = [
        'Thumbs.db',
        '.DS_Store',
    ]

    relroot = os.path.abspath(os.path.join(source_dir, os.pardir))

    with zipfile.ZipFile(output_filename, "w", zipfile.ZIP_DEFLATED) as zip:
        for root, dirs, files in os.walk(source_dir):
            # add directory (needed for empty dirs)
            zip.write(root, os.path.relpath(root, relroot))
            for file_item in files:
                if file_item in exclude_list:
                    continue

                filename = os.path.join(root, file_item)

                if os.path.isfile(filename):  # regular files only
                    arcname = os.path.join(os.path.relpath(root, relroot), file_item)
                    zip.write(filename, arcname)
