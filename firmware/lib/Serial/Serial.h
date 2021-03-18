#ifndef SERIAL_H
#define SERIAL_H

#include "Types.h"

void setup_serial();
void show_splash_screen();
void process_command(const short input, State &state, Direction &direction, Speed &speed);
void print_state(State motor_state, Direction motor_direction, Speed max_speed);

#endif
