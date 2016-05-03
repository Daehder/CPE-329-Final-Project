/*
 * CPE329_Final_Project.c
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/3/2016
 * Revision: 1.0
 */ 

#include "helper_functions.h"

int main(void)
{
	init_GPIO();		// initialize
	
    // stuck here forever
    while (1){
		if(check_halls(HALLE1))
			PORTB |= (1<<LED13);
		else
			PORTB &= ~(1<<LED13);
    }
}

