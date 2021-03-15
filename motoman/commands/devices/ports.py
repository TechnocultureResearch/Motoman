from os import close
import serial
from serial.tools import list_ports
from typing import List, Set, Callable, Any
from dataclasses import dataclass, field
from termcolor import colored, cprint
from nubia import context
# from enum import Enum


commands = [
  'Null',
  'Forward',
  'Reverse',
  'Stop',
  'Idle',
  'SetSpeed'
]


# class port_errors(Enum):
#   PortNotFound = 1
#   PortBusy = 2
#   PortNameInvalid = 3


# def error(err: str):
#   try:
#     err_msg = port_errors[err]
#     print(err_msg)
#   except IndexError as e:
#     print(e)


@dataclass
class Port:
  """
  Simple Port objects
  """
  id: int
  name: str
  vid: int
  pid: int = field(repr=False)
  device: str = field(repr=False)
  
  def __hash__(self):
    return hash(self.device)


is_uart: Callable[[Port], bool] = lambda port: 'tty' in port.name or 'usb' in port.name
has_vid: Callable[[Port], bool] = lambda port: port.vid is not None
description_has_arduino: Callable[[Port], bool] = lambda port: 'arduino' in port.description or 'Arduino' in port.description
criteria: Callable[[Port], bool] = lambda port: (is_uart(port) or description_has_arduino(port)) and has_vid(port)


class Ports:
  _count: int = 0
  _ports: Set[Port] = set()
  _connections: Set[serial.Serial] = set()

  @staticmethod
  def fetch(
        getter: Callable[[], List[Any]] = list_ports.comports, 
        predicate: Callable[[str], bool] = criteria,
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
        new_connection = serial.Serial(port=_.device, baudrate=115200, timeout=.1)
        Ports._connections.add(new_connection)
      printer("{} new device(s) attached.".format(len(diff_port_1)), "green")
    elif len(diff_port_2):
      Ports._count -= 1
      for _ in diff_port_2:
        # i = Ports._ports.index(_)
        Ports._ports.remove(_)
        # close_this = serial.Serial()
        # close_this.port = _.device
        # close_this.baudrate = 115200
        # close_this.timeout = .1
        # p = Ports._connections.remove(close_this)
        # p.close()
        # Ports._connections.remove()
      printer("{} device(s) removed.".format(len(diff_port_2)), "red")


  @staticmethod
  def ports(
        getter: Callable[[], List[Any]] = list_ports.comports, 
        predicate: Callable[[str], bool] = criteria
      ) -> List[Port]:
    """ 
    Prints each of the ports available with reasonable tty like names and vids.

    > Logic:
    > Get all ports -> Filter them based on a criteria -> return the filtered list of ports
    """
    Ports.fetch()
    return list(Ports._ports)

  @staticmethod
  def print_command(id: int, port: Port, command: int, msg: str):
    """
    """

    ctx = context.get_context()

    command_name = ''
    try:
      command_name = commands[command]
    except:
      command_name = commands[-1]
    
    if ctx.verbose:
      cprint("Motor {}: ({}|{}) - {}({}-{})".format(id, port.description, port.name, command_name, command, msg), "green")
    else:
      cprint("Motor {}: {}".format(id, command_name), "green")
    

  @staticmethod
  def dispatch_command(id: int, command: int):
    """
    """

    ctx = context.get_context()
    
    msg = str(command).encode('ascii')

    try:
      port = list(Ports._ports)[id]
    except IndexError as e:
      cprint(e, "red")
      # with serial.Serial(p.device, 115200, timeout=1) as s:
        # msg = command.to_bytes(8, 'little')
    try:
      s = list(Ports._connections)[id]
      s.write(msg)
      # s.flush()
      Ports.print_command(id, port, command, msg)
    except IndexError as e:
      cprint("Error: Connection not found. {}".format(e), "red")
      # error(port_errors.PortNotFound)
    except serial.SerialException as e:
      cprint(e, "red")


# Run fetch at import-time
Ports.fetch()
