from typing import Any
from termcolor import cprint
from nubia import command, argument, context

from motoman.commands.devices.ports import Ports

@command
def motors():
  """
  Show all motors.
  """
  for i, port in enumerate(Ports.ports()):
    cprint("Motor {}: {}".format(i, port), "cyan")


@command#(aliases=["m"])
@argument("id", description="Motor number the command is to be sent to", type=int, positional=True)
@argument("command", description="Command to be sent to the given motor", choices=range(1,71), type=int, positional=True)
# TODO: Move the constants associated to the microcontroller protocol into the config file
def m(id: int, command: int):
  """
  Show a particular motor.
  """
  ctx = context.get_context()

  p = Ports.ports()
  try:
    if ctx.verbose:
      cprint("Motor {}: {}".format(id, p[id]), "green")
    Ports.dispatch_command(id, command)
  except IndexError as e:
    cprint("Error: Motor connection not found.", "red")
    if ctx.verbose:
      cprint(" Exception Raised: {}".format(e), "yellow")


@command(aliases=["p"])
def protocol():
  """
  Print the numbers that the motors use for different commands.
  """
  cprint("")
  cprint("=============================== PROTOCOL ==============================")
  cprint("=======================================================================")
  cprint("Initial Mode: Move slider OUTWARDS [Code: 1]")
  cprint("Change Current Mode: by Sending the Corresponding Number.\n")
  cprint("\tMove Slider OUTWARDS ===> 1", "yellow")
  cprint("\tMove Slider INWARDS  ===> 2", "yellow")
  cprint("\tSTOP Slider          ===> 3", "yellow")
  cprint("\tIDLE mode            ===> 4", "yellow")
  cprint("\tSET MOTOR SPEED      ===> 5 to 70", "yellow")
  cprint("=======================================================================")
  cprint("")


protocol()
motors()
