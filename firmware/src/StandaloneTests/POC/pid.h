#ifndef PID_H__
#define PID_H__

#include <FastPID.h>
#include "util.hpp"

typedef void (*motor_callback)(int, int, int);
typedef double (*feedback_angle)();

double Input, Output;

double Kp = 0.1, Ki = 0.5, Kd = 0.1, Hz = 10;
int output_bits = 8;
bool output_signed = true;

FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

void PID_task(motor_callback callback, feedback_angle get_angle,
              double setpoint) {
  Input = get_angle();
  PRINT(Input);

  double gap = setpoint - Input; // distance away from setpoint
  PRINT(gap);

  int8_t Output = myPID.step(setpoint, Input);
  PRINT(Output);
//   PRINT(abs(Output));
//   PRINT(sgn<int8_t>(Output));

  callback(1, abs(Output), sgn<int8_t>(Output));
}

#endif