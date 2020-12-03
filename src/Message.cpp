#include <Arduino.h>
#include "Message.h"

Message::Message(){

}

String Message::serializeData(
  int distance1, int distance2, int distance3, int distance4,
  int temperature, int humidity, bool coolerState)
{
  const int capacity = JSON_ARRAY_SIZE(6) + 5*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(1);
  StaticJsonBuffer<capacity> jsonBuffer;

  JsonArray& arr = jsonBuffer.createArray();

  JsonObject& sensorDistance1 = jsonBuffer.createObject();
  sensorDistance1["id"] = "d1";
  sensorDistance1["v"] = distance1;

  JsonObject& sensorDistance2 = jsonBuffer.createObject();
  sensorDistance2["id"] = "d2";
  sensorDistance2["v"] = distance2;

  JsonObject& sensorDistance3 = jsonBuffer.createObject();
  sensorDistance3["id"] = "d3";
  sensorDistance3["v"] = distance3;

  JsonObject& sensorDistance4 = jsonBuffer.createObject();
  sensorDistance4["id"] = "d4";
  sensorDistance4["v"] = distance4;

  JsonObject& temperatureSensor = jsonBuffer.createObject();
  sensorDistance1["t"] = temperature;
  sensorDistance1["h"] = humidity;

  JsonObject& cooler = jsonBuffer.createObject();
  cooler["s"] = coolerState;

  arr.add(sensorDistance1);
  arr.add(sensorDistance2);
  arr.add(sensorDistance3);
  arr.add(sensorDistance4);
  arr.add(temperatureSensor);
  arr.add(cooler);

  char output[200] = "";
  arr.printTo(output);
  return output;
}

String Message::serializeDistanceSensorsData(int option, int distance1, int distance2, int distance3, int distance4){
  const int capacity = JSON_ARRAY_SIZE(4) + 4*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(1);
  StaticJsonBuffer<capacity> jsonBuffer;

  JsonArray& arr = jsonBuffer.createArray();

  JsonObject& sensorDistance1 = jsonBuffer.createObject();
  sensorDistance1["id"] = "d1";
  sensorDistance1["v"] = distance1;

  JsonObject& sensorDistance2 = jsonBuffer.createObject();
  sensorDistance2["id"] = "d2";
  sensorDistance2["v"] = distance2;

  JsonObject& sensorDistance3 = jsonBuffer.createObject();
  sensorDistance3["id"] = "d3";
  sensorDistance3["v"] = distance3;

  JsonObject& sensorDistance4 = jsonBuffer.createObject();
  sensorDistance4["id"] = "d4";
  sensorDistance4["v"] = distance4;

  JsonObject& messageOption = jsonBuffer.createObject();
  messageOption["o"] = option;

  arr.add(sensorDistance1);
  arr.add(sensorDistance2);
  arr.add(sensorDistance3);
  arr.add(sensorDistance4);
  arr.add(messageOption);

  char output[200] = "";
  arr.printTo(output);
  return output;
}
// void (*handleData)(int valueSensor1, int valueSensor2, int valueSensor3, int valueSensor4)
void Message::deserializeDistanceSensorsData(char jsonData[]){
  const int capacity = JSON_ARRAY_SIZE(4) + 4*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(1);
  // StaticJsonBuffer<capacity> jsonBuffer;
  // JsonObject& obj = jsonBuffer.parseObject(jsonData);

  // if (!obj.success())
  // {
  //   Serial.println("Error when convert object");
  // }else{
  //   Serial.println("All right");
  // }
  // Serial.println("Hello World");

}

