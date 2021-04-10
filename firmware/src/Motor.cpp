#include <Arduino.h>
#include "Serial.h"
#include "Globals.h"

void setup(){
  setup_serial();

#ifdef DEBUG
  show_splash_screen();
  PROCESS(COMMAND_MOVE_OUT);
#else
  PROCESS(COMMAND_STOP);
#endif
}

void loop() {
  if (Serial.available()) {
    PROCESS(Serial.parseInt());
  }

  REFRESH();
}
