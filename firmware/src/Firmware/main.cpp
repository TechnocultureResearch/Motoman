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
#include "OffsetEncoder.h"
#include "PID.h"
#include "SerialWriter.h"

// #include "SerialShell.h"

QueueHandle_t SerialOutQueue;
QueueHandle_t MotorOutQueue;
QueueHandle_t PositionQueue;

void setup(){
  #ifdef DEBUG
  debug_init();
  // breakpoint();
  #endif

  SerialOutQueue = xQueueCreate(10,                    // Queue length
                                sizeof(message_type_t) // Queue item size
  );
  MotorOutQueue = xQueueCreate(10,                    // Queue length
                                sizeof(message_type_t) // Queue item size
  );
  PositionQueue = xQueueCreate(10,                    // Queue length
                                sizeof(message_type_t) // Queue item size
  );

  if (SerialOutQueue != NULL) {
    // Create Tasks :
    // with predefined stack size, priority, and queues

    /**
     * Output Only Tasks
     */
    OffsetEncoder_init(128, 1, // 
      PositionQueue,  //
      SerialOutQueue, // DEBUG only
      ENCODER_DIGITAL_OUT_CLK, //
      ENCODER_DIGITAL_OUT_DT, //
      ENCODER_DIGITAL_OUT_SW);

    CurrentSensor_init(128, 2, //
      MotorOutQueue,    // 
      SerialOutQueue,   // DEBUG only
      ACS712_ANALOG_IN_PIN);

    DOF6_init(512, 2, //
      PositionQueue, // 
      SerialOutQueue // 
    );

  /*
   * Input Only Taks
  */
    FeedbackMotor_init(128, 2, // 
      MotorOutQueue);

    Serial_init(512, 1, // 
      SerialOutQueue, // 
      SERIAL_1_BAUD_RATE);

    /**
     * Input and Output Tasks
     */
    PID_init(512, 1, //
      MotorOutQueue, // 
      PositionQueue, // 
      SerialOutQueue, // DEBUG only
      0, 0, 0, 0);
  }
}

void loop() {} // Empty Loop
