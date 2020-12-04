#include <Arduino.h>
#include "Message.h"

Message::Message(){

}

String Message::serializeData(
  int distance1, int distance2, int distance3, int distance4,
  int temperature, int humidity, bool coolerState)
{
  const int capacity = JSON_ARRAY_SIZE(6) + 5*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(1);
  JsonObject distanceSensor_1 = this->doc.createNestedObject();
  distanceSensor_1["id"] = "d1";
  distanceSensor_1["v"] = distance1;
  JsonObject distanceSensor_2 = this->doc.createNestedObject();
  distanceSensor_2["id"] = "d2";
  distanceSensor_2["v"] = distance2;
  JsonObject distanceSensor_3 = this->doc.createNestedObject();
  distanceSensor_3["id"] = "d3";
  distanceSensor_3["v"] = distance3;
  JsonObject distanceSensor_4 = this->doc.createNestedObject();
  distanceSensor_4["id"] = "d4";
  distanceSensor_4["v"] = distance4;

  JsonObject temperatureSensor = this->doc.createNestedObject();
  temperatureSensor["t"] = temperature;
  temperatureSensor["h"] = humidity;

  JsonObject coolerState_ = this->doc.createNestedObject();
  coolerState_["cs"] = coolerState;


  char output[200] = "";
  serializeJson(this->doc, output);
  return output;
}

void Message::deserializeData(char jsonSerialized[]){
  deserializeJson(this->doc, jsonSerialized);
}
