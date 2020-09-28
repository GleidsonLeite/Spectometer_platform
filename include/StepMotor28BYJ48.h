#ifndef STEPMOTOR28BYJ48_H
#define STEPMOTOR28BYJ48_H
#ifndef ARDUINO_H
#define ARDUINO_H

#include "Stepper.h"
class StepMotor28BYJ48
{
private:
    int STEPS_PER_REVOLUTION;
    int IN1_PIN;
    int IN2_PIN;
    int IN3_PIN;
    int IN4_PIN;

    int speed_motor;

    Stepper *motor;

    int CLOCKWISE_BUTTON_PIN;
    int ANTICLOCKWISE_BUTTON_PIN;

    int step_length;

    unsigned long inactive_time;


public:
    StepMotor28BYJ48(
            int STEPS_PER_REVOLUTION,
            int IN1_PIN,
            int IN2_PIN,
            int IN3_PIN,
            int IN4_PIN,
            int speed_motor,
            int step_length,
            int CLOCKWISE_BUTTON_PIN,
            int ANTICLOCKWISE_BUTTON_PIN
        );
    
    void setMotorPins(
            int STEPS_PER_REVOLUTION,
            int IN1_PIN,
            int IN2_PIN,
            int IN3_PIN,
            int IN4_PIN
    );

    int get_STEPS_PER_REVOLUTION();
    int get_IN1_PIN();
    int get_IN2_PIN();
    int get_IN3_PIN();
    int get_IN4_PIN();
    
    void setButtonControl(int CLOCKWISE_BUTTON_PIN, int ANTICLOCKWISE_BUTTON_PIN);

    int get_CLOCKWISE_BUTTON_PIN();
    int get_ANTICLOCKWISE_BUTTON_PIN();

    void setStepLength(int step_length);
    int getStepLength();

    void setSpeedMotor(int speed_motor);
    int getSpeedMotor();

    void rotateClockWise();

    void rotateAntiClockWise();

    void listenButtons();

    void putToSleep();
};

#endif
#endif