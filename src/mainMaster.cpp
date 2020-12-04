#include <Arduino.h>
#include <Wire.h>
// I have changed the BUFFER_LENGTH from 32 to 200

#include "Screen.h"
#include "Message.h"

bool Cooler_State;
bool oldCooler_State;
bool btn_cooler;

char buffer[200];
Message messenger = Message();
Screen screen = Screen(false);


void set_Cooler(bool state){
  oldCooler_State = Cooler_State;
  Cooler_State = (state || btn_cooler);
  screen.setCoolerState(Cooler_State, oldCooler_State);
}

void switch_CoolerState() {
  btn_cooler = !btn_cooler;
  set_Cooler(btn_cooler);
}

void requestInfo(byte option){
  Wire.beginTransmission(9);
  Wire.write(option);
  Wire.endTransmission();
}

void handleResponseWire(int howMany){
  int i = 0;
  while (1 < Wire.available() && i<200) { // loop through all but the last
    buffer[i] = Wire.read(); // receive byte as a character
    Serial.print(buffer[i]);         // print the character
    i++;
  }
  buffer[i] = Wire.read();    // receive byte as an integer
  Serial.println(buffer[i]);         // print the integer
  messenger.deserializeData(buffer);
}

void setup() {
  Serial.begin(9600);

  Wire.begin(4);
  Wire.onReceive(handleResponseWire);

  Cooler_State = false;
  oldCooler_State = false;
  btn_cooler = false;

  screen.setup();

}

void loop() {
  screen.touchFlow(switch_CoolerState, requestInfo);
  screen.drawFlow();
}
