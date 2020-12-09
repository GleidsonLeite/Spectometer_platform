#ifndef VL53L0XMANAGER_H
#define VL53L0XMANAGER_H
#ifndef ARDUINO_h
#define ARDUINO_H

#include "Adafruit_VL53L0X.h"

struct distanceSensor
{
  int shutdownPin;
  int address;
  Adafruit_VL53L0X sensor;
  VL53L0X_RangingMeasurementData_t measure;
};

class VL53L0XManager
{
private:
  int numberSensors;
  struct distanceSensor *distanceSensors;

public:
  VL53L0XManager(
      int numberSensors,
      struct distanceSensor *distanceSensors);

  void setAddresses();

  uint16_t getSensorDistance(int sensorNumber);
};

#endif
#endif
