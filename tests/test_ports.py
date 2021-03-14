from ProjectContext import ports
from dataclass import make_dataclass

def getter():
  entries = [
    {
      "name": 'tty3',
      "vid" : 0x0403,
      "pid": 0x6001,
      "device": "/dev/tty3"
    },
    {
      "name": 'cu.USB01',
      "vid" : 0x0403,
      "pid": 0x6011,
      "device": "/dev/cu.USB01"
    },
    {
      "name": 'tty3',
      "vid" : 0x0403,
      "pid": 0x6014,
      "device": "/dev/cu.usb.tty1"
    }
  ]

  l = list()
  for entry in entries:
    p = make_dataclass(ports.Port, entry)
    l.append(p)

  return l

def test_get_uart_ports():
  port_list = ports.get_ports(getter) 
  names = [port.name for port in port_list] 
  print(names)
  names == ['tty3', 'cu.USB01', 'cu.usb.tty1']