#include <Arduino.h>
#include <Wire.h>

#include <FastPID.h>
#include <SimpleSerialShell.h>
#include <MPU6050.h>

#include "main.h"


void setup(){
  // currentIntegerQueue = xQueueCreate(10, // Queue length
  //                             sizeof(current_t) // Queue item size
  //                             );
  // posStructQueue = xQueueCreate(10,           // Queue length
  //                               sizeof(pos_t) // Queue item size
  // );
  serialOutQueue = xQueueCreate(10,           // Queue length
                                sizeof(serial_packet_t) // Queue item size
  );

  if (serialOutQueue != NULL) {
    // Create a task that consumes the queue if it was created.
    xTaskCreate(TaskSerial,                // Task function
                "Manage a shell on Serial Port", // Task Name
                128,                       // Stack Size
                NULL,
                1, // priority
                NULL);

    xTaskCreate(TaskPollCurrentSense,      // Task function
                "Analog Read from ACS712", // Task Name
                128,                       // Stack Size
                NULL,
                1, // priority
                NULL);

    xTaskCreate(TaskPollAccelerometer,     // Task function
                "Measure rotation of the accelerometer", // Task Name
                128,                       // Stack Size
                NULL,
                1, // priority
                NULL);

    xTaskCreate(TaskControlMotor,          // Task function
                "Control speed and direction of motor", // Task Name
                128,                       // Stack Size
                NULL,
                1, // priority
                NULL);
  }
}

void loop() {} // Empty Loop

void print_serial_packet(
  serial_packet_t* p){
  Serial.println(sizeof(*p));
}

void TaskSerial(void *pvParameters)
{
  (void) pvParameters;

  Serial.begin(115200);

  while (!Serial) {
    vTaskDelay(1);
  }

  // serial_packet_t *valueFromQueue =
      // (serial_packet_t *)malloc(sizeof(serial_packet_t));
  serial_packet_t valueFromQueue;

  for (;;)
  {
    if (xQueueReceive(serialOutQueue, &valueFromQueue, portMAX_DELAY) ==
        pdPASS) {
      print_serial_packet(&valueFromQueue);
    }
  }
}

void TaskPollCurrentSense(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    int sensorValue = analogRead(ACS712_ANALOG_IN_PIN);

    xQueueSend(serialOutQueue, &sensorValue, portMAX_DELAY);

    vTaskDelay(1);
  }
}

  void TaskControlMotor(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
      vTaskDelay(1);
    }
  }

  void TaskPollAccelerometer(void *pvParameters) {
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
      accel.getMotion6(
        &acc.x, &acc.y, &acc.z, 
        &gyro.x, &gyro.y, &gyro.z
      );

      xQueueSend(serialOutQueue, &gyro, portMAX_DELAY);

      vTaskDelay(1);
    }
  }