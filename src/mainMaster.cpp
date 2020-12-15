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

void set_Cooler(bool state)
{
  screen.setCoolerState(state);
}

void switch_CoolerState()
{
  btn_cooler = !btn_cooler;
  set_Cooler(btn_cooler);
}

void requestInfo(byte option)
{
  Wire.beginTransmission(12);
  Wire.write(option);
  Wire.endTransmission();
}

void setSensorsData(uint16_t d1, uint16_t d2, uint16_t d3, uint16_t d4, float temperature, float humidity, bool cooler_state)
{
  screen.setCoolerState(cooler_state);
  screen.setHum_DHT(humidity);
  screen.setTempC_DHT(temperature);
  screen.setMeasure_LCo_now(d1);
  screen.setMeasure_LCi_now(d2);
  screen.setMeasure_Pri_now(d3);
  screen.setMeasure_Cam_now(d4);
}

void handleResponseWire(int howMany)
{
  int i = 0;
  while (1 < Wire.available() && i < 200)
  {                          // loop through all but the last
    buffer[i] = Wire.read(); // receive byte as a character
    Serial.print(buffer[i]); // print the character
    i++;
  }
  buffer[i] = Wire.read();   // receive byte as an integer
  Serial.println(buffer[i]); // print the integer
  messenger.deserializeData(buffer, setSensorsData);
}

void setup()
{
  Serial.begin(9600);

  Cooler_State = false;
  oldCooler_State = false;
  btn_cooler = false;
  Serial.println("Configurando tela");
  screen.setup();

  Wire.begin(4);
  Wire.onReceive(handleResponseWire);
}

void loop()
{
  screen.touchFlow(switch_CoolerState, requestInfo);
  screen.drawFlow();
}
