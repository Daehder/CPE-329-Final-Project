/*
 * RGBDriver.c
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/16/2016
 * Revision: 1.0
 */

#ifndef RGBDriver_h
#define RGBDriver_h

#include <stdio.h>
#include "helper_functions.h"

//typedef struct color{       // Debugging stuff for use in xcode, do not add when adding to arduino
//   uint16_t r;
//   uint16_t g;
//   uint16_t b;
//} color;

/* Sets up the TWI registers to prepare for transmission */
void initRGB();
int sendLED(color clr, int led);

//#define TW_START = 0xDE      // Debugging stuff for use in xcode, do not add when adding to arduino


#endif /* RGBDriver_h */
