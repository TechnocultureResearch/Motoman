import serial
from serial.tools import list_ports
from typing import List, Set, Callable, Any
from dataclasses import dataclass, field
from termcolor import colored, cprint
from nubia import context


commands = [
  'Null',
  'Forward',
  'Reverse',
  'Stop',
  'Idle',
  'SetSpeed'
]


@dataclass
class Port:
  """
  Simple Port objects
  """
  id: int
  name: str
  VID: int
  PID: int = field(repr=False)
  device: str = field(repr=False)
  
  def __hash__(self):
    return hash(self.device)


is_uart: Callable[[Port], bool] = lambda port: 'tty' in port.name or 'usb' in port.name
has_vid: Callable[[Port], bool] = lambda port: port.VID is not None
description_has_arduino: Callable[[Port], bool] = lambda port: 'arduino' in port.description or 'Arduino' in port.description
# is_ftdi = lambda port: 0x0403 
# is_arduino 


class Ports:
  _count: int = 0
  _ports: Set[Port] = set()

  @staticmethod
  def fetch(
        getter: Callable[[], List[Any]] = list_ports.comports, 
        predicate: Callable[[str], bool] = description_has_arduino,
        *,
        printer: Callable = cprint
      ) -> List[Port]:
    """
    """

    updated_ports = set()
    for port in getter():
      if predicate(port):
        updated_ports.add(port)

    diff_port_1 = updated_ports.difference(Ports._ports)
    diff_port_2 = Ports._ports.difference(updated_ports)

    if len(diff_port_1):
      Ports._count += 1
      for _ in diff_port_1:
        Ports._ports.add(_)
      printer("{} new device(s) attached.".format(len(diff_port_1)), "green")
    elif len(diff_port_2):
      Ports._count -= 1
      for _ in diff_port_2:
        Ports._ports.remove(_)
      printer("{} device(s) removed.".format(len(diff_port_2)), "red")


  @staticmethod
  def ports(
        getter: Callable[[], List[Any]] = list_ports.comports, 
        predicate: Callable[[str], bool] = description_has_arduino
      ) -> List[Port]:
    """ 
    Prints each of the ports available with reasonable tty like names and vids.

    > Logic:
    > Get all ports -> Filter them based on a criteria -> return the filtered list of ports
    """
    Ports.fetch()
    return list(Ports._ports)


  @staticmethod
  def dispatch_command(id: int, command: int):
    """
    """

    ctx = context.get_context()

    try:
      p = list(Ports._ports)[id]
      with serial.Serial(p.device, 115200, timeout=1) as s:
        if ctx.verbose:
          cprint("Motor {}: ({}|{}) - {}({}-{})".format(id, p.description, p.name, commands[command], command, bin(command)), "green")
        else:
          cprint("Motor {}: {}".format(id, commands[command]), "green")
        s.write(command)
    except IndexError as e:
      print(e)
    except serial.SerialException as e:
      print(e)


# Run fetch at import-time
Ports.fetch()
