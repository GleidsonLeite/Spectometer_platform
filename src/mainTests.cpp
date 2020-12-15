#include <Arduino.h>
#include "StepMotorA4988.h"

#define MOTOR_STEPS_CAMERA_FEEDFORWARD 200
#define FORWARD_BUTTON_CAMERA 46
#define BACKWARD_BUTTON_CAMERA 47
#define DIR 24
#define STEP 25
#define ENB 22

StepMotorA4988 feedfoward_camera_motor = StepMotorA4988(
    DIR, STEP, ENB,
    FORWARD_BUTTON_CAMERA, BACKWARD_BUTTON_CAMERA);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Hello World");

  feedfoward_camera_motor.step(true, 200);
  delay(1000);
  feedfoward_camera_motor.step(false, 200);
  delay(1000);
}
