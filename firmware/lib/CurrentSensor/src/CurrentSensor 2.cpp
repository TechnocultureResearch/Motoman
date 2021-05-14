#include "CurrentSensor.h"
#include <Arduino.h>

#include "message.h"

QueueHandle_t CS_SerialOutQueue;
QueueHandle_t CS_MotorOutQueue;
uint8_t device_pin;

void TaskPollCurrentSense(void *);

void CurrentSensor_init(uint16_t stack_size, uint8_t priority, //
                        QueueHandle_t motor_queue_handle,   //
                        QueueHandle_t serial_out_queue_handle, //
                        uint8_t pin) {
  xTaskCreate(TaskPollCurrentSense,      // Task function
              "Analog Read from ACS712", // Task Name
              stack_size,                // Stack Size
              NULL,
              priority, // priority
              NULL);

  CS_MotorOutQueue = motor_queue_handle;
  CS_SerialOutQueue = serial_out_queue_handle;
  device_pin = pin;
}

void TaskPollCurrentSense(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    int16_t sensorValue = analogRead(device_pin);

    serial_packet_t packet = {.type=BOOL_CURRENT_OVERDRAW_FLAG, .msg=sensorValue};

    xQueueSend(CS_SerialOutQueue, &packet, portMAX_DELAY);

    vTaskDelay(1);
  }
}