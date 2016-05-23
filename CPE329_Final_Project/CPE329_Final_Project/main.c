/*
 * CPE329_Final_Project.c
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/3/2016
 * Revision: 1.0
 */ 

#include "helper_functions.h"

// Global Variables
volatile uint16_t hall_dl = 0;		// distance between halls
volatile uint32_t hall_dt = 0;		// time between hall effect readings (us)
volatile uint32_t hall_dt_last = 0;	// previous hall_dt reading

int main(void)
{
	init_GPIO();
	init_timers();
	sei();
	//hall_dl = (circumference_mm(WHL_DIAM_UM) / NUM_HALLS);
	
    // stuck here forever
    while(1){		
	
    }
}

//////////////////////////////////ISR//////////////////////////////////////////

// PCINT1_vect and PCINT2_vect use the same ISR, PCINT0_vect
ISR_ALIAS(PCINT1_vect, PCINT0_vect);
ISR_ALIAS(PCINT2_vect, PCINT0_vect);

// enter ISR when timer1 overflows in normal mode (4096 us ~ 244Hz)
ISR(TIMER1_OVF_vect){
	// time between reading increases by 4096us
	hall_dt += 4096;
}

// enter ISR whenever a hall effect sensor is read
ISR(PCINT0_vect){
	hall_dt = (hall_dt + tcnt1_to_us());				// add remaining tcnt1 time to hall_dt
	
	// bike is slowing down
	if(hall_dt > hall_dt_last){
		// increase brightness
		
	}
	// bike is speeding up or not changing speed
	else{
		// decrease / maintain brightness
		
	}
	
	// update time variables
	hall_dt_last = hall_dt;		// update last hall reading time
	hall_dt = 0;				// reset hall effect reading time interval 
}