#include "CurrentSensor.h"
#include <Arduino.h>

QueueHandle_t CS_SerialOutQueue;
uint8_t device_pin;

void CurrentSensor_init(uint16_t stack_size, uint8_t priority,
                        QueueHandle_t queue_handle, uint8_t pin) {
  xTaskCreate(TaskPollCurrentSense,      // Task function
              "Analog Read from ACS712", // Task Name
              stack_size,                // Stack Size
              NULL,
              priority, // priority
              NULL);

  CS_SerialOutQueue = queue_handle;
  device_pin = pin;
}

void TaskPollCurrentSense(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    int sensorValue = analogRead(device_pin);

    xQueueSend(CS_SerialOutQueue, &sensorValue, portMAX_DELAY);

    vTaskDelay(1);
  }
}