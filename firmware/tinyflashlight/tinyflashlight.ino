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

  pinMode(PIN_CHAN0, OUTPUT);
  pinMode(PIN_CHAN1, OUTPUT);

  analogWrite(PIN_CHAN0, 31);
  analogWrite(PIN_CHAN1, 31);

}

void loop() {
}
