#ifndef MESSAGE_H__
#define MESSAGE_H__

#include <stdint.h>

typedef enum {
  INT_ACCEL_DATA_GX,
  INT_ACCEL_DATA_GY,
  INT_ACCEL_DATA_GZ,
  INT_ACCEL_DATA_AX,
  INT_ACCEL_DATA_AY,
  INT_CURRENT_DATA,
  INT_ENCODER_DATA,
  INT_MOTOR_SPEED_DATA,
  INT_MOTOR_DIRECTION_DATA,
  NO_MESSAGE
} message_type_t;

static const char *message_string[] = {
    "GX", 
    "GY", 
    "GZ",
    "AX", 
    "AY", 
    "C",
    "EN",  
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