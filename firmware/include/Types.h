#ifndef TYPES_H_
#define TYPES_H_

typedef enum {
  COMMAND_MOVE_OUT = 1,
  COMMAND_MOVE_IN,
  COMMAND_STOP,
  COMMAND_IDLE
} Command;

enum Direction { OUTWARDS = -1, INWARDS = 1 };

enum State { MOVE = 1, STOP, IDLE };

typedef long Speed;

typedef long Freespace;

#endif // TYPES_H_
