#include <Arduino.h>

#include "board.h"

const int LDR = ACS712_ANALOG_IN_PIN;
int input_val = 0;

void setup()
{
  Serial.begin(SERIAL_1_BAUD_RATE);
}

void loop()
{
  input_val = analogRead(LDR);
  Serial.print("LDR Value is: ");
  Serial.println(input_val);
  delay(100);
}