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

#define PIN_PWM  1
#define PIN_TRIM A2

#define ADC_MIN  0
#define ADC_MAX  1023

#define PWM_MIN     0
#define PWM_MAX     64
#define PWM_DEFAULT 64
#define PWM_INVERT  1

#include <Arduino.h>

uint16_t reading = 0;
uint8_t pwm_curr = PWM_DEFAULT;
uint8_t pwm_last = PWM_DEFAULT;

void setup() {

  /*
  PRR = 0;
  TIMSK0 = 0b00000001; // interrupt on t0 overflow
  //OCR0B = pwm_curr;
#if (PWM_INVERT)
  TCCR0A = 0b00110001; // inverted 8bit pwm
#else
  TCCR0A = 0b00100001; // non-inverted 8bit pwm
#endif
  TCCR0B = 0b00001001; // disable prescale, ~3906Hz (?)
  GTCCR = 0;
  */

  pinMode(PIN_PWM, OUTPUT);
  pinMode(PIN_TRIM, INPUT);
}

void loop() {
  reading = analogRead(PIN_TRIM);

  /*
  if (reading == 1023) {
    pwm_curr = 255;
  } else if (reading < 1023 && reading >= 255) {
    pwm_curr = map(reading, 255, 1023, 1, 255);
  } else { // reading < 255
    pwm_curr = 0;
  }
  */

  pwm_curr = map(reading, ADC_MIN, ADC_MAX, PWM_MIN, PWM_MAX);

  if (pwm_curr != pwm_last) {
    analogWrite(PIN_PWM, pwm_curr);
    //OCR0B = pwm_curr;
    pwm_last = pwm_curr;
  }
}
