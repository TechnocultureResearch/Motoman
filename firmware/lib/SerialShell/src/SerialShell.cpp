#include "SerialShell.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <SimpleSerialShell.h>

#include "commands.h"

void TaskSerialShell(void *);


void SerialShell_init(uint16_t stack_size, uint8_t priority) {
  xTaskCreate(
      TaskSerialShell,                 // Task function
      "Manage a shell on Serial Port", // Task Name
      stack_size, // Stack size                             // Stack Size
      NULL,
      priority, // priority
      NULL);
}

void TaskSerialShell(void *pvParameters) {
  (void)pvParameters;

  Serial.begin(115200);
  shell.attach(Serial); // attach to Serial

  shell.addCommand(F("angle"), setAngle);
  shell.addCommand(F("a"), setAngle);

  shell.addCommand(F("vib"), setVibrationStream);
  shell.addCommand(F("v"), setVibrationStream);

  while (!Serial) {
    vTaskDelay(1);
  }

  for (;;) {
    vTaskDelay(10);
    shell.executeIfInput();
  }
}
