/*

R(IREF) ~ 2k55 ohms

*/
#include "helper_functions.h"

// pulses a pin up and back down
void PORTB_pulse(uint8_t pin){
	PORTB |= (1<<pin);		// set pin high
	PORTB &= ~(1<<pin);		// set pin low
}

// sends 1 byte of data over SPI 
void trans_SPI(uint8_t SPI_byte){
	SPDR = SPI_byte; 			 	// starts transmission
    while (!(SPSR & _BV(SPIF))); 	// wait for transmission complete
}

// sets he DC value for every channel for 1+ TLC chip(s)
void setAllDC(uint8_t value){
	// make sure your set value is valid
	if(value>63)
		value = 63;
	
    PORTB |= (1<<MODE);			// set mode high (DC mode)

	// set up 6bit to 8bit pattern to fill SPDR
    uint8_t firstByte = value << 2 | value >> 4;
    uint8_t secondByte = value << 4 | value >> 2;
    uint8_t thirdByte = value << 6 | value;

	// send 8bit bytes through SPI SPDR
    for (uint8_t i = 0; i < (TLC_NUM*12 - 1); i += 3) {
        trans_SPI(firstByte);
        trans_SPI(secondByte);
        trans_SPI(thirdByte);
    }
	
	PORTB_pulse(XLAT);			// pulse XLAT pin 	

	PORTB &= ~(1<<MODE);		// set mode high (GS mode)
}

// sends the GS data to the TLC chip over SPI
// XLAT needs to be added here
void setAllGS(uint16_t value){
	// make sure you value is valid
	if(value>4095)
		value = 4095;
	
	PORTB &= ~(1<<MODE);		// set mode low (GS mode)
	
	// set up 12 bit to 8 bit pattern to fill SPDR
	uint8_t firstByte = (value >> 4);
	uint8_t secondByte = (value << 4) | (value >> 8);
	
	// send each byte into the SPDR
	// needs XLAT between every 12 bits
	for(uint8_t i = 0; i<(TLC_NUM*24 - 1); i++){
		SPI_byte(firstByte);	
		SPI_byte(secondByte);
	}
	
	PORTB_pulse(XLAT);			// pulse XLAT pin
	
}