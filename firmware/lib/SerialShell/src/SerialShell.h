#ifndef SERIALSHELL_H__
#define SERIALSHELL_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>

void TaskSerial(void *);
void Serial_init(uint16_t stack_size, uint8_t priority,
                 QueueHandle_t queue_handle);

#endif // SERIALSHELL_H__