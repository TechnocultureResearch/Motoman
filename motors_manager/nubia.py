import sys

import motors_manager.commands
from nubia import Nubia, Options
from .nubia_plugin import NubiaExamplePlugin


def start_nubia():
    plugin = NubiaExamplePlugin()
    shell = Nubia(
        name="motoman",
        command_pkgs=motors_manager.commands,
        plugin=plugin,
        options=Options(
            persistent_history=True, auto_execute_single_suggestions=True
        ),
    )
    sys.exit(shell.run())