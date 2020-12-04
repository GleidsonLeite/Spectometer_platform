#include <Arduino.h>
#include "Message.h"

Message::Message(){

}



String Message::serializeData(
  uint16_t distance1, uint16_t distance2, uint16_t distance3, uint16_t distance4,
  float temperature, float humidity, bool coolerState)
{
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
void Message::deserializeData(
  char jsonSerialized[],
  void (*setValues)(uint16_t d1, uint16_t d2, uint16_t d3, uint16_t d4, float temperature, float humidity, bool cooler_state)
){
  DeserializationError err = deserializeJson(this->doc, jsonSerialized);
  if(err){
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.c_str());
  }else{
    Serial.println("conversion success");
  }
  JsonArray array = this->doc.as<JsonArray>();
  float distance_1 = array[0]["v"].as<uint16_t>();
  float distance_2 = array[1]["v"].as<uint16_t>();
  float distance_3 = array[2]["v"].as<uint16_t>();
  float distance_4 = array[3]["v"].as<uint16_t>();

  float temperature = array[4]["t"].as<float>();
  float humidity = array[4]["h"].as<float>();
  bool cooler_state = array[5]["cs"].as<bool>();

  setValues(distance_1, distance_2, distance_3, distance_4, temperature, humidity, cooler_state);
}
