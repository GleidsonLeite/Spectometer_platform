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
    setButtonControl(CLOCKWISE_BUTTON_PIN, ANTICLOCKWISE_BUTTON_PIN);
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
    setMaxSpeed(1000);
    setSpeed(500);
    setStepSize(200);
}

void StepMotorA4988::setMaxSpeed(int maxSpeed)
{
    this->maxSpeed = maxSpeed;
    this->motor->setMaxSpeed(maxSpeed);
}
void StepMotorA4988::setSpeed(int speed)
{
    this->speed = speed;
    this->motor->setSpeed(speed);
}
void StepMotorA4988::setStepSize(int stepSize)
{
    this->stepSize = stepSize;
}

void StepMotorA4988::rotateClockWise()
{
    this->motor->setCurrentPosition(0);
    this->motor->runToNewPosition(this->stepSize);
}

void StepMotorA4988::rotateAntiClockWise()
{
    this->motor->setCurrentPosition(0);
    this->motor->runToNewPosition(-this->stepSize);
    // while (this->motor->currentPosition() > -this->stepSize)
    // {
    //     this->motor->setSpeed(-this->speed);
    //     this->motor->runSpeed();
    //     Serial.println(this->motor->currentPosition());
    // }
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
    // Serial.print(clockwiseButtonState);
    // Serial.print("\t");
    // Serial.print(anticlockwiseButtonState);
    // Serial.println("");
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
