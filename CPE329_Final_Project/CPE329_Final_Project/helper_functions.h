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

#define HALLE0 7		// Hall effect sensor at PD7
#define HALLE1 6		// Hall effect sensor at PD6
#define HALLE2 5		// Hall effect sensor at PD5
#define HALLE3 4		// Hall effect sensor at PD4
#define HALLE4 3		// Hall effect sensor at PD3
#define HALLE5 2		// Hall effect sensor at PD2
#define LED13 5			// on-board LED at PB5

#define PI 3.141592		// mathematical pi
#define NUM_HALLS 6		// number of hall effects on wheel

// global libraries
//#include <avr/io.h>
//#include <util/delay.h>
#include <stdint.h>

// struct for color spectrum red, green, and blue color
typedef struct color{
	uint16_t r;
	uint16_t g;
	uint16_t b;
} color;
	
// struct for LEDs (color, location, and brightness)
typedef struct LED{
	color clr; //
	uint8_t loc;
	uint8_t brit;
} LED;

// global helper functions 
void init_GPIO();
void init_timers();
void init_interrupts(); 
void init_I2C();
uint16_t circumference_mm(uint8_t wheel_size_mm); 
uint16_t speed_mm_s(uint8_t time_ms, uint16_t circum);
void delay_us(uint16_t delay_us);
void delay_ms(uint16_t delay_ms);
uint8_t check_halls(uint8_t sensor);

#endif /* HELPER_FUNCTIONS_H_ */