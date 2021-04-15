#include "InputEncoder.h"
#include "message.h"

#include <Arduino.h>


QueueHandle_t IE_SerialOutQueue;

typedef struct {
  uint8_t clk;
  uint8_t dt;
  uint8_t sw;
} device_pins_t;

device_pins_t device_pins;


/*
Global State
*/
int g_counter = 0;
int g_current_state_clk;
int g_last_state_clk;
int g_current_direction = 0;
uint32_t g_last_button_press = 0;


// Forward declarations
void TaskPollInputEncoder(void *);

void InputEncoder_init(uint16_t stack_size, uint8_t priority,
                       QueueHandle_t queue_handle,
                       uint8_t pin_clk, uint8_t pin_dt, uint8_t pin_sw) {
  xTaskCreate(TaskPollInputEncoder,      // Task function
            "Poll Input Encoder", // Task Name
            stack_size,                // Stack Size
            NULL,
            priority, // priority
            NULL);

  IE_SerialOutQueue = queue_handle;

  device_pins = {
    .clk = pin_clk,
    .dt = pin_dt,
    .sw = pin_sw
  };
}

void event_button_pressed() {
  Serial.println("Button pressed!");

  serial_packet_t packet = {
    .type = INT_ENCODER_BUTTON_PRESSED, 
    .msg = 1
  };

  xQueueSend(IE_SerialOutQueue, &packet, portMAX_DELAY);
}

void event_encoder_rotated(const int direction, const int counter) {

  // Serial.print("Encoder Position: ");
  // Serial.println(counter);
  if(direction == 0) {
    Serial.println("Error!");
    vTaskSuspendAll();
  }

  serial_packet_t packet = {.type = INT_ENCODER_DATA,
                            .msg = direction*counter};

  xQueueSend(IE_SerialOutQueue, &packet, portMAX_DELAY);
}

void TaskPollInputEncoder(void *pvParameters) {
  (void)pvParameters;

  // Set encoder pins as inputs
  pinMode(device_pins.clk, INPUT);
  pinMode(device_pins.dt, INPUT);
  pinMode(device_pins.sw, INPUT_PULLUP);

  // Read the initial state of device_pins.dt
  g_last_state_clk = digitalRead(device_pins.clk);

  for (;;) {
    // Read the current state of device_pins.dt
    g_current_state_clk = digitalRead(device_pins.dt);

    // If last and current state of device_pins.dt are different, then
    // pulse occurred React to only 1 state change to avoid double count
    if (g_current_state_clk != g_last_state_clk && g_current_state_clk == 1) {

      // If the device_pins.dt state is different than the
      // device_pins.dt state then the encoder is rotating CCW so
      // decrement
      if (digitalRead(device_pins.dt) != g_current_state_clk) {
        g_counter--;
        g_current_direction = 1;
      } else {
        // Encoder is rotating CW so increment
        g_counter++;
        g_current_direction = -1;
      }

      event_encoder_rotated(g_current_direction, g_counter);
    }

    // Remember last device_pins.dt state
    g_last_state_clk = g_current_state_clk;

    // Read the button state
    int _button_state = digitalRead(device_pins.sw);

    // If we detect LOW signal, button is pressed
    if (_button_state == LOW) {
      // if 50ms have passed since last LOW pulse, it means that the
      // button has been pressed, released and pressed again
      if (millis() - g_last_button_press > 50) {
        event_button_pressed();
      }

      // Remember last button press event
      g_last_button_press = millis();
    }

    vTaskDelay(1);
  }
}