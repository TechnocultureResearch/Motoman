#ifndef FIRMWARE_H__
#define FIRMWARE_H__


#include "board.h"
#include "message.h"
#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <queue.h>

#ifdef DEBUG
#include "avr8-stub.h"
#endif

#include "CurrentSensor.h"
#include "DOF6.h"
#include "FeedbackMotor.h"
#include "OffsetEncoder.h"
#include "PID.h"
#include "SerialWriter.h"

// #include "SerialShell.h"

#define STACK_SIZE_SMALL  128
#define STACK_SIZE_LARGE  1024
#define PRIORITY_LOW      1
#define PRIORITY_MID      2
#define PRIORITY_HIGH     3

#define QUEUE_SIZE_SMALL  10


#endif