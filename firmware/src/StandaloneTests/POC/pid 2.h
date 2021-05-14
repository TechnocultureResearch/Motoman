#ifndef PID_H__
#define PID_H__

#include <FastPID.h>

typedef void (*motor_callback)(int, int, int);

double Setpoint, Input, Output;

double Kp = 0.1, Ki = 0.5, Kd = 0, Hz = 10;
int output_bits = 8;
bool output_signed = true;

FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

void PID_task(motor_callback callback) {
  Input = getRollerAngle();
  // Serial.println(Input);

  double gap = Setpoint - Input; // distance away from setpoint

  // myPID.Compute();
  uint8_t Output = myPID.step(Setpoint, gap);
  // Serial.println(Output);

  int dir = -1;
  if (gap < 0) {
    dir = 1;
  } else if (gap > 0) {
    dir = 0;
  }
  
  callback(1, Output, dir);
}

#endif