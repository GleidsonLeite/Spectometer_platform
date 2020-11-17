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
public:
    Fan(int relayPin, int switchButtonPin, int DHTPin, float biasTemperature);
    void configure();
    void switchStatus();
    void switchStatusByTemperature();
    void configureTimerInterruption();
};

#endif
