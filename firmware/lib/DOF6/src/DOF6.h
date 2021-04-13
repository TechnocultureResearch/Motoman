#ifndef DOF6_H__
#define DOF6_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>


void DOF6_init(
  uint16_t stack_size, 
  uint8_t priority,
  QueueHandle_t queue_handle
);



#endif // DOF6_H__