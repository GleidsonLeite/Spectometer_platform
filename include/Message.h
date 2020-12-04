#ifndef MESSAGE_H
#define MESSAGE_H

#ifndef ARDUINO_h
#define ARDUINO_H

#include <ArduinoJson.h>

const int capacity = JSON_ARRAY_SIZE(6) + 5*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(1);

class Message
{
private:
  StaticJsonDocument<capacity> doc;
public:
  Message();
  String serializeData(int distance1, int distance2, int distance3, int distance4, int temperature, int humidity, bool coolerState);
  void deserializeData(char jsonSerialized[]);
};

#endif
#endif
