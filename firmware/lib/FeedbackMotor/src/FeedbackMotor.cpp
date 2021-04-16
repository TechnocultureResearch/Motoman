#include "FeedbackMotor.h"

void TaskControlMotor(void *);

void FeedbackMotor_init(uint16_t stack_size, uint8_t priority,
                        QueueHandle_t motor_queue_handle) {
  xTaskCreate(TaskControlMotor,                       // Task function
              "Control speed and direction of motor", // Task Name
              stack_size,                             // Stack Size
              NULL,
              priority, // priority
              NULL);
}

void TaskControlMotor(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    vTaskDelay(1);
  }
}
