#include "Globals.h"

/* LIBRARY INCLUDES */
#include <AccelStepper.h>
#include <TMC2208Stepper.h>

/* END LIBRARY INCLUDES */

/* GLOBAL VARIABLES */
TMC2208Stepper driver = TMC2208Stepper(&Serial);
AccelStepper stepper(1, STEP_PIN, DIR_PIN);


inline void setup_motor_params(const long speed, const long acc){
  stepper.setMaxSpeed(speed);
  stepper.setAcceleration(acc);
}

void setup_driver(){
  digitalWrite(EN_PIN, HIGH);
  
  driver.pdn_disable(1);              // Use PDN/UART pin for communication
  // driver.mstep_reg_select(1);   // TRYING TO SET THE MICROSTEPS LIKE THIS, BUT TO NO AVAIL!!
  driver.microsteps(0);
  driver.I_scale_analog(0);           // Adjust current from the registers
  driver.rms_current(1000);            // Set driver current 500mA
  driver.toff(0x2);               // Enable driver
  
  digitalWrite(EN_PIN, LOW); // Enable driver
}

void limitswitch_ISR() {
  if (freespace >= 1000) {
    freespace = -1;
    // process_command(COMMAND_STOP, motor_state, motor_direction, max_speed);
  }
}

void setup_interrupts() {
  attachInterrupt(digitalPinToInterrupt(LIMITSWITCH1_PIN), limitswitch_ISR,
                  FALLING);
  attachInterrupt(digitalPinToInterrupt(LIMITSWITCH2_PIN), limitswitch_ISR,
                  FALLING);
}
