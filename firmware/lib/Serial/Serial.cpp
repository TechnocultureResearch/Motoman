#ifndef SERIAL_H
#define SERIAL_H

#define DEBUG

#include "Serial.h"
#include "Arduino.h"
#include "Types.h"

void setup_serial() { Serial.begin(115200); }

unsigned int commandIndex = 0;

void show_splash_screen() {
  Serial.println("\n=============================== DEBUG MODE "
                 "==============================");
  Serial.println("============================================================="
                 "============");

  Serial.println("Initial Mode: Move slider OUTWARDS [Code: 1]");

  Serial.println("Change Current Mode: by Sending the Corresponding Number.\n");
  Serial.println("\tMove Slider OUTWARDS ===> 1");
  Serial.println("\tMove Slider INWARDS  ===> 2");
  Serial.println("\tSTOP Slider          ===> 3");
  Serial.println("\tIDLE mode            ===> 4");

  Serial.println("\tSET MOTOR SPEED      ===> 5 to 70");

  Serial.println("============================================================="
                 "============");
}

void inline print_state(State motor_state, Direction motor_direction, Speed max_speed) {
  commandIndex++;
  Serial.println("\t");
  Serial.print(commandIndex);
  Serial.print(". ");
  switch (motor_state) {
  case MOVE:
    Serial.print("MOVING => ");
    if (motor_direction == OUTWARDS) {
      Serial.print("OUTWARDS");
    } else if (motor_direction == INWARDS) {
      Serial.print("INWARDS");
    }
    Serial.print(" @speed:");
    Serial.print(max_speed);
    break;
  case STOP:
    Serial.print("STOPPED.");
    break;
  case IDLE:
    Serial.print("IDLE");
    break;
  }
}

void process_command(const short input, State &state, Direction &direction, Speed &speed) {
  if (input == 0) {
    return;
  }

  if (input <= 4) {
    switch (input) {
    case 1:
      direction = OUTWARDS;
      state = MOVE;
      break;
    case 2:
      direction = INWARDS;
      state = MOVE;
      break;
    case 3:
      state = STOP;
      break;
    case 4:
      state = IDLE;
      break;
    default:
      break;
    }
  }

  if (input > 4) {
    speed = input * 100;
  }

#ifdef DEBUG
  print_state(state, direction, speed);
#endif
}

#endif
