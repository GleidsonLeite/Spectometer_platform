#include <Arduino.h>
#include "StepMotorA4988.h"

StepMotorA4988::StepMotorA4988(
    int dirPin,
    int stepPin,
    int enablePin,
    int CLOCKWISE_BUTTON_PIN,
    int ANTICLOCKWISE_BUTTON_PIN
)
{   
    setMotorPins(dirPin, stepPin, enablePin);
    defaultConfig();
}

void StepMotorA4988::setMotorPins(
    int dirPin,
    int stepPin,
    int enablePin
)
{
    this->dirPin = dirPin;
    this->stepPin = stepPin;
    this->enablePin = enablePin;

    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(enablePin, OUTPUT);

}

void StepMotorA4988::defaultConfig()
{
    this->motorInterfaceType = 1;
    this->motor = new AccelStepper(
        this->motorInterfaceType,
        this->stepPin,
        this->dirPin
    );
    this->motor->setMaxSpeed(1000);
    
    setMaxSpeed(1000);
    setSpeed(400);
    setStepSize(10);
}

void StepMotorA4988::setMaxSpeed(int maxSpeed)
{
    this->maxSpeed = maxSpeed;
}
void StepMotorA4988::setSpeed(int speed)
{
    this->speed = speed;
}
void StepMotorA4988::setStepSize(int stepSize)
{
    this->stepSize = stepSize;   
}

void StepMotorA4988::rotateClockWise()
{
    wakeUp();
    this->motor->setCurrentPosition(0);
    while (this->motor->currentPosition() != this->stepSize)
    {
        this->motor->setSpeed(this->speed);
        this->motor->runSpeed();
    }
    putToSleep();
}

void StepMotorA4988::rotateAntiClockWise()
{
    wakeUp();
    this->motor->setCurrentPosition(0);
    while (this->motor->currentPosition() != -this->stepSize)
    {
        this->motor->setSpeed(-this->speed);
        this->motor->runSpeed();
    }
    putToSleep();
}

void StepMotorA4988::putToSleep()
{
    digitalWrite(this->enablePin, HIGH);
}

void StepMotorA4988::wakeUp()
{
    digitalWrite(this->enablePin, LOW);
}

void StepMotorA4988::setButtonControl(
    int CLOCKWISE_BUTTON_PIN,
    int ANTICLOCKWISE_BUTTON_PIN)
{
    this->CLOCKWISE_BUTTON_PIN = CLOCKWISE_BUTTON_PIN;
    pinMode(this->CLOCKWISE_BUTTON_PIN, INPUT_PULLUP);

    this->ANTICLOCKWISE_BUTTON_PIN = ANTICLOCKWISE_BUTTON_PIN;
    pinMode(this->ANTICLOCKWISE_BUTTON_PIN, INPUT_PULLUP);
}

void StepMotorA4988::listenButtons()
{
    byte clockwiseButtonState = digitalRead(this->CLOCKWISE_BUTTON_PIN);
    byte anticlockwiseButtonState = digitalRead(this->ANTICLOCKWISE_BUTTON_PIN);

    if (!clockwiseButtonState)
    {
        wakeUp();
        rotateClockWise();
        this->inactive_time = millis();
    }else if (!anticlockwiseButtonState)
    {   
        wakeUp();
        rotateAntiClockWise();
        this->inactive_time = millis();
    }
    if ((millis()-this->inactive_time)>5000) putToSleep() ;
}