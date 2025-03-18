import sys

if sys.version_info < (3, 10):
    from importlib_metadata import entry_points
else:
    from importlib.metadata import entry_points

plugins = {}
_plugins = entry_points(group="streampu.plugins")
for _ in _plugins:
    plugins[_.name] = _.load()


def installed_plugins():
    plugin_list = [["Name", "Version"]]
    for k, v in plugins.items():
        if hasattr(v, "__version__"):
            plugin_list.append([k, v.__version__])
        elif hasattr(v, "version"):
            plugin_list.append([k, v.__version__])
        else:
            plugin_list.append([k, "?"])
    widths = [max(map(len, col)) for col in zip(*plugin_list)]
    print("-" * (sum(widths) + 4))
    print("|", "  ".join((val.ljust(width) for val, width in zip(plugin_list[0], widths))), "|", sep="")
    print("-" * (sum(widths) + 4))
    for row in plugin_list[1:]:
        print("|", "  ".join((val.ljust(width) for val, width in zip(row, widths))), "|", sep="")
    print("-" * (sum(widths) + 4))


__all__ = [installed_plugins, plugins]
