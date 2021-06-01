#ifndef BOARD_H__
#define BOARD_H__

/* Common */
#define SERIAL_1_BAUD_RATE 115200 /* Duplication in Platformio.ini */
/* End Common */

/*
  Mega
*/
#ifdef BOARD_MEGA
// Rotary Encoder 1(RE1) pinout
  #define RE1_ENCODER_DIGITAL_OUT_CLK 45
  #define RE1_ENCODER_DIGITAL_OUT_DT 43
  #define RE1_ENCODER_DIGITAL_OUT_SW 41

// Rotary Encoder 2(RE2) pinout
  #define RE2_ENCODER_DIGITAL_OUT_CLK 27
  #define RE2_ENCODER_DIGITAL_OUT_DT 25
  #define RE2_ENCODER_DIGITAL_OUT_SW 23


// Motor 5(M5) pinout
  #define M5_MOTOR_DIGITAL_OUT_STBY 22     /* TB6612FNG */
  #define M5_MOTOR_ANALOG_OUT_SPEED_PIN  28  /* PWMA on TB6612FNG */
  #define M5_MOTOR_DIGITAL_OUT_DIR_PIN_A 24 /* AIN1 on TB6612FNG */
  #define M5_MOTOR_DIGITAL_OUT_DIR_PIN_B 26 /* AIN2 on TB6612FNG */

// Motor 3(M3) & Motor 4(M4) pinout
  #define MOTOR_DIGITAL_OUT_STBY 36     /* TB6612FNG */
  #define M3_MOTOR_ANALOG_OUT_SPEED_PIN  42  /* PWMA on TB6612FNG */
  #define M3_MOTOR_DIGITAL_OUT_DIR_PIN_A 38 /* AIN1 on TB6612FNG */
  #define M3_MOTOR_DIGITAL_OUT_DIR_PIN_B 40 /* AIN2 on TB6612FNG */
  #define M4_MOTOR_ANALOG_OUT_SPEED_PIN  30  /* PWMB on TB6612FNG */
  #define M4_MOTOR_DIGITAL_OUT_DIR_PIN_A 34 /* BIN1 on TB6612FNG */
  #define M4_MOTOR_DIGITAL_OUT_DIR_PIN_B 32 /* BIN2 on TB6612FNG */


// Load Cell pinout
  #define LOAD_CELL_DIGITAL_OUT_DT 9
  #define LOAD_CELL_DIGITAL_OUT_SCK 8


// Absulute Encoder pinout
  #define AB_ENCODER_DIGITAL_OUT_CHIP_SELECT 2  /* CSB on AMT203-V */


  #define MPU6050_SCL_PIN A5 /* Not used directly */
  #define MPU6050_SDA_PIN A4 /* Not used directly */
  #define MPU6050_INT_PIN    /* Unused */
  
  // // Current Sensor 5(CM5) pinout
  //   #define ACS712_ANALOG_IN_PIN A11
  
  // // Current Sensor 4(CM4) pinout
  //   #define ACS712_ANALOG_IN_PIN A12
  
  // // Current Sensor 3(CM3) pinout
  //   #define ACS712_ANALOG_IN_PIN A13
#endif


#endif // BOARD_H__