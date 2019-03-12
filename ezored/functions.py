"""General functions"""

import fnmatch
import importlib
import os
import shutil
import stat
import subprocess
import sys
from distutils.dir_util import copy_tree
from subprocess import PIPE

from ezored import constants as const
from ezored import logging as log


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
        path = path.replace('\\', '/')
        return path
    else:
        ''


# -----------------------------------------------------------------------------
def create_dir(path):
    if not os.path.isdir(path):
        os.makedirs(name=path)


# -----------------------------------------------------------------------------
def write_to_file(dir_path, filename, content, method='w'):
    full_file_path = os.path.join(dir_path, filename)
    remove_file(full_file_path)
    create_dir(dir_path)

    with open(full_file_path, method) as f:
        f.write(content)
        f.close()


# -----------------------------------------------------------------------------
def read_file(file_path, method='r'):
    with open(file_path, method) as f:
        content = f.read()
        f.close()

    return content


# -----------------------------------------------------------------------------
def run(args, cwd, env=None):
    proc = subprocess.Popen(
        args,
        env=env,
        cwd=cwd,
        stdout=PIPE,
        stderr=PIPE
    )

    out, err = proc.communicate()
    exitcode = proc.returncode

    return exitcode, err, out


# -----------------------------------------------------------------------------
def copy_file(from_path, to_path):
    create_dir(os.path.dirname(to_path))
    shutil.copyfile(from_path, to_path)


# -----------------------------------------------------------------------------
def home_dir():
    return os.path.expanduser('~')


# -----------------------------------------------------------------------------
def get_target_config(target_name):
    target_folder = os.path.join(
        root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_TARGETS,
        target_name,
        const.DIR_NAME_FILES_TARGET_CONFIG,
    )

    target_config_file = os.path.join(
        target_folder,
        const.FILE_NAME_FILES_TARGET_CONFIG,
    )

    if file_exists(target_config_file):
        return exec_external(
            path=target_folder,
            module_name=const.COMMAND_NAME_CONFIG,
            command_name='run',
            command_params={},
            show_log=False,
            show_error_log=True,
            throw_error=True,
        )

    return {}


# -----------------------------------------------------------------------------
def exec_external(
        path, module_name, command_name,
        command_params, show_log=False,
        show_error_log=False,
        throw_error=False
):
    """
    Execute external command inside path and return the command result.
    :param path: path where python file is located
    :param module_name: module name
    :param command_name: command name
    :param command_params: command params
    :param show_log: show log
    :param show_error_log: show log if exception
    :param throw_error: throw error if exception
    :return: command result
    """
    result = None

    sys_path = list(sys.path)
    original_cwd = os.getcwd()

    target_module = None
    command = None

    try:
        sys.path.insert(0, path)

        target_module = importlib.import_module(module_name)
        command = getattr(target_module, command_name)

        result = command(params=command_params)

        if show_log:
            log.normal('Command "{0}" finished with success'.format(
                command_name
            ))
    except Exception as e:
        if show_error_log:
            log.error('Error while call "{0}" on module "{1}": {2}'.format(
                command_name, module_name, e
            ))

        if throw_error:
            raise
    finally:
        if module_name in sys.modules:
            del sys.modules[module_name]

        if target_module is not None:
            del target_module

        if command is not None:
            del command

        sys.path = sys_path
        os.chdir(original_cwd)

    return result


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
def get_all_targets():
    results = []

    target_dir_list = find_dirs_simple(os.path.join(
        root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_TARGETS,
    ), '*')

    if target_dir_list:
        for target_dir in target_dir_list:
            target_name = os.path.basename(target_dir)

            if target_name:
                results.append(target_name)

    results.sort()
    return results


# -----------------------------------------------------------------------------
def get_all_target_verbs(target_name):
    results = []

    target_verbs_list = find_files_simple(os.path.join(
        root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_TARGETS,
        target_name,
        const.DIR_NAME_FILES_TARGET_VERBS,
    ), '*.py')

    if target_verbs_list:
        for verb_file in target_verbs_list:
            verb_name = os.path.basename(verb_file)
            verb_name = os.path.splitext(verb_name)[0]

            if verb_name:
                results.append(verb_name)

    results.sort()
    return results


# -----------------------------------------------------------------------------
def filter_list(full_list, excludes):
    s = set(excludes)
    return (x for x in full_list if x not in s)


# -----------------------------------------------------------------------------
def get_all_commands():
    results = []

    command_list = find_dirs_simple(os.path.join(
        root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_COMMANDS,
    ), '*')

    if command_list:
        for command_dir in command_list:
            command_name = os.path.basename(command_dir)

            if command_name:
                results.append(command_name)

    results.sort()
    return results


# -----------------------------------------------------------------------------
def run_command(command_name, method, params):
    """Run target with verb"""

    commands = get_all_commands()

    if command_name in commands:
        command_folder = os.path.join(
            root_dir(),
            const.DIR_NAME_FILES,
            const.DIR_NAME_FILES_COMMANDS,
            command_name,
        )

        return exec_external(
            path=command_folder,
            module_name=command_name,
            command_name=method,
            command_params=params,
            show_log=False,
            show_error_log=True,
            throw_error=True,
        )


# -----------------------------------------------------------------------------
def copy_dir(src, dst, symlinks=False, ignore=None):
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
            copy_dir(s, d, symlinks, ignore)
        else:
            shutil.copy2(s, d)


# -----------------------------------------------------------------------------
def run_simple(args, cwd):
    subprocess.call(
        args,
        cwd=cwd
    )


# -----------------------------------------------------------------------------
def copy_all_inside(root_path, dst):
    create_dir(dst)
    copy_tree(root_path, dst, update=1)
