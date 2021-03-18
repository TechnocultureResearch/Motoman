#ifndef MOTOR_GLOBALS_H_
#define MOTOR_GLOBALS_H_

#include "Types.h"

/* PARAMETERS */
#define ACCELERATION 30000
#define LONG_DURATION 800000UL
// #define LONG_DURATION 800000
//(500 * 16) * 1); // ==> 200 for the stepper's original
//steps/revolution, 16 is the microsteps and 1 is the number of turns
/* END PARAMETERS */

/* PINS */
#ifdef STM32
#define EN_PIN PB10  // LOW: Driver enabled. HIGH: Driver disabled
#define STEP_PIN PB7 // Step on rising edge
#define DIR_PIN PB6
#define LIMITSWITCH1_PIN PB4
#define LIMITSWITCH2_PIN PB3
#else
#define EN_PIN 10  // LOW: Driver enabled. HIGH: Driver disabled
#define STEP_PIN 7 // Step on rising edge
#define DIR_PIN 6
#define LIMITSWITCH1_PIN 2
#define LIMITSWITCH2_PIN 3
#endif
/* END PINS */

long freespace = -1;

#endif