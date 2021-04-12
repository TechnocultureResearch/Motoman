#ifndef DOF6_H__
#define DOF6_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>


typedef struct {
  int16_t x, y, z;
} pos_t;

void DOF6_init(uint16_t stack_size, QueueHandle_t &queue_handle);
void TaskPollDOF6(void *);


#endif // DOF6_H__