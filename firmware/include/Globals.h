#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "Types.h"

#define DEBUG
//#define STM32

#define PROCESS(x) process_command(x, motor_state, motor_direction, max_speed);
#define REFRESH() state_machine(motor_state, max_speed, motor_direction);

// STATE -----------------------
Speed max_speed             = 1000;
State motor_state           = STOP;
Direction motor_direction   = OUTWARDS;
// -----------------------------

#define ACCELERATION 30000

#endif
