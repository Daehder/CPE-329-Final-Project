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
	
}

// initialize interrupts
void init_interrupts(){
	
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

// returns the circumference of a tire wheel in mm (distance per revolution)
uint16_t circumference_mm(uint8_t wheel_size_mm){
	double d = PI*(wheel_size_mm/2);
	return (uint16_t)d; 
}

// This must be fixed up
// returns the speed of the by measuring time between two points
uint16_t speed_mm_s(uint8_t time_ms, uint16_t circum_mm){
	//uint8_t dist_mm = (circum_mm/NUM_HALLS); 
	//uint16_t speed = dist_mm/time_ms;
	return 0;
}

// returns logic level of given hall effect sensor  
uint8_t check_halls(uint8_t sensor){
	return !(PIND & (1<<sensor));
}
