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

#define PI 3.141592			// mathematical pi
#define NUM_HALLS 6			// number of hall effects on wheel
#define WHL_DIAM_UM 660000	// diameter of bike wheel in mm

// global libraries
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// struct for color spectrum red, green, and blue color
typedef struct color{
	uint8_t r;
	uint8_t g;
	uint8_t b;
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
void init_variables(); 
void init_I2C();
uint32_t circumference_mm(uint16_t wheel_size_mm); 
uint32_t speed_mm_us(uint32_t dist_mm, uint32_t time_us);
void delay_us(uint16_t delay_us);
void delay_ms(uint16_t delay_ms);
uint8_t check_halls(uint8_t sensor);
uint16_t tcnt1_to_us();

#endif /* HELPER_FUNCTIONS_H_ */