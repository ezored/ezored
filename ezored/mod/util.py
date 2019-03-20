"""Module: Util"""


# -----------------------------------------------------------------------------
def filter_list(full_list, excludes):
    s = set(excludes)
    return (x for x in full_list if x not in s)


# -----------------------------------------------------------------------------
def readable_file_size(num, suffix='b'):
    """
    Readable file size
    :param num: Bytes value
    :type num: int
    :param suffix: Unit suffix (optionnal) default = b
    :type suffix: str
    :rtype: str
    """
    for unit in ['', 'k', 'M', 'G', 'T', 'P', 'E', 'Z']:
        if abs(num) < 1024.0:
            return "%3.1f %s%s" % (num, unit, suffix)

        num /= 1024.0

    return "%.1f%s%s" % (num, 'Yi', suffix)
