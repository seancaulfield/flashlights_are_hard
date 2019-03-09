/*
 * tinyflashlight.ino
 *
 * Simple Arduino based program to PWM-ify a signal from an ATTiny13 to dim an
 * LED flashlight. Reads a trimpot attached to the ADC pins to set the level.
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPLv2.0
 *
 */

#define PIN_CHAN0  0
#define PIN_CHAN1  1

#include <Arduino.h>

void setup() {

  //pinMode(PIN_CHAN0, INPUT);

  pinMode(PIN_CHAN0, OUTPUT);
  pinMode(PIN_CHAN1, OUTPUT);
  digitalWrite(PIN_CHAN0, LOW);
  digitalWrite(PIN_CHAN1, LOW);
  delay(1000);
  digitalWrite(PIN_CHAN0, HIGH);

  //uint8_t pwm = 0;
  //while (pwm < 255) {
  //  analogWrite(PIN_CHAN1, pwm);
  //  delay(100);
  //  pwm++;
  //}
  //delay(100);
  //analogWrite(PIN_CHAN1, 255);

  //delay(1000);

  //pinMode(PIN_CHAN1, OUTPUT);
  //digitalWrite(PIN_CHAN1, HIGH);

  //analogWrite(PIN_CHAN0, 127);
  //digitalWrite(PIN_CHAN0, LOW);

  //delay(1000);
  //digitalWrite(PIN_CHAN1, HIGH);
  //delay(1000);
  //digitalWrite(PIN_CHAN1, LOW);

}

void loop() {
}
