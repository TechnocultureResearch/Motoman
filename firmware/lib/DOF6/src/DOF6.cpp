#include "DOF6.h"
#include <MPU6050.h>
#include <Wire.h>

void TaskPollDOF6(void *);


QueueHandle_t DOF6_SerialOutQueue;

void DOF6_init(uint16_t stack_size, uint8_t priority,
               QueueHandle_t queue_handle) {
  xTaskCreate(TaskPollDOF6,                            // Task function
              "Measure rotation of the accelerometer", // Task Name
              stack_size, //                                     // Stack Size
              NULL,
              priority, // priority
              NULL);
  DOF6_SerialOutQueue = queue_handle;
}

void TaskPollDOF6(void *pvParameters) {
  (void)pvParameters;

  int16_t ax, ay, az = 0;
  int16_t gx, gy, gz = 0;

  Wire.begin();

  MPU6050 accel;
  accel.initialize();

  for (;;) {
    accel.getMotion6(
      &ax, &ay, &az, &gx, &gy, &gz
    );

    xQueueSend(
      DOF6_SerialOutQueue, 
      &gx, 
      portMAX_DELAY);

    vTaskDelay(1);
  }
}
