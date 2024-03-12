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
