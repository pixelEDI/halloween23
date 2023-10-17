/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | https://linktr.ee/pixeledi
CH32V003 Halloween | V1.0 | 10.2023

  pinout
  https://github.com/cnlohr/ch32v003fun'

  You can also use an Arduino Uno

*/
#include <Arduino.h>
#include "leds.h"
#include "motor.h"

leds ledRed(6);
motor ghosty(3);
motor skeleton(2); //optional easy to implement 2nd motor

const byte pirSensor = 8;
int pirState = LOW;
int cooldown=false;
unsigned long previousMillis=0;

enum states
{
  WAIT,
  ACTION
} state;

void refreshCooldown(){
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 20000){
    previousMillis =currentMillis;
    cooldown=false;
  }
}

void checkPIR()
{
  pirState = digitalRead(pirSensor);

  if (pirState == HIGH && cooldown==false)
  {
     state=ACTION;
     Serial.println("only one signal");
     cooldown=true;
  }

}

void setup()
{
  Serial.begin(115200);
  pinMode(pirSensor, INPUT);
}

void loop()
{

  checkPIR();
  refreshCooldown();

  switch (state)
  {
  case ACTION:

    //how many spins, how long should last a spin, deleay between spins
    ghosty.startAndTurnOffAfter(5, 600, 2000);
    skeleton.startAndTurnOffAfter(3,1500,2000);

    ledRed.pulsate(10);
    if (ghosty.isFinished() == true && skeleton.isFinished() == true){
      state = WAIT;
    }
    
    break;
  case WAIT:
    ledRed.turnOff();
    ghosty.ready4nextaction();
    skeleton.ready4nextaction();
    break;
  }
}
