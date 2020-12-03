#ifndef MESSAGE_H
#define MESSAGE_H

#ifndef ARDUINO_h
#define ARDUINO_H

#include <ArduinoJson.h>

class Message
{
private:
public:
  Message();
  String serializeData(int distance1, int distance2, int distance3, int distance4, int temperature, int humidity, bool coolerState);
  String serializeDistanceSensorsData(int option, int distance1, int distance2, int distance3, int distance4);
  void handleResponseWire(int howMany);
  // void (*handleData)(int valueSensor1, int valueSensor2, int valueSensor3, int valueSensor4)
  void deserializeDistanceSensorsData(char jsonData[]);
};

#endif
#endif
