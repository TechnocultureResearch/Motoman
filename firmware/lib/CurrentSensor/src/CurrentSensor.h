#ifndef CURRENT_SENSOR_H__
#define CURRENT_SENSOR_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>

void CurrentSensor_init(uint16_t stack_size, uint8_t priority,
                        QueueHandle_t queue_handle, uint8_t pin);

#endif // CURRENT_SENSOR_H__