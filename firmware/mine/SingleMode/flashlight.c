/* STAR_off_time version 1.2
 *
 * Changelog
 *
 * 1.0 Initial version
 * 1.1 Bug fix
 * 1.2 Added support for dual PWM outputs and selection of PWM mode per output level
 * 1.3 Added ability to have turbo ramp down gradually instead of step down
 *
 */

/*
 * NANJG 105C Diagram
 *           ---
 *         -|   |- VCC
 *  Star 4 -|   |- Voltage ADC
 *  Star 3 -|   |- PWM
 *     GND -|   |- Star 2
 *           ---
 *
 * FUSES
 *		I use these fuse settings
 *		Low:  0x75	(4.8MHz CPU without 8x divider, 9.4kHz phase-correct PWM or 18.75kHz fast-PWM)
 *		High: 0xff
 *
 *      For more details on these settings, visit http://github.com/JCapSolutions/blf-firmware/wiki/PWM-Frequency
 *
 * STARS
 *		Star 2 = Moon if connected and alternate PWM output not used
 *		Star 3 = H-L if connected, L-H if not
 *		Star 4 = Capacitor for off-time
 *
 * VOLTAGE
 *		Resistor values for voltage divider (reference BLF-VLD README for more info)
 *		Reference voltage can be anywhere from 1.0 to 1.2, so this cannot be all that accurate
 *
 *           VCC
 *            |
 *           Vd (~.25 v drop from protection diode)
 *            |
 *          1912 (R1 19,100 ohms)
 *            |
 *            |---- PB2 from MCU
 *            |
 *          4701 (R2 4,700 ohms)
 *            |
 *           GND
 *
 *		ADC = ((V_bat - V_diode) * R2   * 255) / ((R1    + R2  ) * V_ref)
 *		125 = ((3.0   - .25    ) * 4700 * 255) / ((19100 + 4700) * 1.1  )
 *		121 = ((2.9   - .25    ) * 4700 * 255) / ((19100 + 4700) * 1.1  )
 *
 *		Well 125 and 121 were too close, so it shut off right after lowering to low mode, so I went with
 *		130 and 120
 *
 *		To find out what value to use, plug in the target voltage (V) to this equation
 *			value = (V * 4700 * 255) / (23800 * 1.1)
 *      
 */

#define F_CPU 4800000UL

/*
 * =========================================================================
 * Settings to modify per driver
 */

#define VOLTAGE_MON				// Comment out to disable

#define LIFEPO4				1	//Changes low voltage detection threshold
								// from around 3.2V to 2.8V, as LiFePO4
								// batteries have a slightly lower voltage
								// because of their chemistry.

#if LIFEPO4
#warning "Compiling for LiFePO4 low batt level (2.8V)"
#define ADC_LOW				110	// (LiFePO4 3.2V) When do we start ramping
#define ADC_CRIT			100	// (LiFePO4 3.2V) When do we turn off
#else
#warning "Compiling for Li-ion low batt level (3.2V)"
#define ADC_LOW				130	// (Li-ion 3.7V) When do we start ramping
#define ADC_CRIT			120	// (Li-ion 3.7V) When do we turn off
#endif

#define MODE_NORMAL			63
#define MODE_LOW			31

/*
 * =========================================================================
 */

//#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>	
#include <avr/eeprom.h>
#include <avr/sleep.h>
//#include <avr/power.h>

#define PWM_PIN			PB1
#define VOLTAGE_PIN		PB2

#define ADC_CHANNEL		0x01	// MUX 01 corresponds with PB2
#define ADC_DIDR 		ADC1D	// Digital input disable bit for PB2
#define ADC_PRSCL		0x06	// Divide ADC clk by 64

#define PWM_OUT			OCR0B	// OCR0B is the PB1 output compare register
#define LOWBATT_COUNT	8		// Number of low battery readings to consider

/*
 * global variables
 */

uint8_t curr_pwm = 0;
uint8_t lowbatt_cnt = 0;

/*
 * watchdog timer functions
 */

inline void WDT_on() {
	// Setup watchdog timer to only interrupt, not reset
	cli();							// Disable interrupts
	wdt_reset();					// Reset the WDT
	WDTCR |= (1<<WDCE) | (1<<WDE);  // Start timed sequence
	#ifdef TICKS_250MS
	WDTCR = (1<<WDTIE) | (1<<WDP2); // Enable interrupt every 250ms
	#else
	WDTCR = (1<<WDTIE) | (1<<WDP2) | (1<<WDP0); // Enable interrupt every 500ms
	#endif
	sei();							// Enable interrupts
}

