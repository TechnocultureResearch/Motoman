#ifndef FEEDBACKMOTOR_H__
#define FEEDBACKMOTOR_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>

void FeedbackMotor_init(int16_t stack_size);
void TaskControlMotor(void *);

#endif // FEEDBACKMOTOR_H__