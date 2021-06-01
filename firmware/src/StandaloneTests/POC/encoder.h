#ifndef ENCODER_H___
#define ENCODER_H___

#include <Arduino.h>

#define TICK_FACTOR 5

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";

void setup_encoder() {
  // Set encoder pins as inputs
  pinMode(RE1_ENCODER_DIGITAL_OUT_CLK, INPUT);
  pinMode(RE1_ENCODER_DIGITAL_OUT_DT, INPUT);
  pinMode(RE1_ENCODER_DIGITAL_OUT_SW, INPUT_PULLUP);

  // Read the initial state of ENCODER_DIGITAL_OUT_CLK
  lastStateCLK = digitalRead(RE1_ENCODER_DIGITAL_OUT_CLK);
}

int getPosition() {
  // Read the current state of RE1_ENCODER_DIGITAL_OUT_CLK
  currentStateCLK = digitalRead(RE1_ENCODER_DIGITAL_OUT_CLK);

  // If last and current state of RE1_ENCODER_DIGITAL_OUT_CLK are different, then
  // pulse occurred React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {

    // If the ENCODER_DIGITAL_OUT_DT state is different than the
    // RE1_ENCODER_DIGITAL_OUT_CLK state then the encoder is rotating CCW so
    // decrement
    if (digitalRead(RE1_ENCODER_DIGITAL_OUT_DT) != currentStateCLK) {
      counter--;
      currentDir = "CC";
    } else {
      // Encoder is rotating CW so increment
      counter++;
      currentDir = "C";
    }
  }

  // Remember last RE1_ENCODER_DIGITAL_OUT_CLK state
  lastStateCLK = currentStateCLK;

  return counter * TICK_FACTOR;
}

#endif