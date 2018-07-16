/*
 * alfredo.c
 *
 * Testing out the FSM flashlight framework by Selene "ToyKeeper" Scriven.
 * Figured noodle sauces would be an appropriate naming scheme. :P
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPLv3
 *
 */

/*
 *           ----
 *   Reset -|1  8|- VCC
 *  Star 4 -|2  7|- Voltage ADC
 *  Star 3 -|3  6|- PWM (FET)
 *     GND -|4  5|- PWM (1x7135)
 *           ----
 *                       HARDWARE LAYOUT
 *
 *                          +---    ---+
 *                    !RST -|1  \__/  8|- VCC
 *  Momentary Switch / PB3 -|2        7|- PB2 / Voltage ADC
 *            [UNUSED] PB4 -|3 Tiny85 6|- PB1 / PWM channel 0 (white)
 *                     GND -|4        5|- PB0 / PWM channel 1 (red)
 *                          +----------+

 *
 */

#define _2XD_LAYOUT

#define USE_LVP

#define VOLTAGE_LOW             (29)
#define VOLTAGE_FUDGE_FACTOR    (5)
#define VOLTAGE_WARNING_SECONDS (30)

#define USE_THERMAL_REGULATION 

#define DEFAULT_THERM_CEIL      (60)
#define THERMAL_WARNING_SECONDS (30)

#define USE_RAMPING

#define RAMP_LENGTH             (50)

#define USE_DELAY_4MS
#define USE_DELAY_MS
#define USE_DELAY_ZERO

// How many clock ticks before a "press" event becomes a "hold" event?
#define HOLD_TIMEOUT            (15)

// How many clock ticks before a "release" event becomes a "click" event?
// Basically, the maximum time between clicks in a double-click or triple-click
#define RELEASE_TIMEOUT         (7)

//#define USE_BATTCHECK

#include "spaghetti-monster.h"

void setup() {
    debug_blink(2);
}

void loop() {
    nice_delay_ms(1000);
}

// vi: syntax=arduino ts=4 sw=4 expandtab
