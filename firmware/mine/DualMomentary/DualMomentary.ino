/*
 * DualMomentary.ino
 *
 * Arduino sketch for driving flashlights with momentary switches (i.e., that
 * aren't shutting the light completely on/off by disconnecting the battery).
 * Targeted at ATTiny85's because Arduino/Wiring is heavier weight than
 * straight avr-gcc, but lets me use a ton of libraries rather than deciphering
 * and modifying existing drivers.
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPL v2.0
 *
 *                       HARDWARE LAYOUT
 *
 *                          +--    --+
 *                    !RST -|* \__/  |- VCC
 *  Momentary Switch / PB3 -|        |- PB2 / Voltage ADC
 *     Indicator LED / PB4 -| Tiny85 |- PB1 / PWM channel 0
 *                     GND -|        |- PB0 / PWM channel 1
 *                          +--------+
 *
 */

#include <Arduino.h>
#include <Button.h>
#include "buttoke.h"

#define PIN_PWM0 1
#define PIN_PWM1 0
#define PIN_BUTT 3
#define PIN_LED  4
#define PIN_VDIV 2

#define MODE_01 7
#define MODE_25 31
#define MODE_50 127
#define MODE_75 191
#define MODE_99 255

// Flashlight state machine
typedef enum {
  STATE_OFF,
  STATE_ON_MOON,
  STATE_ON_LOW,
  STATE_ON_MED,
  STATE_ON_HIGH,
  STATE_ON_MAX,
} light_state_t;

// Button state machine

// Global state variables
light_state_t curr_state = STATE_OFF;
light_state_t last_state = STATE_OFF;

// Above what PWM level will we switch from phase correct to fast?
#define FAST_PWM_START 8

// ADC readings for user warning/dimming, and complete shut-off
#define BATT_LOW  130
#define BATT_CRIT 120

// Button settings
#define BUTT_PULLUP         (true)
#define BUTT_INVERT         (true)
#define BUTT_DEBOUNCE_MS    (20)
#define BUTT_LONG_PRESS_MS  (300)

Button butt(PIN_BUTT, BUTT_PULLUP, BUTT_INVERT, BUTT_DEBOUNCE_MS);

void setup()
{
}

void loop()
{

  // Update button state
  butt.read();

  // Dispatch
  switch (curr_state)
  {

    case STATE_ON_MOON:
      break;

    case STATE_ON_LOW:
      break;

    case STATE_ON_MED:
      break;

    case STATE_ON_HIGH:
      break;

    case STATE_ON_MAX:
      break;

    case STATE_OFF:
    default: // default fall-through to also be off
      break;

  }
}
