#include "DOF6.h"
#include <MPU6050.h>
#include <Wire.h>

#include "message.h"

QueueHandle_t DOF6_SerialOutQueue;

void TaskPollDOF6(void *);


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


int getVerticalAngle(MPU6050& mpu) {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  int i = 0;
  long x = 0;
  long y = 0;
  long z = 0;

  int repeatCount = 100;

  // 
  for (i = 0; i < repeatCount; ++i) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    x = x + ax; // 
    y = y + ay; // 
    z = z + az; // 
  }

  double avX = x / repeatCount;
  double avY = y / repeatCount;

  int verticalAngle = atan2(avX - 507, avY - 520) / 3.14159 * 180.0;
  // Serial.println(verticalAngle);
  return verticalAngle;
}


void TaskPollDOF6(void *pvParameters) {
  (void)pvParameters;

  Wire.begin();
  MPU6050 accel;

  accel.initialize();

  for (;;) {
    int angle = getVerticalAngle(accel);
    serial_packet_t packet_vert_angle = {.type = INT_ACCEL_DATA_GZ, .msg = angle};
    xQueueSend(DOF6_SerialOutQueue, &packet_vert_angle, portMAX_DELAY);

    vTaskDelay(1);
  }
}
