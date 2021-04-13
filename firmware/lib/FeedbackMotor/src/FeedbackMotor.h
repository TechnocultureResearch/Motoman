#ifndef FEEDBACKMOTOR_H__
#define FEEDBACKMOTOR_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>

void FeedbackMotor_init(uint16_t stack_size, uint8_t priority);

#endif // FEEDBACKMOTOR_H__