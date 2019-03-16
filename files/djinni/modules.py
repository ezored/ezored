"""Djinni modules"""


# -----------------------------------------------------------------------------
def get_modules(params={}):
    return [
        'app-domain',
        'app-core',
        'app-data-services',
        'app-system-services',
        'app-helpers',

        'datetime',
        'file-helper',
        'http-client',
        'logger',
        'shared-data',
        'string-helper',
    ]
