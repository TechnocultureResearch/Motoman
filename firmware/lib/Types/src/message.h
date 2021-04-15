#ifndef MESSAGE_H__
#define MESSAGE_H__

#include <stdint.h>

typedef enum {
  INT_ACCEL_DATA_GX,
  INT_ACCEL_DATA_GY,
  INT_ACCEL_DATA_GZ,
  INT_ACCEL_DATA_AX,
  INT_ACCEL_DATA_AY,
  INT_ACCEL_DATA_AZ,
  // INT_VERTICAL_ANGLE
  // INT_ROTATIONAL_ANGLE
  INT_CURRENT_DATA, // BOOL_CURRENT_OVERDRAW_FLAG
  INT_ENCODER_DATA, // INT_ENCODER_OFFSET
  INT_ENCODER_BUTTON_PRESSED,
  INT_MOTOR_SPEED_DATA,     // 0 <= speed <= 100
  INT_MOTOR_DIRECTION_DATA, // {-1, 1}
  NO_MESSAGE
} message_type_t;

static const char *message_string[] = {
    "GX", 
    "GY", 
    "GZ",
    "AX", 
    "AY", 
    "AZ",
    "C",
    "EN", 
    "BTN"
    "SPEED", 
    "DIR", 
    "NULL"
    };

typedef struct {
  message_type_t type;
  int16_t msg;
} serial_packet_t;

#define PRINT_MESSAGE(x, message)                                              \
  x.print(message_string[message.type]);                                         \
  x.print(": ");                                                         \
  x.println(message.msg);                                                       \

#endif // MESSAGE_H__