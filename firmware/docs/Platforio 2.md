1. Default keyboard bindings for vs code
    > `ctrl + alt + b`: build
    > `ctrl + alt + u`: upload
    > `ctrl + alt + s`: serial port monitor
2. Command line for build and upload
  - `pio run`: Build
  - `pio run --target upload`: flash binary to the microcontroller
  - `pio device monitor`: open serial port on Serial port
  >  `pio` is an alias for the command `platformio`
    - Prefferable to Python-Serial in order to get an interactive shell with input as well as output
      > `pyserial-miniterm /dev/ttyUSB0 115200` (install using pip or apt)
