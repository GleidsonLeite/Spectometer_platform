#include <Arduino.h>
#include "StepMotor28BYJ48.h"

// STEP MOTOR 
const int STEPS_PER_REVOLUTION = 2048;

#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25

#define STEP_LENGTH 5
#define CONTROL_BUTTON_1 2
#define CONTROL_BUTTON_2 3
#define SPEED 15
byte controlButtonState = 0;

StepMotor28BYJ48 motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION, IN1, IN3, IN2, IN4, 
  SPEED, STEP_LENGTH, CONTROL_BUTTON_1, CONTROL_BUTTON_2);

unsigned long time;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // time = millis();
  motor.listenButtons();
  // Serial.println(millis()-time);
}