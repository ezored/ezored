"""Run target with verb"""

import os

import ezored.constants as const
import ezored.functions as fn
import ezored.logging as log


# -----------------------------------------------------------------------------
def run(params={}):
    args = params['args']

    targets = fn.get_all_targets()

    show_target_list = False

    if len(args) > 0:
        target_name = args[0]
        args.pop(0)

        if target_name in targets:
            target_verbs = fn.get_all_target_verbs(target_name)
            target_verbs = list(fn.filter_list(target_verbs, const.TARGET_VERBS_INTERNAL))

            show_target_verb_list = False

            if len(args) > 0:
                verb_name = args[0]

                if verb_name in target_verbs:
                    log.info('Running "{0}" on target "{1}"...'.format(verb_name, target_name))

                    target_verb_folder = os.path.join(
                        fn.root_dir(),
                        const.DIR_NAME_FILES,
                        const.DIR_NAME_FILES_TARGETS,
                        target_name,
                        const.DIR_NAME_FILES_TARGET_VERBS,
                    )

                    params = {
                        'target_name': target_name,
                        'args': args,
                    }

                    fn.exec_external(
                        path=target_verb_folder,
                        module_name=verb_name,
                        command_name='run',
                        command_params=params,
                        show_log=False,
                        show_error_log=True,
                        throw_error=True,
                    )

                    log.ok()
                else:
                    show_target_verb_list = True
            else:
                show_target_verb_list = True

            if show_target_verb_list:
                if target_verbs and len(target_verbs) > 0:
                    log.colored('List of available target verbs:\n', log.PURPLE)

                    for target_verb in target_verbs:
                        log.normal('  - {0}'.format(target_verb))
                else:
                    log.error('No target verbs available')
        else:
            show_target_list = True
    else:
        show_target_list = True

    if show_target_list:
        help(params)


# -----------------------------------------------------------------------------
def help(params={}):
    targets = fn.get_all_targets()

    if targets and len(targets) > 0:
        log.colored('List of available targets:\n', log.PURPLE)

        for target in targets:
            log.normal('  - {0}'.format(target))
    else:
        log.error('No targets available')


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'Run target with verb'
