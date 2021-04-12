#include "DOF6.h"
#include <MPU6050.h>
#include <Wire.h>

QueueHandle_t DOF6_SerialOutQueue;

void TaskPollDOF6(void *pvParameters) {
  (void)pvParameters;

  MPU6050 accel;
  pos_t acc = {0, 0, 0};
  pos_t gyro = {0, 0, 0};

  /*
    In current hardware setup:
      - gx or gy is in the direction normal to the chip?
  */

  Wire.begin();
  accel.initialize();

  for (;;) {
    accel.getMotion6(&acc.x, &acc.y, &acc.z, &gyro.x, &gyro.y, &gyro.z);

    xQueueSend(DOF6_SerialOutQueue, &gyro.x, portMAX_DELAY);

    vTaskDelay(1);
  }
}

void DOF6_init(uint16_t stack_size, QueueHandle_t &queue_hande){
  xTaskCreate(TaskPollDOF6,                   // Task function
              "Measure rotation of the accelerometer", // Task Name
              stack_size, //                                     // Stack Size
              NULL,
              1, // priority
              NULL);
  DOF6_SerialOutQueue = queue_hande;
}