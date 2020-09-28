#ifndef STEPMOTORA4988_H
#define STEPMOTORA4988_H

#ifndef ARDUINO_h
#define ARDUINO_H

#include <AccelStepper.h>

class StepMotorA4988
{
private:
    
    // Pinout
    int dirPin;
    int stepPin;
    int enablePin;

    int motorInterfaceType;

    AccelStepper *motor;
    
    int stepSize;
    int maxSpeed;
    int speed;

    //Controller
    int CLOCKWISE_BUTTON_PIN;
    int ANTICLOCKWISE_BUTTON_PIN;

    unsigned long inactive_time;

public:
    StepMotorA4988(
        int DIRPin,
        int STPPin,
        int ENBPin,
        int CLOCKWISE_BUTTON_PIN,
        int ANTICLOCKWISE_BUTTON_PIN
    );

    void setMotorPins(
        int dirPin,
        int stepPin,
        int enablePin
    );

    void defaultConfig();

    void setMaxSpeed(int speed);
    void setSpeed(int speed);
    void setStepSize(int step);

    void rotateClockWise();
    void rotateAntiClockWise();

    void putToSleep();
    void wakeUp();

    void setButtonControl(int CLOCKWISE_BUTTON_PIN, int ANTICLOCKWISE_BUTTON_PIN);
    void listenButtons();

};

#endif
#endif