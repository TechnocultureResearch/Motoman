#include "DOF6.h"
#include <MPU6050.h>
#include <Wire.h>

#include "message.h"

QueueHandle_t DOF6_SerialOutQueue;
QueueHandle_t DOF6_PositionQueue;

void TaskPollDOF6(void *);

void DOF6_init(uint16_t stack_size, uint8_t priority,
               QueueHandle_t serial_out_queue_handle,
               QueueHandle_t position_queue_handle) {
  xTaskCreate(TaskPollDOF6,                            // Task function
              "Measure rotation of the accelerometer", // Task Name
              stack_size, //                                     // Stack Size
              NULL,
              priority, // priority
              NULL);

  DOF6_SerialOutQueue = serial_out_queue_handle;
  DOF6_PositionQueue = position_queue_handle;
}

int getRollerAngle(MPU6050& mpu) {
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
    int angle = getRollerAngle(accel);
    
    serial_packet_t packet_roller_angle = {
      .type = INT_ROLLER_ANGLE, 
      .msg = angle};
    
    xQueueSend(DOF6_SerialOutQueue, &packet_roller_angle, portMAX_DELAY);
    xQueueSend(DOF6_PositionQueue, &packet_roller_angle, portMAX_DELAY);

    vTaskDelay(1);
  }
}