inline void WDT_off()
{
	cli();							// Disable interrupts
	wdt_reset();					// Reset the WDT
	MCUSR &= ~(1<<WDRF);			// Clear Watchdog reset flag
	WDTCR |= (1<<WDCE) | (1<<WDE);  // Start timed sequence
	WDTCR = 0x00;					// Disable WDT
	sei();							// Enable interrupts
}

/*
 * watchdog timer IRQ handler
 */

ISR(WDT_vect) {
	static uint8_t ticks = 0;
	if (ticks < 255) ticks++;
	// If you want more than 255 for longer turbo timeouts
	//static uint16_t ticks = 0;
	//if (ticks < 60000) ticks++;
}

/*
 * analog-digital converter functions functions
 */

inline void ADC_on() {
	DIDR0 |= (1 << ADC_DIDR); // disable digital input on ADC pin to reduce power consumption
	ADMUX  = (1 << REFS0) | (1 << ADLAR) | ADC_CHANNEL; // 1.1v reference, left-adjust, ADC1/PB2
	ADCSRA = (1 << ADEN ) | (1 << ADSC ) | ADC_PRSCL;   // enable, start, prescale
}

inline void ADC_off() {
	ADCSRA &= ~(1<<7); //ADC off
}

/*
 * set output to given level. mostly for coordinating since it's a single line
 * of code doing the actual work.
 */
inline void set_output(uint8_t new_pwm_lvl) {

	// Set output level
	PWM_OUT = new_pwm_lvl;

	// Save pwm level in global var for later
	curr_pwm = new_pwm_lvl;
}

/*
 * (optional) voltage monitoring function
 */

#ifdef VOLTAGE_MON
uint8_t get_voltage() {
	uint8_t reading;

	// Start conversion
	ADCSRA |= (1 << ADSC);

	// Wait for completion
	while (ADCSRA & (1 << ADSC))
    	;

	reading = ADCH;

	return reading;
}
#endif

int main(void)
{	

    // Set PWM pin to output
    DDRB |= (1 << PWM_PIN);

    // Set timer to do PWM for correct output pin and set prescaler timing
    TCCR0A = 0x23; // phase corrected PWM is 0x21 for PB1, fast-PWM is 0x23
    TCCR0B = 0x01; // pre-scaler for timer (1 => 1, 2 => 8, 3 => 64...)
	
	// Enable ADC only if we're monitoring voltage
	#ifdef VOLTAGE_MON
	ADC_on();
	#else
	ADC_off();
	#endif

	ACSR   |=  (1<<7); //AC off XXX ???
	
	// Enable sleep mode set to Idle that will be triggered by the sleep_mode() command.
	// Will allow us to go idle between WDT interrupts
	set_sleep_mode(SLEEP_MODE_IDLE);
	
	WDT_on();
	
	// Setup PWM
	TCCR0A = 0b00100011; // fast-PWM normal output
	//TCCR0A = 0b00100001; // phase corrected PWM normal output
	TCCR0B = 0x01; // pre-scaler for timer (1 => 1, 2 => 8, 3 => 64...)
	
	// Set output to normal mode
	set_output(MODE_NORMAL);
	
	uint8_t i = 0;
	uint8_t hold_pwm;
	uint8_t voltage;

	while(1) {

#ifdef VOLTAGE_MON
		voltage = get_voltage();

		if (voltage < ADC_CRIT && ++lowbatt_cnt > LOWBATT_COUNT) {

			// we hit the critical level so flash 10 times and turn off
			hold_pwm = curr_pwm;
			for (i=0; i<10; i++) {
				set_output(0);
				_delay_ms(250);
				set_output(hold_pwm);
				_delay_ms(500);
			}

			// Turn off the light
			set_output(0);

			// Disable WDT so it doesn't wake us up
			WDT_off();

			// Power down as many components as possible
			set_sleep_mode(SLEEP_MODE_PWR_DOWN);
			sleep_mode();

		} else if (voltage < ADC_CRIT && ++lowbatt_cnt > LOWBATT_COUNT) {

			// Flash 3 times before lowering
			hold_pwm = curr_pwm;
			for (i=0; i<3; i++) {
				set_output(0);
				_delay_ms(250);
				set_output(hold_pwm);
				_delay_ms(500);
			}

			// Set output to low setting
			set_output(MODE_LOW);

		} else {
			// Reset count if we got a good reading
			lowbatt_cnt = 0;
		}
#endif

		sleep_mode();
	}

    return 0; // Standard Return Code
}

// vi: syntax=cpp ts=4 sw=4 noexpandtab smarttab
