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

#define PIN_PWM 1
#define PIN_TRIM 4

#define ADC_MIN 0
#define ADC_MAX 1023
#define PWM_MIN 0
#define PWM_MAX 255

#include <Arduino.h>

void setup() {
  pinMode(PIN_PWM, OUTPUT);
  pinMode(PIN_TRIM, INPUT);
}

uint8_t brightness = 127;

void loop() {
  uint8_t reading;
  reading = analogRead(PIN_TRIM) >> 2;
  if (reading != brightness) {
    brightness = reading;
    analogWrite(PIN_PWM, brightness);
  }
}
