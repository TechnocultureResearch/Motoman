#ifndef MAIN_H__
#define MAIN_H__

#include "board.h"

#ifdef BOARD_NANO
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#endif

void TaskSerial(void *);
void TaskPollCurrentSense(void *);
void TaskPollAccelerometer(void *);
void TaskControlMotor(void *);

typedef int16_t current_t;

typedef struct {
  int16_t x, y, z;
} pos_t;

typedef union {
  pos_t pos;
  current_t current;
} serial_packet_t;


// QueueHandle_t posStructQueue;
// QueueHandle_t currentIntegerQueue;
QueueHandle_t serialOutQueue;

#endif // MAIN_H_
