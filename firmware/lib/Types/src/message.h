#ifndef MESSAGE_H__
#define MESSAGE_H__

#include <stdint.h>

typedef enum {
  INT_ROLLER_ANGLE,
  INT_TILT_ANGLE,

  BOOL_CURRENT_OVERDRAW_FLAG,

  INT_ENCODER_OFFSET,
  BOOL_ENCODER_BUTTON_PRESSED,

  INT_MOTOR_SPEED,     // 0 <= speed <= 100
  INT_MOTOR_DIRECTION, // {-1, 1}

  NO_MESSAGE
} message_type_t;

static const char *message_string[] = {
    "RA",
    "TA",

    "COD",

    "EO",
    "BP",

    "MS",
    "MD",

    "NULL"};


typedef struct {
  message_type_t type;
  int16_t msg;
} serial_packet_t;


#define PRINT_MESSAGE(x, message)                                              \
  x.print(message_string[message.type]);                                         \
  x.print(": ");                                                         \
  x.println(message.msg);                                                       \

#endif // MESSAGE_H__