#include <Arduino.h>
#include "board.h"

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
    sizeof(int) // Queue item size
  );

  if (serialOutQueue != NULL) {
    // Create Tasks :
    // with predefined stack size, priority, and queues

    Serial_init(128, 1, serialOutQueue);

    CurrentSensor_init(
      128, 1,
      serialOutQueue, 
      ACS712_ANALOG_IN_PIN);
    
    DOF6_init(128, 3, serialOutQueue);
    
    FeedbackMotor_init(128, 1);
  }
}

void loop() {} // Empty Loop