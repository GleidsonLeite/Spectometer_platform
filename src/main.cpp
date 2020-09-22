#include <Arduino.h>
#include "StepMotor28BYJ48.h"
#include "StepMotorA4988.h"

const int STEPS_PER_REVOLUTION = 2048;
#define STEP_LENGTH 10
#define SPEED 15

#define IN1_CILINDRICA 34
#define IN2_CILINDRICA 36
#define IN3_CILINDRICA 38
#define IN4_CILINDRICA 40

#define UP_BUTTON_CILINDRICA 42
#define DOWN_BUTTON_CILINDRICA 44

StepMotor28BYJ48 cilindrica_motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION, 
IN1_CILINDRICA, IN2_CILINDRICA, IN3_CILINDRICA, IN4_CILINDRICA, 
  SPEED, STEP_LENGTH, UP_BUTTON_CILINDRICA, DOWN_BUTTON_CILINDRICA);


#define IN1_PRISMA 27
#define IN2_PRISMA 29
#define IN3_PRISMA 31
#define IN4_PRISMA 33

#define UP_BUTTON_PRISMA 49
#define DOWN_BUTTON_PRISMA 51

StepMotor28BYJ48 prisma_motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION, 
IN1_PRISMA, IN2_PRISMA, IN3_PRISMA, IN4_PRISMA, 
  SPEED, STEP_LENGTH, UP_BUTTON_PRISMA, DOWN_BUTTON_PRISMA);

#define IN1_COLIMADORA 26
#define IN2_COLIMADORA 28
#define IN3_COLIMADORA 30
#define IN4_COLIMADORA 32

#define UP_BUTTON_COLIMADORA 48
#define DOWN_BUTTON_COLIMADORA 50

StepMotor28BYJ48 colimadora_motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION, 
IN1_COLIMADORA, IN2_COLIMADORA, IN3_COLIMADORA, IN4_COLIMADORA, 
  SPEED, STEP_LENGTH, UP_BUTTON_COLIMADORA, DOWN_BUTTON_COLIMADORA);


#define IN1_CAMERA 35
#define IN2_CAMERA 37
#define IN3_CAMERA 39
#define IN4_CAMERA 41

#define UP_BUTTON_CAMERA 43
#define DOWN_BUTTON_CAMERA 45

StepMotor28BYJ48 camera_motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION, 
IN1_CAMERA, IN2_CAMERA, IN3_CAMERA, IN4_CAMERA, 
  SPEED, STEP_LENGTH, UP_BUTTON_CAMERA, DOWN_BUTTON_CAMERA);


#define MOTOR_STEPS_CAMERA_FEEDFORWARD 200
#define FORWARD_BUTTON_CAMERA 46
#define BACKWARD_BUTTON_CAMERA 47
#define DIR 24
#define STEP 25
#define ENB 22

StepMotorA4988 feedfoward_camera_motor = StepMotorA4988(
  DIR, STEP, ENB,
  FORWARD_BUTTON_CAMERA, BACKWARD_BUTTON_CAMERA
);

void setup() {
  Serial.begin(9600);
}

unsigned long time;

void loop() {
  time = millis();
  colimadora_motor.listenButtons();
  prisma_motor.listenButtons();
  cilindrica_motor.listenButtons();
  camera_motor.listenButtons();
  feedfoward_camera_motor.listenButtons();
  Serial.println(millis()-time);
  delay(1000);
  // feedfoward_camera_motor.rotateClockWise();
  // delay(3000);
  // feedfoward_camera_motor.rotateAntiClockWise();
  // delay(3000);
}