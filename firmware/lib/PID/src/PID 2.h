#ifndef PID_H__
#define PID_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>

void PID_init(uint16_t stack_size, uint8_t priority, //
              QueueHandle_t motor_queue_handle,      //
              QueueHandle_t position_queue_handle,   //
              QueueHandle_t serial_out_queue_handle, //
              float Kp, float Ki, float Kd, float Hz);

#endif // PID_H__