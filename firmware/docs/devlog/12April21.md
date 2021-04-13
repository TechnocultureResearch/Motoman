## Crash at Boot time: Stack Size of Threads and Queues of Union data types

Arduino Nano `L Led` blinking bright red and the serial port monitor showing no data. Suggests a crash. Upon reading a few forums, it was deduced to be due to stack size allocated being overflown. There needs to be a way to debug these issues moving forward. Temperarily solved by using a simple integer Queue instead of a queue based on a union datatype between an int and a struct. Finally, the stack size of 512 on the thread emitting accelerometer data was deduced to be a cause of the crash - given that reducing it to 128bytes from 512 bytes led to elimination of the crash at boot.


## Trying gitmoji

Adds visual queue, however these visual queues are not as descriptive as commitizen tags. 

