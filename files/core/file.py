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
        """ """


# -----------------------------------------------------------------------------
def create_dir(path):
    if not os.path.isdir(path):
        try:
            os.makedirs(path, exist_ok=True)
        except FileExistsError:
            # directory already exists
            pass


# -----------------------------------------------------------------------------
def write_to_file(file_path, content, method="w"):
    file_dir = os.path.dirname(file_path)
    remove_file(file_path)
    create_dir(file_dir)

    with open(file_path, method) as f:
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


# -----------------------------------------------------------------------------
def file_ref_abs_dir(file_ref):
    return os.path.dirname(os.path.abspath(file_ref))


# -----------------------------------------------------------------------------
def file_has_content(file, content):
    with open(file) as f:
        if content in f.read():
            return True

    return False


# -----------------------------------------------------------------------------
def get_file_content(file):
    file = open(file, mode="r")
    content = file.read()
    file.close()
    return content


# -----------------------------------------------------------------------------
def prepend_to_file(file, content):
    file_content = content + "\n" + get_file_content(file)
    file_dest = open(file, "w")
    file_dest.write(file_content)
    file_dest.close()


# -----------------------------------------------------------------------------
def append_to_file(file, content):
    file_content = get_file_content(file) + "\n" + content
    file_dest = open(file, "w")
    file_dest.write(file_content)
    file_dest.close()


# -----------------------------------------------------------------------------
def replace_in_file(filename, old_string, new_string):
    with open(filename) as f:
        s = f.read()

        if old_string not in s:
            return

    # safely write the changed content, if found in the file
    with open(filename, "w") as f:
        s = s.replace(old_string, new_string)
        f.write(s)
        f.close()


# -----------------------------------------------------------------------------
def replace_line_in_file(filename, line, content):
    with open(filename) as f:
        lines = f.readlines()
        lines[line - 1] = content
        f.close()

        with open(filename, "w") as f:
            f.writelines(lines)
            f.close()


# -----------------------------------------------------------------------------
def get_file_line_content(filename, line):
    with open(filename) as f:
        lines = f.readlines()
        content = lines[line - 1]
        f.close()

        return content

    return None


# -----------------------------------------------------------------------------
def file_line_has_content(filename, line, content):
    line_content = get_file_line_content(filename, line)
    return line_content == content


# -----------------------------------------------------------------------------
def file_line_comment(filename, line, comment="#"):
    line_content = get_file_line_content(filename, line)

    if not line_content.startswith(comment):
        replace_line_in_file(filename, line, comment + line_content)


# -----------------------------------------------------------------------------
def file_line_comment_range(filename, line_start, line_end, comment="#"):
    for x in range(line_start, line_end + 1):
        file_line_comment(filename, x, comment)
