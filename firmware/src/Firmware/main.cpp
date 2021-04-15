#include <Arduino.h>
#include "board.h"
#include "message.h"

#include <Arduino_FreeRTOS.h>
#include <queue.h>

#ifdef DEBUG
#include "avr8-stub.h"
#endif

#include "CurrentSensor.h"
#include "DOF6.h"
#include "FeedbackMotor.h"
#include "PID.h"
// #include "SerialShell.h"
#include "SerialWriter.h"
#include "InputEncoder.h"

QueueHandle_t serialOutQueue;

void setup(){
  #ifdef DEBUG
  debug_init();
  // breakpoint();
  #endif

  serialOutQueue = xQueueCreate(
    10,         // Queue length
    sizeof(message_type_t) // Queue item size
  );

  if (serialOutQueue != NULL) {
    // Create Tasks :
    // with predefined stack size, priority, and queues

    CurrentSensor_init(
      128, 2,
      serialOutQueue, 
      ACS712_ANALOG_IN_PIN);
    
    DOF6_init(128, 2, serialOutQueue);
    
    FeedbackMotor_init(128, 2);

    InputEncoder_init(
      128, 1,
      serialOutQueue, ENCODER_DIGITAL_OUT_CLK,
      ENCODER_DIGITAL_OUT_DT, ENCODER_DIGITAL_OUT_SW
    );

    Serial_init(128, 1, serialOutQueue, 115200);
  }
}

void loop() {} // Empty Loop