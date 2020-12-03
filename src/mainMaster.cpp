#include <Arduino.h>
#include <Wire.h>

// I have changed the BUFFER_LENGTH from 32 to 200

#include "Screen.h"


bool Cooler_State;
bool oldCooler_State;
bool btn_cooler;

char buffer[400];
boolean receiveFlag = false;

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
  // Wire.beginTransmission(9); // The slave i2c address should be configured on 9;
  // Wire.write(btn_cooler ? 1 : 0);
  // Wire.endTransmission();
}

void requestInfo(byte option){
  // Serial.print("Estou pedindo uma informação com opção: ");
  // Serial.println(option);
  Wire.beginTransmission(9);
  Wire.write(option);
  Wire.endTransmission();
  // Serial.println("Envio de dados finalizado.");
}

void handleResponseWire(int howMany){
  // char buf[200];
  // for (int i = 0; i < howMany; i++)
  // {
  //   buf[i] = Wire.read();
  //   // Serial.println(buffer[i]);
  // }
  // Serial.println(buf);
  // Serial.print("SLAVE SENT DATA: ");
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  // Wire.readBytes(buffer, howMany);
  // receiveFlag = true;
  // Serial.println(buffer);
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
