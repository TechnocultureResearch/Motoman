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
// #include "SerialShell.h"
#include "SerialWriter.h"

QueueHandle_t serialOutQueue;
QueueHandle_t serialOutQueue1;

typedef enum {
  INT_ACCEL_DATA_GX,
  INT_ACCEL_DATA_GY,
  INT_ACCEL_DATA_GZ,
  INT_ACCEL_DATA_AX,
  INT_ACCEL_DATA_AY,
  INT_CURRENT_DATA,
  INT_ENCODER_DATA,
  INT_MOTOR_SPEED_DATA,
  INT_MOTOR_DIRECTION_DATA
} message_type_t;

typedef struct {
  message_type_t msg; char msg_content[8];
} serial_packet_t;

void setup(){
  serialOutQueue = xQueueCreate(
    10,             // Queue length
    sizeof(int) // Queue item size
  );

  serialOutQueue1 = xQueueCreate(10,         // Queue length
                                sizeof(message_type_t) // Queue item size
  );

  if (serialOutQueue != NULL) {
    // Create Tasks :
    // with predefined stack size, priority, and queues

    CurrentSensor_init(
      128, 1,
      serialOutQueue, 
      ACS712_ANALOG_IN_PIN);
    
    DOF6_init(128, 1, serialOutQueue);
    
    FeedbackMotor_init(128, 1);

    Serial_init(128, 1, serialOutQueue);
  }
}

void loop() {} // Empty Loop