#include <Arduino.h>
#include "StepMotor28BYJ48.h"

StepMotor28BYJ48::StepMotor28BYJ48(
                int STEPS_PER_REVOLUTION,
                int IN1_PIN,
                int IN2_PIN,
                int IN3_PIN,
                int IN4_PIN,
                int speed_motor,
                int step_length,
                int CLOCKWISE_BUTTON_PIN,
                int ANTICLOCKWISE_BUTTON_PIN
            )
{   
    setMotorPins(STEPS_PER_REVOLUTION, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);
    setButtonControl(CLOCKWISE_BUTTON_PIN, ANTICLOCKWISE_BUTTON_PIN);
    setStepLength(step_length);
    setSpeedMotor(speed_motor);

    this->inactive_time = millis();
}

void StepMotor28BYJ48::setMotorPins(
                    int STEPS_PER_REVOLUTION,
                    int IN1_PIN,
                    int IN2_PIN,
                    int IN3_PIN,
                    int IN4_PIN
                )
{
    this->STEPS_PER_REVOLUTION = STEPS_PER_REVOLUTION;
    this->IN1_PIN = IN1_PIN;
    this->IN2_PIN = IN2_PIN;
    this->IN3_PIN = IN3_PIN;
    this->IN4_PIN = IN4_PIN;

    pinMode(this->IN1_PIN, OUTPUT);
    pinMode(this->IN2_PIN, OUTPUT);
    pinMode(this->IN3_PIN, OUTPUT);
    pinMode(this->IN4_PIN, OUTPUT);

    this->motor = new Stepper(
        this->STEPS_PER_REVOLUTION,
        this->IN1_PIN,
        this->IN2_PIN,
        this->IN3_PIN,
        this->IN4_PIN);
}

int StepMotor28BYJ48::get_STEPS_PER_REVOLUTION()
{
    return this->STEPS_PER_REVOLUTION;
}

int StepMotor28BYJ48::get_IN1_PIN()
{
    return this->IN1_PIN;
}

int StepMotor28BYJ48::get_IN2_PIN()
{
    return this->IN2_PIN;
}

int StepMotor28BYJ48::get_IN3_PIN()
{
    return this->IN3_PIN;
}

int StepMotor28BYJ48::get_IN4_PIN()
{
    return this->IN4_PIN;
}

void StepMotor28BYJ48::setButtonControl(int CLOCKWISE_BUTTON_PIN, 
                                        int ANTICLOCKWISE_BUTTON_PIN)
{
    this->CLOCKWISE_BUTTON_PIN = CLOCKWISE_BUTTON_PIN;
    pinMode(this->CLOCKWISE_BUTTON_PIN, INPUT);

    this->ANTICLOCKWISE_BUTTON_PIN = ANTICLOCKWISE_BUTTON_PIN;
    pinMode(this->ANTICLOCKWISE_BUTTON_PIN, INPUT);
}

int StepMotor28BYJ48::get_CLOCKWISE_BUTTON_PIN()
{
    return this->CLOCKWISE_BUTTON_PIN;
}

int StepMotor28BYJ48::get_ANTICLOCKWISE_BUTTON_PIN()
{
    return this->ANTICLOCKWISE_BUTTON_PIN;
}

void StepMotor28BYJ48::setStepLength(int step_length)
{
    this->step_length = step_length;
}

int StepMotor28BYJ48::getStepLength()
{
    return this->step_length;
}

void StepMotor28BYJ48::setSpeedMotor(int speed_motor)
{
    this->speed_motor = speed_motor;
    this->motor->setSpeed(this->speed_motor);
}

int StepMotor28BYJ48::getSpeedMotor()
{
    return this->speed_motor;
}

void StepMotor28BYJ48::rotateClockWise()
{
    this->motor->step(this->step_length);
}

void StepMotor28BYJ48::rotateAntiClockWise()
{
    this->motor->step(-this->step_length);
}

void StepMotor28BYJ48::listenButtons()
{
    byte clockwiseButtonState = digitalRead(this->CLOCKWISE_BUTTON_PIN);
    byte anticlockwiseButtonState = digitalRead(this->ANTICLOCKWISE_BUTTON_PIN);

    if (clockwiseButtonState)
    {
        rotateClockWise();
        this->inactive_time = millis();
    }else if (anticlockwiseButtonState)
    {
        rotateAntiClockWise();
        this->inactive_time = millis();
    }
    

    if ((millis()-this->inactive_time)>5000) putToSleep() ;
}

void StepMotor28BYJ48::putToSleep(){
    digitalWrite(this->IN1_PIN, LOW);
    digitalWrite(this->IN2_PIN, LOW);
    digitalWrite(this->IN3_PIN, LOW);
    digitalWrite(this->IN4_PIN, LOW);
}

