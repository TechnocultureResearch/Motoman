#include "SerialWriter.h"
#include <Arduino.h>

QueueHandle_t SerialWriterQueue;
void TaskSerialWriter(void *);

void Serial_init(uint16_t stack_size, uint8_t priority,
                      QueueHandle_t queue_handle) {
  xTaskCreate(
      TaskSerialWriter,                // Task function
      "Write to n Serial Port", // Task Name
      stack_size, // Stack size                             // Stack Size
      NULL,
      priority, // priority
      NULL);

  SerialWriterQueue = queue_handle;
}

void TaskSerialWriter(void *pvParameters) {
  (void)pvParameters;

  Serial.begin(115200);

  while (!Serial) {
    vTaskDelay(1);
  }

  int valueFromQueue = 0;

  for (;;) {
    if (xQueueReceive(SerialWriterQueue, &valueFromQueue, portMAX_DELAY) ==
        pdPASS) {

      Serial.println(valueFromQueue);
    }
  }
}
