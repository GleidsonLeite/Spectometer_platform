#ifndef MESSAGE_H
#define MESSAGE_H

#ifndef ARDUINO_h
#define ARDUINO_H

#include <ArduinoJson.h>

const int capacity = JSON_ARRAY_SIZE(6) + 5*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(1);

class Message
{
private:
public:
  Message();
  String serializeData(uint16_t distance1, uint16_t distance2, uint16_t distance3, uint16_t distance4, float temperature, float humidity, bool coolerState);
  void deserializeData(char jsonSerialized[], void (*setValues)(uint16_t d1, uint16_t d2, uint16_t d3, uint16_t d4, float temperature, float humidity, bool cooler_state));
};

#endif
#endif
