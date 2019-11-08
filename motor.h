#ifndef MOTOR_H_
#define MOTOR_H_

#include <msp430.h>

#define STNDBY_PIN               1
#define STNDBY_BIT               BIT1
#define STNDBY_PORT              P1OUT
#define STNDBY_DDR               P1DIR
#define SET_STNDBY_AS_AN_OUTPUT  STNDBY_DDR |= STNDBY_BIT

#define PWM_PIN               2
#define PWM_BIT               BIT2
#define PWM_PORT              P1OUT
#define PWM_DDR               P1DIR
#define SET_PWM_AS_AN_OUTPUT  PWM_DDR |= PWM_BIT

#define RENC_1_PIN               4
#define RENC_1_BIT               BIT4
#define RENC_1_PORT              P2OUT
#define RENC_1_DDR               P2DIR
#define SET_RENC_1_AS_AN_INPUT   RENC_1_DDR &= ~RENC_1_BIT

#define RENC_2_PIN               3
#define RENC_2_BIT               BIT3
#define RENC_2_PORT              P2OUT
#define RENC_2_DDR               P2DIR
#define SET_RENC_2_AS_AN_INPUT   RENC_2_DDR &= ~RENC_2_BIT


#define ROTARY_ENCODER_BOUNCE_TIME_MAX 5

// Function Prototypes
void InitializeRotaryEncoderPortPins(void);
/*
 *  * This function configures and initializes all of the pins associated with the rotary encoder.
 */

#endif /* MOTOR_H_ */
