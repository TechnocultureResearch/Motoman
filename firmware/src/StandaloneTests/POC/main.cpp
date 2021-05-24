#include "Arduino.h"
#include "board.h"

#include "motor.h"
#include "motion.h"
#include "pid.h"
#include "encoder.h"

#define SERIAL_1_BAUD_RATE 115200

void setup() {
  Serial.begin(SERIAL_1_BAUD_RATE);

  setup_motor();
  setup_mpu6050();
  setup_encoder();

  // Setpoint = 90; // IMPORTANT
  Setpoint = getPosition() + 90;
  // Serial.println(getPosition());
}


void mock_move(int motor, int speed, int dir) {
  Serial.println("mock motor: move");
}

void loop() {
  // PID_task(&mock_move);
  PID_task(&move);
  Setpoint = getPosition() + 90;
  Serial.println(Setpoint);
}