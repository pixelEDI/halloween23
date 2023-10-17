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
Motor | V1.0 | 10.2023

  different states with enums

  case 1:
    reset -> motor -> checkloop -> wait ->
  case 2:
    motor -> checkloop - wait ->
  case 3: 
    motor ->  checkloop -> finished
*/
#ifndef motor_h
#define motor_h

#include <Arduino.h>

class motor {
  private:
  enum states
    {
      MOTOR,
      WAIT,
      CHECKLOOP,
      FINISHED,
      RESET
    };

    states state = RESET;
    int pinMotor;
    int motorState=LOW;
    int motorduration=0;
    int motoroff=0;
    int currentLoops=0;
    int loops=0;
    bool nextLoop=false;
    bool motorFinished=false;

    unsigned long previousMillis = 0;
    unsigned long previousMillisNextLoop = 0;
  
  public:
    motor(int pin);
    void turnOn();
    void turnOff();
    void startMotor();
    void startAndTurnOffAfter(int _loops, int _motorduration, int _motoroff);
    bool isFinished();
    void waiting4nextloop();
    void ready4nextaction();
    void checkLoops();
    void wait4nextLoop();
    void resetPreviousMillis();

};

#endif