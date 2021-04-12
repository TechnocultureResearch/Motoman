#include <Arduino.h>

#include <FastPID.h>
#include <SimpleSerialShell.h>
#include <MPU6050.h>

#include "board.h"

#ifdef BOARD_NANO
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#endif

void TaskSerial(void *);
void TaskPollCurrentSense(void *);
void TaskPollAccelerometer(void *);
void TaskControlMotor(void *);

QueueHandle_t integerQueue;

void setup(){
  integerQueue = xQueueCreate(10, // Queue length
                              sizeof(int) // Queue item size
                              );
  if(integerQueue != NULL) {
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

void TaskSerial(void *pvParameters)
{
  (void) pvParameters;

  Serial.begin(115200);

  while (!Serial) {
    vTaskDelay(1);
  }

  int valueFromQueue = 0;

  for (;;)
  {
    if (xQueueReceive(integerQueue, &valueFromQueue, portMAX_DELAY) == pdPASS) {
      Serial.println(valueFromQueue);
    }
  }
}

void TaskPollCurrentSense(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    int sensorValue = analogRead(ACS712_ANALOG_IN_PIN);

    xQueueSend(integerQueue, &sensorValue, portMAX_DELAY);

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

    for (;;) {
      vTaskDelay(1);
    }
  }