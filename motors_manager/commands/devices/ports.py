from serial.tools import list_ports
from typing import List, Set, Callable, Any
from dataclasses import dataclass, field
from termcolor import cprint

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
  def ports(
        getter: Callable[[], List[Any]] = list_ports.comports, 
        predicate: Callable[[str], bool] = description_has_arduino
      ) -> List[Port]:
    """ 
    Prints each of the ports available with reasonable tty like names and vids.

    > Logic:
    > Get all ports -> Filter them based on a criteria -> return the filtered list of ports
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
      cprint("{} new device(s) attached.".format(len(diff_port_1)), "green")
    elif len(diff_port_2):
      Ports._count -= 1
      for _ in diff_port_2:
        Ports._ports.remove(_)
      cprint("{} device(s) removed.".format(len(diff_port_2)), "red")
    # print(Ports._ports)

    return list(Ports._ports)
