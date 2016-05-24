/*
 * helper_functions.c
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/3/2016
 * Revision: 1.0
 */

#include "helper_functions.h"

// initializes the GPIO
void init_GPIO(){
	DDRD &= ~(1<<HALLE0);	// Hall effects are inputs
	//DDRB |= (1<<LED13);		// LED at pin 13 is output (debug LED)
	DDRD |= (1<<GSCLK);
	
	PORTD |= (1<<HALLE0);	// hall effect 1 internal pulled up 	
	PORTD |= (1<<HALLE1);	// hall effect 1 internal pulled up 	
	PORTD |= (1<<HALLE2);	// hall effect 1 internal pulled up 	
}

// initialize timers
void init_timers(){
	// timer 0 (8bit)
		
	// timer 1 (16it timer)
	TCCR1A = 0x00;			// normal mode (overflow at 0xFFFF)
	TCCR1B = (1<<CS10);		// no clock pre-scaler
	TIMSK1 = (1<<TOIE1);	// mask to view 
	TIFR1 = (1<<TOV1);		// enable Interrupts when TCNT overflows
	
	// timer 2 (8 bit)
	TCCR2A = _BV(COM2B1)	// set on BOTTOM, clear on OCR2A (non-inverting) output on OC2B
			| _BV(WGM21)	// Fast pwm with OCR2A top
			| _BV(WGM20);	// Fast pwm with OCR2A top
	TCCR2B = _BV(WGM22);	// Fast pwm with OCR2A top
	OCR2B = 0;			// duty factor (as short a pulse as possible)
	OCR2A = 3;				// see tlc_config.h
	TCCR2B |= _BV(CS20);	// no prescale, (start pwm output)
}

// initialize variables
void init_variables(){
	
}

// delay in us via variable up to 65,535us
void delay_us(uint16_t delay_us){
	while(delay_us){
		_delay_us(1);
		delay_us--;
	}
}

// delay in us via variable up to 65,535us
void delay_ms(uint16_t delay_ms){
	while(delay_ms){
		_delay_ms(1);
		delay_ms--;
	}
}

/*
// returns the circumference of a tire wheel in mm (distance per revolution)
uint32_t circumference_mm(uint16_t wheel_size_mm){
	double d = PI*(wheel_size_mm);
	return (uint32_t)d; 
}

// This must be fixed up
// returns the speed of the by measuring time between two points
uint32_t speed_mm_us(uint32_t dist_mm, uint32_t time_us){
	return (dist_mm / time_us);
}
*/

// returns logic level of given hall effect sensor  
uint8_t check_halls(uint8_t sensor){
	return !(PIND & (1<<sensor));
}

// return the time in us remaining in TCNT1
uint16_t tcnt1_to_us(){
	return ( (TCNT1 * 1000000) / F_CPU);
}
