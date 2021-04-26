#include "Arduino.h"

#include "board.h"

#include <PID_v1.h>

#define RAD_TO_DEG(x) x *(180.0 / 3.14159)

#include <Wire.h>
#define SERIAL_1_BAUD_RATE 115200

const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// Define Variables we'll be connecting to
double Setpoint, Input, Output;

// Define the aggressive and conservative Tuning Parameters
double aggKp = 4, aggKi = 0.2, aggKd = 1;
double consKp = 1, consKi = 0.05, consKd = 0.25;

// Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, aggKp, aggKi, aggKp, DIRECT);

void getMotion6(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy,
                int16_t *gz) {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  *ax = Wire.read() << 8 |
        Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  *ay = Wire.read() << 8 |
        Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  *az = Wire.read() << 8 |
        Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  // Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42
  // (TEMP_OUT_L)
  *gx =
      Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  *gy =
      Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  *gz =
      Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

double getRollerAngle(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx,
                   int16_t *gy, int16_t *gz) {
  // getVerticalAngle
  int i = 0;
  long x = 0;
  long y = 0;
  long z = 0;

  int repeatCount = 5;

  //
  for (i = 0; i < repeatCount; ++i) {
    getMotion6(ax, ay, az, gx, gy, gz);

    x = x + *ax; //
    y = y + *ay; //
    z = z + *az; //
  }

  double avX = x / repeatCount;
  double avY = y / repeatCount;

  double verticalAngle = atan2(avX - 507, avY - 520);
  return RAD_TO_DEG(verticalAngle) + 20.0;
}

void move(int motor, int speed, int direction) {
  // Move specific motor at speed and direction
  // motor: 0 for B 1 for A
  // speed: 0 is off, and 255 is full speed
  // direction: 0 clockwise, 1 counter-clockwise

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

void PID_task() {
  Input = getRollerAngle(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ);
  Serial.println(Input);

  double gap = Setpoint - Input; // distance away from setpoint
  // if (abs(gap) < 10) { 
  //   // we're close to setpoint, use conservative tuning parameters
  //   myPID.SetTunings(consKp, consKi, consKd);
  // } else {
    // we're far from setpoint, use aggressive tuning parameters
    myPID.SetTunings(aggKp, aggKi, aggKd);
  // }

  myPID.Compute();
  Serial.println(Output);

  int dir = -1;
  if (gap < 0) { dir = 1; } 
  else if (gap > 0) { dir = 0; }
  // Serial.println(gap);
  // Serial.println(dir);
  move(1, (int) Output, dir);
  // move(1, 50, 0);
  // analogWrite(PIN_OUTPUT, Output);
}

void setup() {
  pinMode(MOTOR_DIGITAL_OUT_STBY, OUTPUT);

  pinMode(MOTOR_ANALOG_OUT_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_DIGITAL_OUT_DIR_PIN_A, OUTPUT);
  pinMode(MOTOR_DIGITAL_OUT_DIR_PIN_B, OUTPUT);

  // turn the PID on
  myPID.SetMode(AUTOMATIC);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(SERIAL_1_BAUD_RATE);

  // initialize the variables we're linked to
  // Input = getRollerAngle(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ) * RATIO;
  Setpoint = 80; // IMPORTANT
}

void loop() {
  PID_task();
}
