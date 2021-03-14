from serial.tools import list_ports
from typing import List, Callable, Any
from dataclasses import dataclass, field


is_uart = lambda port: 'tty' in port.name or 'usb' in port.name
# is_ftdi = lambda port: 0x0403 
# is_arduino 


@dataclass
class Port:
  """
  Simple Port objects
  """
  name: str
  vid: int
  device: str = field(repr=False)
  pid: int = field(repr=False)


def get_ports(
      getter: Callable[[], List[Any]] = list_ports.comports, 
      predicate: Callable[[str], bool] = is_uart
    ) -> List[Port]:
  """ 
  Return a list of Ports data objects containing name and device identifier
  """
  ports = [Port(port_info.name, port_info.vid, port_info.device, port_info.pid) for port_info in getter()]
  uart_ports = list(filter(predicate, ports))
  return uart_ports
