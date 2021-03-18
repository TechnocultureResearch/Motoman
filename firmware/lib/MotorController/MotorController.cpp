#include "MotorController.h"
#include "Types.h"
#include "Globals.h"
#include "MotorSetup.h"

void setup_motor(Speed speed) {
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  setup_driver();
  setup_motor_params(speed, ACCELERATION); // <== Setup Max Speed and Acceleration
  setup_interrupts();
}

void Move(Speed speed, Direction direction) {
  stepper.setMaxSpeed(speed);
  stepper.moveTo((long)direction * LONG_DURATION);
  stepper.run();
  // freespace++;
}

void Stop() {
  stepper.stop();
} // Serial.println((long)motor_direction * (long)LONG_DURATION); }

void state_machine(State state, Speed speed, Direction direction) {
  switch (state) {
  case STOP:
    Stop();
    break;
  case MOVE:
    Move(speed, direction);
    break;
  case IDLE:
    break;
  default:
    break;
  }
}
