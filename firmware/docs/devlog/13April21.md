# Crash continues, Blocking Shell library

The program is being difficult to continue with due to the limitions of the microcontroller. Crash continues when all the tasks (especially the Serial tasks) are on. This crash is likely to be due to a segmentaion fault or a similar memory boundry related issue. However, commenting on it with clarity can not be done without a reasonable debugger in line. 

Another serious problem is the use of SimpleSerialShell library is difficult to integrate as it does not provide a non-blocking interface.

## Considerations: Moving to STM32/mbedOS
MbedOS and appears to be the next best option for rapid development comparable to arduino in availability of drivers (MPU6050), and libraries(Shell). **Drawback**: This ties us down to STM32 based microcontrollers - this however is not a significant drawback as **Microfabricator T** does not have a requirement to be as low cost as possible.
