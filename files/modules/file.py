"""Module: File"""

import fnmatch
import os
import shutil
import stat
from distutils.dir_util import copy_tree


# -----------------------------------------------------------------------------
def remove_dir(path):
    shutil.rmtree(path, ignore_errors=True)


# -----------------------------------------------------------------------------
def remove_file(path):
    if os.path.isfile(path):
        os.remove(path)


# -----------------------------------------------------------------------------
def purge_files(root_path, pattern):
    for root, _, files in os.walk(root_path, topdown=False):
        for name in files:
            path = os.path.join(root, name)
            filename = os.path.basename(path)

            if fnmatch.fnmatch(filename, pattern):
                os.remove(path)


# -----------------------------------------------------------------------------
def purge_dirs(root_path, pattern):
    for root, dirs, _ in os.walk(root_path, topdown=False):
        for name in dirs:
            path = os.path.join(root, name)
            dirname = os.path.basename(path)

            if fnmatch.fnmatch(dirname, pattern):
                remove_dir(path)


# -----------------------------------------------------------------------------
def find_files(root_path, pattern):
    results = []
    for root, _, files in os.walk(root_path, topdown=False):
        for name in files:
            path = os.path.join(root, name)
            filename = os.path.basename(path)

            if fnmatch.fnmatch(filename, pattern):
                results.append(path)

    return results


# -----------------------------------------------------------------------------
def find_files_simple(root_path, pattern):
    results = []
    for item in os.listdir(root_path):
        path = os.path.join(root_path, item)

        if os.path.isfile(path):
            filename = os.path.basename(path)

            if fnmatch.fnmatch(filename, pattern):
                results.append(path)

    return results


# -----------------------------------------------------------------------------
def find_dirs(root_path, pattern):
    results = []
    for root, dirs, _ in os.walk(root_path, topdown=False):
        for name in dirs:
            path = os.path.join(root, name)
            dirname = os.path.basename(path)

            if fnmatch.fnmatch(dirname, pattern):
                results.append(path)

    return results


# -----------------------------------------------------------------------------
def find_dirs_simple(root_path, pattern):
    results = []
    for item in os.listdir(root_path):
        path = os.path.join(root_path, item)

        if os.path.isdir(path):
            if fnmatch.fnmatch(item, pattern):
                results.append(path)

    return results


# -----------------------------------------------------------------------------
def root_dir():
    return normalize_path(os.getcwd())


# -----------------------------------------------------------------------------
def normalize_path(path):
    if path:
        path = path.replace("\\", "/")
        return path
    else:
        ""


# -----------------------------------------------------------------------------
def create_dir(path):
    if not os.path.isdir(path):
        os.makedirs(path)


# -----------------------------------------------------------------------------
def write_to_file(dir_path, filename, content, method="w"):
    full_file_path = os.path.join(dir_path, filename)
    remove_file(full_file_path)
    create_dir(dir_path)

    with open(full_file_path, method) as f:
        f.write(content)
        f.close()


# -----------------------------------------------------------------------------
def read_file(file_path, method="r"):
    with open(file_path, method) as f:
        content = f.read()
        f.close()

    return content


# -----------------------------------------------------------------------------
def copy_file(from_path, to_path):
    create_dir(os.path.dirname(to_path))
    shutil.copyfile(from_path, to_path)


# -----------------------------------------------------------------------------
def home_dir():
    return os.path.expanduser("~")


# -----------------------------------------------------------------------------
def file_exists(path):
    if os.path.exists(path) and os.path.isfile(path):
        return True

    return False


# -----------------------------------------------------------------------------
def dir_exists(path):
    if os.path.exists(path) and os.path.isdir(path):
        return True

    return False


# -----------------------------------------------------------------------------
def copy_dir(src, dst, symlinks=False, ignore=None, ignore_file=None):
    if not os.path.exists(dst):
        os.makedirs(dst)
        shutil.copystat(src, dst)

    lst = os.listdir(src)

    if ignore:
        excl = ignore(src, lst)
        lst = [x for x in lst if x not in excl]

    for item in lst:
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if symlinks and os.path.islink(s):
            if os.path.lexists(d):
                os.remove(d)
            os.symlink(os.readlink(s), d)
            try:
                st = os.lstat(s)
                mode = stat.S_IMODE(st.st_mode)
                os.lchmod(d, mode)
            except:
                pass  # lchmod not available
        elif os.path.isdir(s):
            copy_dir(s, d, symlinks, ignore, ignore_file)
        else:
            if ignore_file is not None:
                ignored_file = ignore_file(s)
            else:
                ignored_file = False

            if not ignored_file:
                shutil.copy2(s, d)


# -----------------------------------------------------------------------------
def copy_all_inside(root_path, dst):
    create_dir(dst)
    copy_tree(root_path, dst, update=1)
