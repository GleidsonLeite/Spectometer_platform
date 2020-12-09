#include <Arduino.h>
#include "Fan.h"

Fan::Fan(int relayPin, int switchButtonPin,
         int DHTPin, float biasTemperature)
{
  this->relayPin = relayPin;
  this->switchButtonPin = switchButtonPin;
  this->status = false;

  this->biasTemperature = biasTemperature;
  this->temperatureSensor = new DHT(DHTPin, DHT22);
}

void Fan::switchStatus()
{
  digitalWrite(this->relayPin, this->status ? HIGH : LOW);
  this->status = !this->status;
}

void Fan::switchStatusByTemperature()
{
  this->currentTemperature = this->temperatureSensor->readTemperature();
  this->currentHumidity = this->temperatureSensor->readHumidity();
  if (isnan(this->currentTemperature))
  {
    Serial.println(F("Failed to read temperature from DHT sensor"));
    return;
  }
  // Serial.println(this->currentTemperature);
  if (this->currentTemperature >= this->biasTemperature && !this->status)
  {
    digitalWrite(this->relayPin, LOW);
    this->status = true;
  }
  else if (this->currentTemperature < this->biasTemperature && this->status)
  {
    digitalWrite(this->relayPin, HIGH);
    this->status = false;
  }
}

void Fan::configure()
{
  // relayPin
  pinMode(this->relayPin, OUTPUT);
  digitalWrite(this->relayPin, HIGH);

  // Switch button
  pinMode(this->switchButtonPin, INPUT_PULLUP);
  configureTimerInterruption();
}

void Fan::configureTimerInterruption()
{
  /*
    * We are using this timer interruption because we need read the dht sensor every 2 seconds
  */

  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 62500;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

float Fan::getCurrentTemperature() { return this->currentTemperature; }
float Fan::getCurrentHumidity() { return this->currentHumidity; }
bool Fan::getStatus() { return this->status; }
