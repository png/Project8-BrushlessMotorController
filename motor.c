#include <motor.h>

void InitializeRotaryEncoderPortPins(void)
{
    SET_RENC_1_AS_AN_INPUT;
    SET_RENC_2_AS_AN_INPUT;
    SET_STNDBY_AS_AN_OUTPUT;
    SET_PWM_AS_AN_OUTPUT;

    P1SEL |= PWM_BIT;

    STNDBY_PORT |= STNDBY_PIN;
    PWM_PORT |= PWM_PIN;
}
