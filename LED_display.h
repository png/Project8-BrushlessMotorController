#ifndef LED_DISPLAY_H_
#define LED_DISPLAY_H_

#include <msp430.h>
#include "spi.h"

#define LED_BLANK_PIN               4
#define LED_BLANK_BIT               BIT4
#define LED_BLANK_PORT              P1OUT
#define LED_BLANK_DDR               P1DIR
#define SET_LED_BLANK_AS_AN_OUTPUT  LED_BLANK_DDR |= LED_BLANK_BIT
#define TURN_OFF_LEDS               LED_BLANK_PORT |= LED_BLANK_BIT
#define TURN_ON_LEDS                LED_BLANK_PORT &= ~LED_BLANK_BIT
#define TOGGLE_LED_BLANK            LED_BLANK_PORT ^= LED_BLANK_BIT

#define LED_LATCH_PIN               0
#define LED_LATCH_BIT               BIT0
#define LED_LATCH_PORT              P2OUT
#define LED_LATCH_DDR               P2DIR
#define SET_LED_LATCH_AS_AN_OUTPUT  LED_LATCH_DDR |= LED_LATCH_BIT
#define TURN_ON_LED_LATCH           LED_LATCH_PORT |= LED_LATCH_BIT
#define TURN_OFF_LED_LATCH          LED_LATCH_PORT &= ~LED_LATCH_BIT
#define TOGGLE_LED_LATCH            LED_BLANK_PORT ^= LED_BLANK_BIT

// Function Prototypes
void InitializeLEDDisplay(void);
/*
 * This function configures and initializes all of the pins associated with the 7-segment displays.
 */

void SetLEDDisplay(unsigned int DisplayValue);
/*
 * Given as an input DisplayValue, this function will determine the correct digits to display in the
 * two 7-segment displays, and then use this information to send the appropriate information to the
 * LED display drivers.
 */
unsigned int getHex(unsigned char val);

#endif /* LED_DISPLAY_H_ */
