/*
 * helper_functions.h
 *
 * Created: 5/3/2016 12:03:39 AM
 *  Author: mytch
 */ 


#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

// global defines 

// micro controller I/O 
#define F_CPU 16000000	// CPU clock frequency 
#define HALLE0 7		// Hall effect sensor at PD7
#define HALLE1 6		// Hall effect sensor at PD6
#define HALLE2 5		// Hall effect sensor at PD5
#define LED13 5			// on-board LED at PB5

// TLC5946 input pins (needs to be edited)
#define MODE 2
#define XLAT 6
#define MOSI 3		// SIN
#define BLANK 4
#define SCLK 5
#define GSCLK 3

// real world values
#define PI 3.141592			// mathematical pi
#define NUM_HALLS 3			// number of hall effects on wheel
#define WHL_DIAM_UM 660000	// diameter of bike wheel in mm
#define TLC_NUM 1			// number of TLC5946 chips

// global libraries
#include <avr/io.h>
#include <util/delay.h>
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
void init_variables(); 
uint32_t circumference_mm(uint16_t wheel_size_mm); 
uint32_t speed_mm_us(uint32_t dist_mm, uint32_t time_us);
void delay_us(uint16_t delay_us);
void delay_ms(uint16_t delay_ms);
uint8_t check_halls(uint8_t sensor);
uint16_t tcnt1_to_us();

void setAllDC(uint8_t value);
void PORTB_pulse(uint8_t pin);
void trans_SPI(uint8_t SPI_byte);
void setAllGS(uint16_t value);

#endif /* HELPER_FUNCTIONS_H_ */