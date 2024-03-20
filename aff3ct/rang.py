from ._ext.rang import style, bg, fg, fgB, bgB

style.__add__ = lambda slf, message: str(slf) + message
style.__radd__ = lambda slf, message: message + str(slf)

bg.__add__ = lambda slf, message: str(slf) + message
bg.__radd__ = lambda slf, message: message + str(slf)

fg.__add__ = lambda slf, message: str(slf) + message
fg.__radd__ = lambda slf, message: message + str(slf)

bgB.__add__ = lambda slf, message: str(slf) + message
bgB.__radd__ = lambda slf, message: message + str(slf)

fgB.__add__ = lambda slf, message: str(slf) + message
fgB.__radd__ = lambda slf, message: message + str(slf)


def warning_tag(instr: str):
    """
    Preppend warning tag to a string.

    Args:
        instr (str): Input string

    Returns:
        out (str): Tagged string
    """
    return style.bold + fg.yellow + "(WW) " + style.reset + instr


def error_tag(instr: str):
    """
    Preppend error tag to a string.

    Args:
        instr (str): Input string

    Returns:
        out (str): Tagged string
    """
    return style.bold + fg.red + "(EE) " + style.reset + instr


def info_tag(instr: str):
    """
    Preppend information tag to a string.

    Args:
        instr (str): Input string

    Returns:
        out (str): Tagged string
    """
    return style.bold + fg.blue + "(II) " + style.reset + instr


def positive_tag(instr: str):
    """
    Preppend information tag to a string.

    Args:
        instr (str): Input string

    Returns:
        out (str): Tagged string
    """
    return style.bold + fg.freen + "(II) " + style.reset + instr
