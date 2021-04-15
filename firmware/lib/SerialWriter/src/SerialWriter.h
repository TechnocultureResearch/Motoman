#ifndef SERIALWRITER_H__
#define SERIALWRITER_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>

void Serial_init(uint16_t stack_size, uint8_t priority,
                 QueueHandle_t queue_handle, const int32_t baud_rate);

#endif // SERIALWRITER_H__