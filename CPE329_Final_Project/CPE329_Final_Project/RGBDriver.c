/*
 * RGBDriver.c
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/16/2016
 * Revision: 1.0
 */

#include "RGBDriver.h"

#define NUM_BYTES 24  /* The number of bytes sent to the TI LED controller */
//#define WRITE_COMMAND_BITS 0x25   /* As defined by TI's datasheet */

//#define OUTTMG 1  /* Bit 217, or the 1st bit of the 28th byte */
//#define EXTGCK 0  /* Bit 216, or the 0th bit of the 28th byte */
//
//#define TMGRST 7  /* Bit 215, or the 7th bit of the 27th byte */
//#define DSPRPT 6  /* Bit 214, or the 6th bit of the 27th byte */
//#define BLANK 5   /* Bit 213, or the 5th bit of the 27th byte */

#define NIBBLE_MASK = 0xF /* A mask that only exposes a nibble */
#define BYTE_MASK 0xFF  /* A mask that only exposes the bottom byte */
#define TWELVE_BIT_MASK 0xFFF /* A mask that exposes the grayscale value */
#define BYTE 8    /* Bits */


#define MOSI 2  // PB pin 3
#define SCK  1  // PB pin 5
#define SS   0  // PB pin 2

#define LED_CONFIG	(DDRD |= (1<<PD6))
#define LED_ON (PORTD |= (1<<PD6))
#define LED_OFF (PORTD &= ~(1<<PD6))
#define LED_TOGGLE (PORTD ^= (1<<PD6))

/* Set MOSI and SCK output, all others input */
#define initIO (DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS))

//#define gsTopByte(bytes) (((bytes) >> BYTE) & BYTE_MASK)
//#define gsBottomByte(bytes) ((bytes) & BYTE_MASK)
//
//#define bcgTop(bcg) (((bcg) >> 1) & 0x3F)
//#define bcgBottom(bcg) ((bcg) & 0x01)
//#define BCG_BOTTOM 7
//
//#define bcbTop(bcb) (((bcb) >> 2) & 0x1F)
//#define bcbBottom(bcb) ((bcb) & 0x03)
//#define BCB_BOTTOM 6

#define BCR 0x3F
#define BCG 0x3F
#define BCB 0x3F

void updateLEDs();
void sendByte(unsigned char);

unsigned char shiftReg[NUM_BYTES];


 int TWBR;      // Debugging stuff for use in xcode, do not add when adding to arduino
 int TWSR;
 int TWCR;
int TWINT;
 int TWSTA;
 int TWEN;
 int TWDR;


void gsConvert(int data, int led) {
   int ndx = (led * 12) / 8;
   int offset = (led * 12) % 8;
   int mask = BYTE_MASK >> offset;
   
   shiftReg[ndx] = ((data & mask) << offset);
   
   if(mask == NIBBLE_MASK) {
      mask = BYTE_MASK;
      offset = 0;
   }
   else {
      mask = NIBBLE_MASK;
      offset = 4;
   }
   
   shiftReg[++ndx] = ((data & mask) << offset);
}

