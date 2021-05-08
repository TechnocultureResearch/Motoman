#include <Arduino.h>

#include "Filter.h"

#define ADC_PIN 3
#define PWM_PIN 7

#define INITIAL_DELAY 20000

unsigned long initial_time = 0;

ExponentialFilter<float> FilteredSignal(1, 0); // the <float> makes a filter for float numbers: 20 is the weight (20 => 20%), 0 is the initial value of the filter

int smooth(){
  int value = 0;
  int numReadings = 25;

  for (int i = 0; i < numReadings; i++){
    value = value + analogRead(ADC_PIN); // Read light sensor data
    delay(1); // 1ms pause adds more stability between reads
  }
  value = value / numReadings; // Take an average of all the readings

  FilteredSignal.Filter(value);
  return FilteredSignal.Current();
}

void setup(){
  Serial.begin(115200);
  
  pinMode(ADC_PIN, INPUT);
  pinMode(PWM_PIN, OUTPUT);
  //  analogReference(INTERNAL);            
  // analogReadResolution(12);
  
  analogWrite(PWM_PIN, 255);

  initial_time = millis();
}

void loop(){ 
  if( millis() - initial_time > INITIAL_DELAY ){ Serial.println(smooth()); }
  else { smooth(); }
}
