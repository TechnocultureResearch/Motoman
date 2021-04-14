#ifndef BOARD_H__
#define BOARD_H__

/* Common */
#define SERIAL_1_BAUD_RATE 115200 /* Duplication in Platformio.ini */
/* End Common */


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
  #define MPU6050_SCL_PIN A5  /* Not used directly */
  #define MPU6050_SDA_PIN A4  /* Not used directly */
  #define MPU6050_INT_PIN     /* Unused */

  #define ACS712_ANALOG_IN_PIN A0
  
  #define ENCODER_DIGITAL_OUT_CLK 2
  #define ENCODER_DIGITAL_OUT_DT 3
  #define ENCODER_DIGITAL_OUT_SW 4

  #define MOTOR_DIGITAL_OUT_STBY 10     /* TB6612fng */
  #define MOTOR_ANALOG_OUT_SPEED_PIN 6  /* PWMA on TB6612fng */
  #define MOTOR_DIGITAL_OUT_DIR_PIN_A 9 /* AIN1 on TB6612fng */
  #define MOTOR_DIGITAL_OUT_DIR_PIN_B 8 /* AIN2 on TB6612fng */
#endif

#endif // BOARD_H__