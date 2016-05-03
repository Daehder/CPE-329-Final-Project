/*
 * helper_functions.h
 *
 * Created: 5/3/2016 12:03:39 AM
 *  Author: mytch
 */ 


#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

// global defines 
#define F_CPU 16000000	// CPU clock frequency 

#define HALLE1 7		// Hall effect sensor at PD7
#define LED13 5			// on-board LED at PB5

// global libraries
#include <avr/io.h>
#include <util/delay.h>

// global helper functions 
void init_GPIO();
void init_timers();
void init_interrupts(); 
void init_I2C();
void delay_us(uint16_t delay_us);
void delay_ms(uint16_t delay_ms);
uint8_t check_halls(uint8_t sensor);

#endif /* HELPER_FUNCTIONS_H_ */