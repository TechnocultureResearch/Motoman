#include "Arduino.h"
#include "board.h"

#include "motor.h"
#include "motion.h"
#include "pid.h"
#include "encoder.h"
#include "util.h"

// #define NODEBUG

#define SERIAL_1_BAUD_RATE 115200

void setup() {
  Serial.begin(SERIAL_1_BAUD_RATE);

  setup_motor();
  setup_mpu6050();
  setup_encoder();

  // Setpoint = 90; // IMPORTANT
  Setpoint = getPosition() + 90;
}


void mock_move(int motor, int speed, int dir) {
  PRINT("mock motor: move");
}

void loop() {
  // PID_task(&mock_move);
  PID_task(&move, &getRollerAngle);
  Setpoint = getPosition() + 90;
//   PRINT(Setpoint);
}