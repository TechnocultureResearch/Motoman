# Crash continues, Blocking Shell library

The program is being difficult to continue with due to the limitions of the microcontroller. Crash continues when all the tasks (especially the Serial tasks) are on. This crash is likely to be due to a segmentaion fault or a similar memory boundry related issue. However, commenting on it with clarity can not be done without a reasonable debugger in line. 

Another serious problem is the use of SimpleSerialShell library is difficult to integrate as it does not provide a non-blocking interface.


## Option 1: Moving to STM32/mbedOS
MbedOS and appears to be the next best option for rapid development comparable to arduino in availability of drivers (MPU6050), and libraries(Shell). **Drawback**: This ties us down to STM32 based microcontrollers - this however is not a significant drawback as **Microfabricator T** does not have a requirement to be as low cost as possible.


## Option 2: Replacing serial shell with a digital encoder and buttons

Replacing a serial shell with a digital encoder and buttons would allow for a tactile UI, and be less burdensome on the tiny RAM of the arduino nano. We can in this scenario continue to use the serial port to send information to the computer, but we eliminate the need to wait on inputs. This does not by any means represent an engineering bottleneck. However, in terms of time spent building a concurrent serial shell - it is unclear if the utility is equal to the effort. Furthermore, all the requirements of the system should be possible to achieve without such a shell.

> Problem left unsolved without a shell:
> - How could the system recieve parameters for the PID controller when it boots up? 


