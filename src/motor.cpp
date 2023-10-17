#include "motor.h"
#include <Arduino.h>

motor::motor(int pin)
{
  pinMotor = pin;
  pinMode(pinMotor, OUTPUT);
}

void motor::turnOn()
{
  digitalWrite(pinMotor, HIGH);
}

void motor::turnOff()
{
  digitalWrite(pinMotor, LOW);
}

void motor::resetPreviousMillis()
{
  previousMillis = millis();
}

void motor::wait4nextLoop()
{
}

void motor::checkLoops()
{
  currentLoops++;
  if (currentLoops == loops)
  {
    state = FINISHED;
  }
  else
  {
    state = WAIT;
    previousMillisNextLoop=millis();
  }
  Serial.println(currentLoops);
}

void motor::waiting4nextloop()
{

  unsigned long currentMillisWait = millis();
  if (currentMillisWait - previousMillisNextLoop >= motoroff)
  {   
      state = RESET;
  }

}

void motor::startMotor()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= motorduration)
  {
    motorState = LOW;
    state = CHECKLOOP;
    Serial.println("motor aus");
  }
  else
  {
    motorState = HIGH;
  }

  digitalWrite(pinMotor, motorState);
}

void motor::startAndTurnOffAfter(int _loops, int _motorduration, int _motoroff)
{

  switch (state)
  {
  case RESET:
    motorduration = _motorduration;
    loops = _loops;
    motoroff = _motoroff;
    motorFinished = false;
    resetPreviousMillis();
    state = MOTOR;
    Serial.println("reset");
    // kein break weil switch case soll weiter
  case MOTOR:
    //Serial.println("motor");
    startMotor();
    break;
  case WAIT:
    waiting4nextloop();
    break;
  case CHECKLOOP:
    checkLoops();
    break;
  case FINISHED:
    motorFinished = true;
    break;
  default:
    state = RESET;
    Serial.println("DEFAULT");
    break;
  }
}

bool motor::isFinished()
{
  return motorFinished;
}

void motor::ready4nextaction()
{
  state = RESET;
  currentLoops = 0;
}