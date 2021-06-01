#ifndef MOTOR_H__
#define MOTOR_H__

#include <Arduino.h>

#include "board.h"

// #define CURRENT_THRESHOLD 900

void move(uint8_t motor, uint8_t speed, int8_t direction) {
    // Serial.println(speed);
    digitalWrite(MOTOR_DIGITAL_OUT_STBY, HIGH); // disable standby
    digitalWrite(M5_MOTOR_DIGITAL_OUT_STBY, HIGH); // disable standby

    boolean inPin1 = LOW;
    boolean inPin2 = HIGH;

    if (direction == 1) {
      inPin1 = HIGH;
      inPin2 = LOW;
  }

  if (motor == 0) {
    digitalWrite(M5_MOTOR_DIGITAL_OUT_DIR_PIN_A, inPin1);
    digitalWrite(M5_MOTOR_DIGITAL_OUT_DIR_PIN_B, inPin2);
    analogWrite(M5_MOTOR_ANALOG_OUT_SPEED_PIN, speed);
  } else if(motor == 1) {
    digitalWrite(M3_MOTOR_DIGITAL_OUT_DIR_PIN_A, inPin1);
    digitalWrite(M3_MOTOR_DIGITAL_OUT_DIR_PIN_B, inPin2);
    analogWrite(M3_MOTOR_ANALOG_OUT_SPEED_PIN, speed);
  } else if (motor == 2) {
    digitalWrite(M4_MOTOR_DIGITAL_OUT_DIR_PIN_A, inPin1);
    digitalWrite(M4_MOTOR_DIGITAL_OUT_DIR_PIN_B, inPin2);
    analogWrite(M4_MOTOR_ANALOG_OUT_SPEED_PIN, speed);
  }
}

void setup_motor() {
  pinMode(MOTOR_DIGITAL_OUT_STBY, OUTPUT);
  pinMode(M5_MOTOR_DIGITAL_OUT_STBY, OUTPUT);

  pinMode(M3_MOTOR_ANALOG_OUT_SPEED_PIN, OUTPUT);
  pinMode(M3_MOTOR_DIGITAL_OUT_DIR_PIN_A, OUTPUT);
  pinMode(M3_MOTOR_DIGITAL_OUT_DIR_PIN_B, OUTPUT);

  pinMode(M4_MOTOR_ANALOG_OUT_SPEED_PIN, OUTPUT);
  pinMode(M4_MOTOR_DIGITAL_OUT_DIR_PIN_A, OUTPUT);
  pinMode(M4_MOTOR_DIGITAL_OUT_DIR_PIN_B, OUTPUT);

  pinMode(M5_MOTOR_ANALOG_OUT_SPEED_PIN, OUTPUT);
  pinMode(M5_MOTOR_DIGITAL_OUT_DIR_PIN_A, OUTPUT);
  pinMode(M5_MOTOR_DIGITAL_OUT_DIR_PIN_B, OUTPUT);
}

#endif


  // Move specific motor at speed and direction
  // motor: 0 for B 1 for A
  // speed: 0 is off, and 255 is full speed
  // direction: 0 clockwise, 1 counter-clockwise

//   if (analogRead(ACS712_ANALOG_IN_PIN) > CURRENT_THRESHOLD) {
    // analogWrite(MOTOR_ANALOG_OUT_SPEED_PIN, 0);
    // return;
//   }