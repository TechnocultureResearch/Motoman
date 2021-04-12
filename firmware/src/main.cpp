#include "board.h"
#include <Arduino.h>

#ifdef BOARD_NANO
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#endif

#include "CurrentSensor.h"
#include "DOF6.h"
#include "FeedbackMotor.h"
#include "PID.h"
#include "SerialShell.h"

QueueHandle_t serialOutQueue;


void setup(){
  serialOutQueue = xQueueCreate(
    10,             // Queue length
    sizeof(int16_t) // Queue item size
  );

  if (serialOutQueue != NULL) {
    Serial_init(512, serialOutQueue);
    CurrentSensor_init(128, serialOutQueue, ACS712_ANALOG_IN_PIN);
    // DOF6_init(512, serialOutQueue);
    FeedbackMotor_init(128);
  }
}

void loop() {} // Empty Loop