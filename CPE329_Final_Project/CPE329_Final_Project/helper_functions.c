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
	DDRB |= (1<<LED13);		// LED at pin 13 is output (debug LED)
	
	PORTD |= (1<<HALLE0);	// hall effect 1 internal pulled up 	
	PORTD |= (1<<HALLE1);	// hall effect 1 internal pulled up 	
	PORTD |= (1<<HALLE2);	// hall effect 1 internal pulled up 	
	PORTD |= (1<<HALLE3);	// hall effect 1 internal pulled up
	PORTD |= (1<<HALLE4);	// hall effect 1 internal pulled up
	PORTD |= (1<<HALLE5);	// hall effect 1 internal pulled up
}

// initialize timers
void init_timers(){
	// timer 0 (bit)
	
	// timer 1 (16it timer)
	TCCR1A = 0x00;			// normal mode (overflow at 0xFFFF)
	TCCR1B = (1<<CS10);		// no clock pre-scaler
	TIMSK1 = (1<<TOIE1);	// mask to view 
	TIFR1 = (1<<TOV1);		// enable Interrupts when TCNT overflows
}

// initialize variables
void init_variables(){
	
}

// initialize I2C communication
void init_I2C(){
	
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
