#include <Arduino.h>
#include "Screen.h"

Screen screen = Screen(false);

void test(){
  Serial.println("Hello World");
}

void setup() {
  Serial.begin(9600);
  screen.setup();
}

void loop() {
  screen.touchFlow(test);
  screen.drawFlow(0, 0, 0, 0, 0, 0);
}
