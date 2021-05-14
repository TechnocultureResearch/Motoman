#include "SerialWriter.h"
#include <Arduino.h>

#include "message.h"

#ifdef DEBUG
#include "avr8-stub.h"
#endif

#ifndef BOARD_NANO
#define CONSOLE Serial1
#endif

#ifdef BOARD_NANO
#define CONSOLE Serial
#endif

QueueHandle_t SerialWriterQueue;
static int32_t g_baud_rate = 0;


// Forward Declarations
void TaskSerialWriter(void *);


void Serial_init(uint16_t stack_size, uint8_t priority,
                      QueueHandle_t queue_handle, const int32_t baud_rate) {
  xTaskCreate(
      TaskSerialWriter,                // Task function
      "Write to n Serial Port", // Task Name
      stack_size, // Stack size                             // Stack Size
      NULL,
      priority, // priority
      NULL);

  SerialWriterQueue = queue_handle;
  g_baud_rate = baud_rate;
}

void TaskSerialWriter(void *pvParameters) {
  (void)pvParameters;

  CONSOLE.begin(g_baud_rate);

  while (!CONSOLE) {
    vTaskDelay(1);
  }

  serial_packet_t valueFromQueue;

  for (;;) {
    if (xQueueReceive(SerialWriterQueue, &valueFromQueue, portMAX_DELAY) ==
        pdPASS) {
      #ifdef DEBUG
      breakpoint();
      #endif

      PRINT_MESSAGE(CONSOLE, valueFromQueue);
    }
  }
}
