#ifndef BOARD_H__
#define BOARD_H__

/*
  ESP32
*/
// #ifdef ARDUINO_FREERTOS
//   #define MPU6050_SCL_PIN 0
//   #define MPU6050_SDA_PIN 0
//   #define MPU6050_INT_PIN 0
//   #define ACS712_ANALOG_IN_PIN 0
//   #define MOTOR_ANALOG_OUT_PIN 0
//   #define RTOS FREERTOS
// #endif

/*
  Nano
*/
#ifdef BOARD_NANO
  #define MPU6050_SCL_PIN 0
  #define MPU6050_SDA_PIN 0
  #define MPU6050_INT_PIN 0
  #define ACS712_ANALOG_IN_PIN A0
  #define MOTOR_ANALOG_OUT_SPEED_PIN 0
  #define MOTOR_DIGITAL_OUT_DIR_PIN 0
#endif

#endif // BOARD_H__