#ifndef STEPMOTORA4988_H
#define STEPMOTORA4988_H

#ifndef ARDUINO_h
#define ARDUINO_H

class StepMotorA4988
{
private:
  // Pinout
  int dirPin;
  int stepPin;
  int enablePin;

  int motorInterfaceType;

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
      int ANTICLOCKWISE_BUTTON_PIN);

  void setMotorPins(
      int dirPin,
      int stepPin,
      int enablePin);

  void step(boolean dir, int steps);

  void putToSleep();
  void wakeUp();

  void setButtonControl(int CLOCKWISE_BUTTON_PIN, int ANTICLOCKWISE_BUTTON_PIN);
  void listenButtons();
};

#endif
#endif
