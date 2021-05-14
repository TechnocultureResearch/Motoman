#include "firmware.h"


QueueHandle_t SerialOutQueue;
QueueHandle_t MotorOutQueue;
QueueHandle_t PositionQueue;


void setup(){
  #ifdef DEBUG
  debug_init();
  // breakpoint();
  #endif

  SerialOutQueue = xQueueCreate( //
      QUEUE_SIZE_SMALL,          // Queue length
      sizeof(message_type_t)     // Queue item size
  );
  MotorOutQueue = xQueueCreate( //
      QUEUE_SIZE_SMALL,         // Queue length
      sizeof(message_type_t)    // Queue item size
  );
  PositionQueue = xQueueCreate(//
      QUEUE_SIZE_SMALL, // Queue length
      sizeof(message_type_t) // Queue item size
  );

  if (SerialOutQueue != NULL) {
    // Create Tasks :
    // with predefined stack size, priority, and queues

    /**
     * Output Only Tasks
     */
    OffsetEncoder_init(   //
        STACK_SIZE_SMALL, //
        PRIORITY_LOW,     //

        // Queues
        PositionQueue,
        // DEBUG only
        SerialOutQueue,

        // Pins
        ENCODER_DIGITAL_OUT_CLK, //
        ENCODER_DIGITAL_OUT_DT,  //
        ENCODER_DIGITAL_OUT_SW);


    CurrentSensor_init(   //
        STACK_SIZE_SMALL, //
        PRIORITY_LOW,     //
        
        // Queues
        MotorOutQueue,
        // DEBUG only
        SerialOutQueue, 
        
        // Pins
        ACS712_ANALOG_IN_PIN);


    DOF6_init(//
      STACK_SIZE_SMALL, //
      PRIORITY_LOW, //
      
      // Queues
      PositionQueue, // 
      SerialOutQueue // 
    );

  /**
   * Input Only Taks
  */
    FeedbackMotor_init(//
      STACK_SIZE_SMALL, //
      PRIORITY_LOW, // 

      // Queues
      MotorOutQueue);

    Serial_init(//
      STACK_SIZE_SMALL,// 
      PRIORITY_LOW, // 

      // Queues
      SerialOutQueue, 
      
      // Config Variables
      SERIAL_1_BAUD_RATE);

    /**
     * Input and Output Tasks
     */
    PID_init(//
      STACK_SIZE_SMALL, 
      PRIORITY_LOW, //
      
      // Queues
      MotorOutQueue, // 
      PositionQueue, // 
      // DEBUG Only
      SerialOutQueue,

      // PID Parameters
      0, 0, 0, 0);
  }
}

void loop() {} // Empty Loop