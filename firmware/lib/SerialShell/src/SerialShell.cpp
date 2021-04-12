#include "SerialShell.h"
#include <Arduino.h>
#include <SimpleSerialShell.h>

QueueHandle_t SerialQueue;

void Serial_init(uint16_t stack_size, QueueHandle_t &queue_handle) {
  xTaskCreate(TaskSerial,                      // Task function
              "Manage a shell on Serial Port", // Task Name
              stack_size, // Stack size                             // Stack Size
              NULL,
              1, // priority
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

  Serial.println("C");
  for (;;) {
    if (xQueueReceive(SerialQueue, &valueFromQueue, portMAX_DELAY) ==
        pdPASS) {
      Serial.println("H");
      // print_serial_packet(&valueFromQueue);
    }
  }
}