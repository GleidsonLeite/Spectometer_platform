#ifndef FAN_H
#define FAN_H
#ifndef ARDUINO_h
#define ARDUINO_H

#include <DHT.h>

class Fan
{
private:
    bool status;
    int relayPin;
    int switchButtonPin;

    DHT *temperatureSensor;
    float biasTemperature;
    float currentTemperature;
    float currentHumidity;
public:
    Fan(int relayPin, int switchButtonPin, int DHTPin, float biasTemperature);
    void configure();
    void switchStatus();
    void switchStatusByTemperature();
    void configureTimerInterruption();
    float getCurrentTemperature();
    float getCurrentHumidity();
    bool getStatus();
};

#endif
#endif
