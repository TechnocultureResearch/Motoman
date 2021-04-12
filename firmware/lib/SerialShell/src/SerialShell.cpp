#include "SerialShell.h"
#include <Arduino.h>
#include <SimpleSerialShell.h>

QueueHandle_t SerialQueue;

void Serial_init(uint16_t stack_size, uint8_t priority,
                 QueueHandle_t queue_handle) {
  xTaskCreate(TaskSerial,                      // Task function
              "Manage a shell on Serial Port", // Task Name
              stack_size, // Stack size                             // Stack Size
              NULL,
              priority, // priority
              NULL);

  SerialQueue = queue_handle;
}

void TaskSerial(void *pvParameters) {
  (void)pvParameters;

  Serial.begin(115200);

  while (!Serial) {
    vTaskDelay(1);
  }

  int valueFromQueue;

  for (;;) {
    if (xQueueReceive(
      SerialQueue, 
      &valueFromQueue, 
      portMAX_DELAY) == pdPASS) {

      Serial.println(valueFromQueue);
    }
  }
}