/* Sets up the TWI registers to prepare for transmission */
void initRGB() {
   initIO;
//   TWBR = 0x12;   /* Sets SCL to 50 kHz */
//   TWSR = 0x01;   /* Sets the overflow bit to set the frequency of the SCL
//                   * SCL freq = (CPU freq)/(16 + 2*TWBR*4^TWPS)
//                   * 8*10^6/(16+2*18*4^1) = 50000 hz
//                   */
   
   //    SPCR = (0<<SPIE) |     //No interrupts
   //    (1<<SPE) |             //SPI enabled
   //    (0<<DORD) |         //send MSB first
   //    (1<<MSTR) |         //master
   //    (0<<CPOL) |         //clock idles low
   //    (1<<CPHA) |         //sample leading edge
   //    (0<<SPR1) | (0<<SPR0) ; //clock speed
   //    SPSR = (0<<SPIF) |     //SPI interrupt flag
   //    (0<<WCOL) |         //Write collision flag
   //    (0<<SPI2X) ;        //Doubles SPI clock
   
   
   PORTB |= 1 << SS;       // make sure SS is high
   
   /* Enable SPI, Master, set clock rate fck/16 */
   SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
   
   /* GSR0 */
   shiftReg[0] = 0;
   shiftReg[1] = 0;
   
   /* GSG0 */
   shiftReg[2] = 0;
   shiftReg[3] = 0;
   
   /* GSB0 */
   shiftReg[4] = 0;
   shiftReg[5] = 0;
   
   /* GSR1 */
   shiftReg[6] = 0;
   shiftReg[7] = 0;
   
   /* GSG1 */
   shiftReg[8] = 0;
   shiftReg[9] = 0;
   
   /* GSB1 */
   shiftReg[10] = 0;
   shiftReg[11] = 0;
   
   /* GSR2 */
   shiftReg[12] = 0;
   shiftReg[13] = 0;
   
   /* GSG2 */
   shiftReg[14] = 0;
   shiftReg[15] = 0;
   
   /* GSB2 */
   shiftReg[16] = 0;
   shiftReg[17] = 0;
   
   /* GSR3 */
   shiftReg[18] = 0;
   shiftReg[19] = 0;
   
   /* GSG3 */
   shiftReg[20] = 0;
   shiftReg[21] = 0;
   
   /* GSB3 */
   shiftReg[22] = 0;
   shiftReg[23] = 0;
//   
//   /* BCG 0 | BCR 6:0 */
//   shiftReg[24] = ((bcgTop(BCG) << BCG_BOTTOM) | (BCR & 0x7F));
//   
//   /* BCB 1:0 | BCG 6:1 */
//   shiftReg[25] = ((bcbBottom(BCB) << BCB_BOTTOM) | bcgTop(BCG));
//   
//   /* TMGRST | DSPRPT | BLANK | BCB 6:2 */
//   shiftReg[26] = (~(1 << TMGRST) & ~(1 << DSPRPT) & ~(1 << BLANK) &
//                   bcbTop(BCB));
//   
//   /* WRITE_COMMAND_BITS (0x25) | OUTTMG | EXTGCK */
//   shiftReg[27] = ((WRITE_COMMAND_BITS << 2) & ~(1 << OUTTMG) &
//                  ~(1 << EXTGCK));
   
   
//   // send start condition
//   TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
//   
//   // check if status is no "start"
//   if( (TWSR & 0xF8) != TW_START ) {
//      return -1; // error has occured
//   }
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
//   /* GSR(led) */
//   shiftReg[rBytes] = gsBottomByte(clr.r);
//   shiftReg[++rBytes] = gsTopByte(clr.r);
//   
//   /* GSG(led) */
//   shiftReg[gBytes] = gsBottomByte(clr.g);
//   shiftReg[++gBytes] = gsTopByte(clr.g);
//   
//   /* GSB(led) */
//   shiftReg[bBytes] = gsBottomByte(clr.b);
//   shiftReg[++bBytes] = gsTopByte(clr.b);
   
   
//   // slave address to write to
//   TWDR = (0x74<<1) | TW_WRITE;
   
//   TWCR = (1<<TWINT) | (1<<TWEN);
//   
//   while( !(TWCR & (1<<TWINT)) ){
//      
//   }
//   
//   if( (TWSR & 0xF8) != TW_MT_SLA_ACK ){
//      return -1;
//   }
   
   updateLEDs();
   
   return 0;
}

void updateLEDs() {
   int ndx;
   
   for (ndx = 0; ndx < NUM_BYTES; ndx++)
      sendByte(shiftReg[ndx]);
}

void sendByte(unsigned char data) {
//   TWDR = data;
//   
//   TWCR = (1<<TWINT) | (1<<TWEN);
//   
//   while( !(TWCR & (1<<TWINT)) ){
//      
//   }
   PORTB &= ~(1 << SS);        // assert the slave select
   
   /* Start transmission */
   SPDR = Data;
   /* Wait for transmission complete */
   while(!(SPSR & (1<<SPIF))) {
//      LED_TOGGLE;
//      _delay_us(10000);
   }
   
   PORTB |= 1 << SS;        // deassert the slave select
}