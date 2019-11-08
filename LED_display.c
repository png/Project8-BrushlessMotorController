#include "LED_display.h"

// This array contains the hexadecimal character required to display the corresponding
// hexadecimal digit on the 7-segment display.
const unsigned char LEDDisplayCharacters[16] = {
		0x3F, // 0
		0x06, // 1
		0x5B, // 2
		0x4F, // 3
		0x66, // 4
		0x6D, // 5
		0x7D, // 6
		0x07, // 7
		0x7F, // 8
		0x67, // 9
		0x77, // A
		0x7C, // B
		0x39, // C
		0x5E, // D
		0x79, // E
		0x71  // F
};

void InitializeLEDDisplay(void)
{
    //Initialize pins
    //pin 1.4 -- blank
    SET_LED_BLANK_AS_AN_OUTPUT;
    TURN_ON_LEDS;

    //pin 1.5 -- sclk -- spi.c

    //pin 2.0 -- latch 1
    SET_LED_LATCH_AS_AN_OUTPUT;
    TURN_OFF_LED_LATCH;

}

void SetLEDDisplay(unsigned int DisplayValue)
{
    unsigned int DisplayHex = getHex(DisplayValue);
    unsigned char lower = (unsigned char)DisplayHex;
    unsigned char upper = (unsigned char) (DisplayHex>>8);
    SPISendByte(lower); // lower first
    SPISendByte(upper); // then upper
    TURN_ON_LED_LATCH;
    TURN_OFF_LED_LATCH;

}

unsigned int getHex(unsigned char val){
    //while loop to mod
    unsigned char ones = val;
    unsigned char tens = 0;
    while(ones >= 10){
        ones -= 10;
        tens += 1;
    }
    unsigned int ret = (LEDDisplayCharacters[tens] << 8) | (LEDDisplayCharacters[ones]);
    return ret;
}

