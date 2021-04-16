#ifndef INPUT_ENCODER_H__
#define INPUT_ENCODER_H__

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdint.h>

void OffsetEncoder_init(uint16_t stack_size, uint8_t priority, //  
                        QueueHandle_t position_queue_handle, // 
                        QueueHandle_t serial_out_queue_handle, // 
                        uint8_t pin_clk,
                        uint8_t pin_dt, uint8_t pin_sw);

#endif // INPUT_ENCODER_H__