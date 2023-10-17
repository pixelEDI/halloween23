#include "leds.h"
#include <Arduino.h>

// WITHOUT analogWrite !!!!!!!!!!!!!!!

leds::leds(int pin) {
  pinLED = pin;
  pinMode(pinLED, OUTPUT);
}

void leds::turnOn() {
  digitalWrite(pinLED, HIGH);
}

void leds::turnOff() {
  digitalWrite(pinLED, LOW);
}

void leds::fadeOn(int millisec) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisFadeOn >= millisec) {
    previousMillisFadeOn = currentMillis;

    if (brightness <= 255) {

      digitalWrite(pinLED, HIGH);
      delayMicroseconds(brightness);
      digitalWrite(pinLED, LOW);
      delayMicroseconds(255 - brightness);
      brightness += fadeAmount;
    } else {
      digitalWrite(pinLED, LOW);
      delayMicroseconds(255);
    }
  }
}

void leds::pulsate(int delay_ms) {

    unsigned long currentMillis = millis();

  if (currentMillis - previousMillisPulsate >= delay_ms) {
    previousMillisPulsate = currentMillis;

    brightness += fadeDirection * fadeAmount;

    // Reverse the fade direction when reaching brightness limits
    if (brightness <= 0 || brightness >= 255) {
      fadeDirection = -fadeDirection;
    }

    digitalWrite(pinLED, HIGH);
    delayMicroseconds(brightness);
    digitalWrite(pinLED, LOW);
    delayMicroseconds(255 - brightness);
  } else {
    digitalWrite(pinLED, LOW);
    delayMicroseconds(255);
  }
}