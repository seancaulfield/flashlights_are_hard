/*
 * tk-attiny-supplemental.h
 *
 * Additional layout(s) for ToyKeeper's FSM framework. Separate include file to make maintenance hopefully easier.
 *
 * Copyright (C) 2018 Selene Scriven, Sean Caulfield
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TK_ATTINY_SUPPLEMENTAL_H
#define TK_ATTINY_SUPPLEMENTAL_H

#ifdef _2XD_LAYOUT
#define DRIVER_TYPE_DEFINED

/*
 *           ----
 *   Reset -|1  8|- VCC
 * Eswitch -|2  7|- Voltage ADC
 *         -|3  6|- PWM (white)
 *     GND -|4  5|- PWM (red)
 *           ----
 *
 */

//#define CAP_PIN     PB3     // pin 2, OTC
//#define CAP_CHANNEL 0x03    // MUX 03 corresponds with PB3 (Star 4)
//#define CAP_DIDR    ADC3D   // Digital input disable bit corresponding with PB3

//#define PWM_PIN     PB1     // pin 6, FET PWM
//#define PWM_LVL     OCR0B   // OCR0B is the output compare register for PB1
//#define ALT_PWM_PIN PB0     // pin 5, 1x7135 PWM
//#define ALT_PWM_LVL OCR0A   // OCR0A is the output compare register for PB0

#define VOLTAGE_PIN PB2     // pin 7, voltage ADC
#define ADC_CHANNEL 0x01    // MUX 01 corresponds with PB2
#define ADC_DIDR    ADC1D   // Digital input disable bit corresponding with PB2
#define ADC_PRSCL   0x06    // clk/64

//#define AUXLED_PIN   PB4    // pin 3

#define SWITCH_PIN   PB3    // pin 2
#define SWITCH_PCINT PCINT3 // pin 2 pin change interrupt

#define PWM1_PIN PB0        // pin 5, 1x7135 PWM
#define PWM1_LVL OCR0A      // OCR0A is the output compare register for PB0
#define PWM2_PIN PB1        // pin 6, FET PWM
#define PWM2_LVL OCR0B      // OCR0B is the output compare register for PB1

#define USE_VOLTAGE_DIVIDER // use a voltage divider on pin 7, not VCC
#define VOLTAGE_PIN PB2     // pin 7, voltage ADC
#define VOLTAGE_CHANNEL 0x01 // MUX 01 corresponds with PB2
// 1.1V reference, left-adjust, ADC1/PB2
//#define ADMUX_VOLTAGE_DIVIDER ((1 << V_REF) | (1 << ADLAR) | VOLTAGE_CHANNEL)
// 1.1V reference, no left-adjust, ADC1/PB2
#define ADMUX_VOLTAGE_DIVIDER ((1 << V_REF) | VOLTAGE_CHANNEL)
#define VOLTAGE_ADC_DIDR    ADC1D   // Digital input disable bit corresponding with PB2
#define ADC_PRSCL   0x06    // clk/64

// Raw ADC readings at 4.4V and 2.2V (in-between, we assume values form a straight line)
#define ADC_44 184
#define ADC_22 92

//#define TEMP_DIDR   ADC4D
#define TEMP_CHANNEL 0b00001111

#define FAST 0xA3           // fast PWM both channels
#define PHASE 0xA1          // phase-correct PWM both channels

#endif //_2XD_LAYOUT

#endif //TK_ATTINY_SUPPLEMENTAL_H
