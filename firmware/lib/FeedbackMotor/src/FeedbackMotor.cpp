#include "FeedbackMotor.h"

void FeedbackMotor_init(int16_t stack_size){
  xTaskCreate(TaskControlMotor,                       // Task function
              "Control speed and direction of motor", // Task Name
              stack_size,                             // Stack Size
              NULL,
              1, // priority
              NULL);
}

void TaskControlMotor(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    vTaskDelay(1);
  }
}
