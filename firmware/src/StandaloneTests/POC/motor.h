#ifndef MOTOR_H__
#define MOTOR_H__

#define CURRENT_THRESHOLD 900

void move(int motor, int speed, int direction) {
  // Move specific motor at speed and direction
  // motor: 0 for B 1 for A
  // speed: 0 is off, and 255 is full speed
  // direction: 0 clockwise, 1 counter-clockwise

  if (analogRead(ACS712_ANALOG_IN_PIN) > CURRENT_THRESHOLD) {
    analogWrite(MOTOR_ANALOG_OUT_SPEED_PIN, 0);
    return;
  }

    // Serial.println(speed);
  digitalWrite(MOTOR_DIGITAL_OUT_STBY, HIGH); // disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 1) {
    digitalWrite(MOTOR_DIGITAL_OUT_DIR_PIN_A, inPin1);
    digitalWrite(MOTOR_DIGITAL_OUT_DIR_PIN_B, inPin2);
    analogWrite(MOTOR_ANALOG_OUT_SPEED_PIN, speed);
  } else {
    //    digitalWrite(BIN1, inPin1);
    //    digitalWrite(BIN2, inPin2);
    //    analogWrite(PWMB, speed);
  }
}

void setup_motor() {
  pinMode(MOTOR_DIGITAL_OUT_STBY, OUTPUT);

  pinMode(MOTOR_ANALOG_OUT_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_DIGITAL_OUT_DIR_PIN_A, OUTPUT);
  pinMode(MOTOR_DIGITAL_OUT_DIR_PIN_B, OUTPUT);
}

#endif