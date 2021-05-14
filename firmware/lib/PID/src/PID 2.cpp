#include "PID.h"
#include "message.h"
#include <FastPID.h>

// #define PIN_INPUT A0
// #define PIN_SETPOINT A1
// #define PIN_OUTPUT 9

QueueHandle_t PID_MotorQueue;
QueueHandle_t PID_PositionQueue;
QueueHandle_t PID_SerialOutQueue;
void TaskPIDController(void *);

float Kp = 0.1, Ki = 0.5, Kd = 0, Hz = 10;
int output_bits = 8;
bool output_signed = false;

;//(Kp, Ki, Kd, Hz, output_bits, output_signed);
FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

void PID_init(uint16_t stack_size, uint8_t priority, //
              QueueHandle_t motor_queue_handle,      //
              QueueHandle_t position_queue_handle,      //
              QueueHandle_t serial_out_queue_handle, //
              float Kp, float Ki, float Kd, float Hz) {
  xTaskCreate(
      TaskPIDController,        // Task function
      "Control a PID output based on feedback", // Task Name
      stack_size, // Stack size                             // Stack Size
      NULL,
      priority, // priority
      NULL);

  PID_MotorQueue = motor_queue_handle;
  PID_PositionQueue = position_queue_handle;
  PID_SerialOutQueue = serial_out_queue_handle;
}

void TaskPIDController(void *pvParameters) {
  (void)pvParameters;
  // int setpoint = analogRead(PIN_SETPOINT) / 2;
  // int feedback = analogRead(PIN_INPUT);
  // uint32_t before, after;
  // before = micros();
  // uint8_t output = myPID.step(setpoint, feedback);
  // after = micros();

  // analogWrite(PIN_OUTPUT, output);
  // Serial.print("runtime: ");
  // Serial.print(after - before);
  // Serial.print(" sp: ");
  // Serial.print(setpoint);
  // Serial.print(" fb: ");
  // Serial.print(feedback);
  // Serial.print(" out: ");
  // Serial.println(output);
  // delay(100);
}
