import asyncio
import socket
from typing import Any
from termcolor import cprint
from nubia import command, argument, context

from .devices.ports import Ports

@command
def motors():
  """
  Show all motors.
  """
  for i, port in enumerate(Ports.ports()):
    cprint("Motor {}: {}".format(i, port), "cyan")


@command#(aliases=["m"])
@argument("id", type=int, positional=True)
def m(id: int):
  """
  Show a particular motor.
  """
  ctx = context.get_context()

  p = Ports.ports()
  try:
    cprint("Motor {}: {}".format(id, p[id]), "green")
  except IndexError as e:
    cprint("Error: No active motor connections found.", "red")
    if ctx.verbose:
      cprint(" Exception Raised: {}".format(e), "yellow")


@command(aliases=["p"])
def protocol():
  """
  Print the numbers that the motors use for different commands.
  """
  cprint("=============================== DEBUG MODE ==============================", "yellow")
  cprint("=========================================================================", "yellow")
  cprint("Initial Mode: Move slider OUTWARDS [Code: 1]", "yellow")
  cprint("Change Current Mode: by Sending the Corresponding Number.\n", "yellow")
  cprint("\tMove Slider OUTWARDS ===> 1", "yellow")
  cprint("\tMove Slider INWARDS  ===> 2", "yellow")
  cprint("\tSTOP Slider          ===> 3", "yellow")
  cprint("\tIDLE mode            ===> 4", "yellow")
  cprint("\tSET MOTOR SPEED      ===> 5 to 70", "yellow")
  cprint("=========================================================================", "yellow")
