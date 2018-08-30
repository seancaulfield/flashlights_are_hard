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

#define USE_LVP

#define VOLTAGE_LOW             (29)
#define VOLTAGE_FUDGE_FACTOR    (5)
#define VOLTAGE_WARNING_SECONDS (30)

#define USE_THERMAL_REGULATION 

#define DEFAULT_THERM_CEIL      (60)
#define THERMAL_WARNING_SECONDS (30)

#define USE_RAMPING

//#define RAMP_LENGTH             (50)
#define MAX_CLICKS 3

#define USE_DELAY_4MS
#define USE_DELAY_MS
#define USE_DELAY_ZERO
#define USE_IDLE_MODE   // reduce power use while awake and no tasks are pending

#define USE_SET_LEVEL_GRADUALLY  // isn't used except for thermal adjustments

// How many clock ticks before a "press" event becomes a "hold" event?
#define HOLD_TIMEOUT            (15)

// How many clock ticks before a "release" event becomes a "click" event?
// Basically, the maximum time between clicks in a double-click or triple-click
#define RELEASE_TIMEOUT         (7)

//#define USE_BATTCHECK

// ramp down via regular button hold if a ramp-up ended <1s ago
// ("hold, release, hold" ramps down instead of up)
#define USE_REVERSING

// try to auto-detect how many eeprom bytes
#define USE_EEPROM
#define EEPROM_BYTES_BASE 2

#ifdef USE_INDICATOR_LED
#define EEPROM_INDICATOR_BYTES 1
#else
#define EEPROM_INDICATOR_BYTES 0
#endif

#ifdef USE_THERMAL_REGULATION
#define EEPROM_THERMAL_BYTES 2
#else
#define EEPROM_THERMAL_BYTES 0
#endif

#define EEPROM_BYTES (EEPROM_BYTES_BASE+EEPROM_INDICATOR_BYTES+EEPROM_THERMAL_BYTES)

#include "cfg-2xd.h"
#include "spaghetti-monster.h"

uint8_t off_state(EventPtr event, uint16_t arg);
uint8_t steady_state(EventPtr event, uint16_t arg);
uint8_t nearest_level(int16_t target);

void load_config();
void save_config();

// default ramp options if not overridden earlier per-driver
#ifndef RAMP_SMOOTH_FLOOR
  #define RAMP_SMOOTH_FLOOR 1
#endif
#ifndef RAMP_SMOOTH_CEIL
  #if PWM_CHANNELS == 3
    #define RAMP_SMOOTH_CEIL MAX_Nx7135
  #else
    #define RAMP_SMOOTH_CEIL MAX_LEVEL - 30
  #endif
#endif
#ifndef RAMP_DISCRETE_FLOOR
  #define RAMP_DISCRETE_FLOOR 20
#endif
#ifndef RAMP_DISCRETE_CEIL
  #define RAMP_DISCRETE_CEIL RAMP_SMOOTH_CEIL
#endif
#ifndef RAMP_DISCRETE_STEPS
  #define RAMP_DISCRETE_STEPS 7
#endif

// brightness control
uint8_t memorized_level = MAX_1x7135;
// smooth vs discrete ramping
//volatile uint8_t ramp_style = 0;  // 0 = smooth, 1 = discrete
volatile uint8_t ramp_smooth_floor = RAMP_SMOOTH_FLOOR;
volatile uint8_t ramp_smooth_ceil = RAMP_SMOOTH_CEIL;
//volatile uint8_t ramp_discrete_floor = RAMP_DISCRETE_FLOOR;
//volatile uint8_t ramp_discrete_ceil = RAMP_DISCRETE_CEIL;
//volatile uint8_t ramp_discrete_steps = RAMP_DISCRETE_STEPS;
//uint8_t ramp_discrete_step_size;  // don't set this

#ifdef USE_INDICATOR_LED
// bits 2-3 control lockout mode
// bits 0-1 control "off" mode
// modes are: 0=off, 1=low, 2=high, 3=blinking (if TICK_DURING_STANDBY enabled)
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
//uint8_t indicator_led_mode = (1<<2) + 2;
uint8_t indicator_led_mode = (2<<2) + 1;
#else
uint8_t indicator_led_mode = (3<<2) + 1;
#endif
#endif

#ifdef USE_THERMAL_REGULATION
// brightness before thermal step-down
uint8_t target_level = 0;
#endif

