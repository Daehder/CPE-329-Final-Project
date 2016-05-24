/*
 * RGBDriver.c
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/16/2016
 * Revision: 1.0
 */
//#include "helper_functions.h"
#include "RGBDriver.h"

#define NUM_BYTES 24  /* The number of bytes sent to the TI LED controller */
//#define TLC_NUM 1

#define NIBBLE_MASK 0xF /* A mask that only exposes a nibble */
#define BYTE_MASK 0xFF  /* A mask that only exposes the bottom byte */
#define TWELVE_BIT_MASK 0xFFF /* A mask that exposes the grayscale value */
#define BYTE 8    /* Bits */

/*
#define MOSI 4  // PB pin 3
#define SCK  5  // PB pin 5
#define SS   0  // PB pin 2
*/

#define LED_CONFIG	(DDRD |= (1<<PD6))
#define LED_ON (PORTD |= (1<<PD6))
#define LED_OFF (PORTD &= ~(1<<PD6))
#define LED_TOGGLE (PORTD ^= (1<<PD6))

/* Set MOSI and SCK output, all others input */
//#define initIO 1


void updateLEDs();
void sendByte(unsigned char);

unsigned char shiftReg[NUM_BYTES];

void gsConvert(int data, int led) {
   int ndx = (led * 12) / 8;
   int offset = (led * 12) % 8;
   int mask = BYTE_MASK >> offset;
   
   shiftReg[ndx] &= ~(mask << offset);
   shiftReg[ndx] |= ((data & mask) << offset);
   
   if(mask == NIBBLE_MASK)
      mask = BYTE_MASK;
   else
      mask = NIBBLE_MASK;
   
   offset = 8 - offset;
   
   shiftReg[++ndx] &= ~(mask);
   shiftReg[ndx] |= ((data >> offset & mask));
}

/* Sets up the TWI registers to prepare for transmission */
void initRGB() {
   DDRB |= (1<<MOSI)|(1<<SCLK);
   SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
   
   for(int i=0; i<(TLC_NUM*24); i++){
	   shiftReg[i] = 0;
   }

}

/* Sets LED number led to color clr */
int sendLED(color clr, int led) {
   int rVal = clr.r;
   int gVal = clr.g;
   int bVal = clr.b;
   
   if (led > 4 || led < 0) {
      return -2;  // LED is out of range
   }
   
   led *= 3;
   
   gsConvert(rVal, led);
   gsConvert(gVal, ++led);
   gsConvert(bVal, ++led);
   
   updateLEDs();
   
   return 0;
}

void updateLEDs() {
   int ndx;
   
   PORTB |= (1 << BLANK);
   
   for (ndx = NUM_BYTES-1; ndx >= 0; ndx--)
      sendByte(shiftReg[ndx]);
	  
   PORTB &= ~(1 << BLANK);
   PORTB_pulse(XLAT);
}

void sendByte(unsigned char data) {  
   /* Start transmission */
   SPDR = data;
   /* Wait for transmission complete */
   while(!(SPSR & (1<<SPIF))) {
   }
}