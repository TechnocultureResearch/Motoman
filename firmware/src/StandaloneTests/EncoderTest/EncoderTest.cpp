#include<Arduino.h>

#include "board.h"
 
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;
 
void setup() {
  
  // Set encoder pins as inputs
  pinMode(ENCODER_DIGITAL_OUT_CLK,INPUT);
  pinMode(ENCODER_DIGITAL_OUT_DT,INPUT);
  pinMode(ENCODER_DIGITAL_OUT_SW, INPUT_PULLUP);
 
  // Setup Serial Monitor
  Serial.begin(9600);
 
  // Read the initial state of ENCODER_DIGITAL_OUT_CLK
  lastStateCLK = digitalRead(ENCODER_DIGITAL_OUT_CLK);
}
 
void loop() {
  
  // Read the current state of ENCODER_DIGITAL_OUT_CLK
  currentStateCLK = digitalRead(ENCODER_DIGITAL_OUT_CLK);
 
  // If last and current state of ENCODER_DIGITAL_OUT_CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
 
    // If the ENCODER_DIGITAL_OUT_DT state is different than the ENCODER_DIGITAL_OUT_CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ENCODER_DIGITAL_OUT_DT) != currentStateCLK) {
      counter --;
      currentDir ="CCW";
    } else {
      // Encoder is rotating CW so increment
      counter ++;
      currentDir ="CW";
    }
 
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }
 
  // Remember last ENCODER_DIGITAL_OUT_CLK state
  lastStateCLK = currentStateCLK;
 
  // Read the button state
  int btnState = digitalRead(ENCODER_DIGITAL_OUT_SW);
 
  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
    }
 
    // Remember last button press event
    lastButtonPress = millis();
  }
 
  // Put in a slight delay to help debounce the reading
  delay(1);
}