uint8_t off_state(EventPtr event, uint16_t arg) {

    // Initial entry to state, turn off
    if (event == EV_enter_state) {
        set_level(0);
        go_to_standby = 1;
        return MISCHIEF_MANAGED;
    }
    
    // Return to sleep mode if we got bumped but didn't leave off state
    else if (event == EV_tick) {
        if (arg > TICKS_PER_SECOND*2) {
            go_to_standby = 1;
        }
        return MISCHIEF_MANAGED;
    }

    // hold (start): go to lowest level, but allow this to be
    // aborted for a regular click (XXX: How?)
    else if (event == EV_click1_press) {
        set_level(nearest_level(1));
        return MISCHIEF_MANAGED;
    }

    // hold: go to lowest level
    else if (event == EV_click1_hold) {
        if (arg >= HOLD_TIMEOUT) {
            set_state(steady_state, 1);
        }
        return MISCHIEF_MANAGED;
    }

    // hold, release quickly: go to lowest level
    else if (event == EV_click1_hold_release) {
        set_state(steady_state, 1);
        return MISCHIEF_MANAGED;
    }

    // 1 click (pre-timeout): go to last level, but allow abort for a double tap
    else if (event == EV_click1_release) {
        set_level(nearest_level(memorized_level));
        return MISCHIEF_MANAGED;
    }

    // 1 click: regular mode
    else if (event == EV_1click) {
        set_state(steady_state, memorized_level);
        return MISCHIEF_MANAGED;
    }

    // 2 clicks (start): off, prep for later events (XXX ???)
    else if (event == EV_click2_press) {
        set_level(0);
        return MISCHIEF_MANAGED;
    }

    // 2 clicks, hold: go to highest level for ramping down
    else if (event == EV_click2_hold) {
        set_state(steady_state, MAX_LEVEL);
        return MISCHIEF_MANAGED;
    }

    // 2 clicks: higest mode
    else if (event == EV_2clicks) {
        set_state(steady_state, nearest_level(MAX_LEVEL));
        return MISCHIEF_MANAGED;
    }

    return EVENT_NOT_HANDLED;
}

uint8_t steady_state(EventPtr event, uint16_t arg) {
    return EVENT_NOT_HANDLED;
}

// find the ramp level closest to the target,
// using only the levels which are allowed in the current state
uint8_t nearest_level(int16_t target) {
    // bounds check
    // using int16_t here saves us a bunch of logic elsewhere,
    // by allowing us to correct for numbers < 0 or > 255 in one central place
    uint8_t mode_min = ramp_smooth_floor;
    uint8_t mode_max = ramp_smooth_ceil;
    if (target < mode_min) return mode_min;
    if (target > mode_max) return mode_max;

    // Only need smoooooth ramping
    return target;
}


void load_config() {
    if (load_eeprom()) {
        ramp_smooth_floor = eeprom[0];
        ramp_smooth_ceil = eeprom[1];
        #ifdef USE_THERMAL_REGULATION
        therm_ceil = eeprom[EEPROM_BYTES_BASE];
        therm_cal_offset = eeprom[EEPROM_BYTES_BASE+1];
        #endif
        #ifdef USE_INDICATOR_LED
        indicator_led_mode = eeprom[EEPROM_BYTES_BASE+EEPROM_THERMAL_BYTES];
        #endif
    }
}

void save_config() {
    eeprom[0] = ramp_smooth_floor;
    eeprom[1] = ramp_smooth_ceil;
    #ifdef USE_THERMAL_REGULATION
    eeprom[EEPROM_BYTES_BASE  ] = therm_ceil;
    eeprom[EEPROM_BYTES_BASE+1] = therm_cal_offset;
    #endif
    #ifdef USE_INDICATOR_LED
    eeprom[EEPROM_BYTES_BASE+EEPROM_THERMAL_BYTES] = indicator_led_mode;
    #endif

    save_eeprom();
}


void low_voltage() {
    StatePtr state = current_state;

    // in normal mode, step down or turn off
    if (state == steady_state) {
        if (actual_level > 1) {
            uint8_t lvl = (actual_level >> 1) + (actual_level >> 2);
            set_level(lvl);
            #ifdef USE_THERMAL_REGULATION
            target_level = lvl;
            #ifdef USE_SET_LEVEL_GRADUALLY
            // not needed?
            //set_level_gradually(lvl);
            #endif
            #endif
        }
        else {
            set_state(off_state, 0);
        }
    }
    // all other modes, just turn off when voltage is low
    else {
        set_state(off_state, 0);
    }
}

void setup() {
    set_level(RAMP_SIZE/8);
    delay_4ms(3);
    set_level(0);
    //load_config();
    push_state(off_state, 0);
}

void loop() {
    nice_delay_ms(1000);
}

// vi: syntax=arduino ts=4 sw=4 expandtab
