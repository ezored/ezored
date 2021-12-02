"""Module: Util"""

from pygemstones.type import list as l


# -----------------------------------------------------------------------------
def get_version(params, config):
    version = l.get_arg_list_value(params["args"], "--version")

    if not version or len(version) == 0:
        proj_path = params["proj_path"]
        target_name = params["target_name"]
        target_config = config.run(proj_path, target_name, params)
        version = target_config["version"]

    return version
