"""Run target with verb"""

import os

from pygemstones.system import runner as r
from pygemstones.type import list as ls
from pygemstones.util import log as l

from files.core import const, target


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]
    proj_path = params["proj_path"]

    targets = target.get_all_targets(proj_path)

    show_target_list = False

    if len(args) > 0:
        target_item = args[0]
        args.pop(0)

        if target_item in targets:
            target_verbs = target.get_all_target_verbs(proj_path, target_item)
            target_verbs = list(
                ls.filter_list(target_verbs, const.TARGET_VERBS_INTERNAL)
            )

            show_target_verb_list = False

            if len(args) > 0:
                verb_name = args[0]

                if verb_name in target_verbs:
                    l.i(
                        'Running "{0}" on target "{1}"...'.format(
                            verb_name, target_item
                        )
                    )

                    target_verb_folder = os.path.join(
                        proj_path,
                        const.DIR_NAME_FILES,
                        const.DIR_NAME_FILES_TARGETS,
                        target_item,
                        const.DIR_NAME_FILES_TARGET_VERBS,
                    )

                    params["target_name"] = target_item

                    r.run_external(
                        path=target_verb_folder,
                        module_name=verb_name,
                        command_name="run",
                        command_params=params,
                        show_log=False,
                        show_error_log=True,
                        throw_error=True,
                    )
                else:
                    show_target_verb_list = True
            else:
                show_target_verb_list = True

            if show_target_verb_list:
                if target_verbs and len(target_verbs) > 0:
                    l.colored("List of available target verbs:\n", l.MAGENTA)

                    for target_verb in target_verbs:
                        l.m("  - {0}".format(target_verb))
                else:
                    l.e("No target verbs available")
        else:
            show_target_list = True
    else:
        show_target_list = True

    if show_target_list:
        show_help(params)


# -----------------------------------------------------------------------------
def show_help(params):
    proj_path = params["proj_path"]
    targets = target.get_all_targets(proj_path)

    if targets and len(targets) > 0:
        l.colored("List of available targets:\n", l.MAGENTA)

        for target_item in targets:
            l.m("  - {0}".format(target_item))
    else:
        l.e("No targets available")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Run target verb"
