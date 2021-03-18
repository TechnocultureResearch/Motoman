#ifndef MOTOR_COTROLLER_H_
#define MOTOR_COTROLLER_H_

#include "Types.h"

void setup_motor(Speed speed);
void state_machine(State, Speed, Direction);

#endif