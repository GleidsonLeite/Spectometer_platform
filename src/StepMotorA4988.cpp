#include <Arduino.h>
#include "StepMotorA4988.h"

StepMotorA4988::StepMotorA4988(
    int dirPin,
    int stepPin,
    int enablePin,
    int CLOCKWISE_BUTTON_PIN,
    int ANTICLOCKWISE_BUTTON_PIN)
{
  setMotorPins(dirPin, stepPin, enablePin);
  setButtonControl(CLOCKWISE_BUTTON_PIN, ANTICLOCKWISE_BUTTON_PIN);
}

void StepMotorA4988::setMotorPins(
    int dirPin,
    int stepPin,
    int enablePin)
{
  this->dirPin = dirPin;
  this->stepPin = stepPin;
  this->enablePin = enablePin;

  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(this->enablePin, LOW);
}

void StepMotorA4988::step(boolean dir, int steps)
{
  digitalWrite(this->dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++)
  {
    digitalWrite(this->stepPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(this->stepPin, LOW);
    delayMicroseconds(800);
  }
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
    this->step(true, 200);
    this->inactive_time = millis();
  }
  else if (!anticlockwiseButtonState)
  {
    wakeUp();
    this->step(false, 200);
    this->inactive_time = millis();
  }
  if ((millis() - this->inactive_time) > 5000)
    putToSleep();
}
