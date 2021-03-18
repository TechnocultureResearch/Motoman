#ifndef TYPES_H_
#define TYPES_H_

typedef enum {
  COMMAND_MOVE_OUT = 1,
  COMMAND_MOVE_IN,
  COMMAND_STOP,
  COMMAND_IDLE
} Command;

typedef enum { OUTWARDS = -1, INWARDS = 1 } Direction;

typedef enum { MOVE = 1, STOP, IDLE } State;

typedef long Speed;

typedef long Freespace;

#endif // TYPES_H_
