#include <Arduino.h>
#include "Screen.h"

bool Cooler_State;
bool oldCooler_State;
bool btn_cooler;

Screen screen = Screen(false);

void test(){
  Serial.println("Hello World");
}

void set_Cooler(bool state){
  oldCooler_State = Cooler_State;
  Cooler_State = (state || btn_cooler);
  screen.setCoolerState(Cooler_State, oldCooler_State);
}

void switch_CoolerState() {
  btn_cooler = !btn_cooler;
  set_Cooler(btn_cooler);
}

void setup() {
  Serial.begin(9600);

  Cooler_State = false;
  oldCooler_State = false;
  btn_cooler = false;

  screen.setup();
}

void loop() {
  screen.touchFlow(switch_CoolerState);
  screen.drawFlow(0, 0, 0, 0, 0, 0);
}
