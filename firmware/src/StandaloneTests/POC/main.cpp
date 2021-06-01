#include "Arduino.h"
#include "board.h"

#include "motor.h"
#include "absEncoder.h"
#include "encoder.h"
#include "pid.h"
#include "util.hpp"

// #define NODEBUG

#define SERIAL_1_BAUD_RATE 115200

double Setpoint = 0;

void setup() {
  Serial.begin(SERIAL_1_BAUD_RATE);

  setup_motor();
  setup_encoder();
  setup_absEncoder();

//   Setpoint = 0; // IMPORTANT

move(2, 100, 1);
}

void loop() {
//   Setpoint = 100 + getPosition();
  PID_task(&move, &getRotaryAngle, 20);
  //   PRINT(Setpoint);
}
