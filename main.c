#include <motor.h>
#include <msp430.h>
#include "LED.h"
#include "pushbutton.h"
#include "spi.h"
#include "timerA.h"
#include "debounce.h"
#include "FSM.h"
#include "LED_display.h"
#include "InterruptServiceRoutines.h"

// Global Variables
unsigned int g1msTimer; // Global 1 ms timer used for pushbutton debounce.
int RotaryEncoderStateCount; // Indicates valid FSM sequences.
int LEDDisplayValue; // Indicates value to display in the 7-segment displays

#define FALSE 0
#define TRUE 1

// Function Prototypes
void ConfigureClockModule();
SwitchStatus DebounceSwitch(SwitchDefine *Switch);

int main(void)
{
	FSMType RotaryEncoder_FSM;
    SwitchDefine RotaryEncoderReset;
    SwitchDefine RotaryEncoderSwitchA;
    SwitchDefine RotaryEncoderSwitchB;

	WDTCTL = WDTPW | WDTHOLD;
	// Stop watchdog timer
    ConfigureClockModule();

    // Initialize hardware.
    ConfigureTimerA();
	InitializeLEDPortPins();
	InitializePushButtonPortPin();
	InitializeRotaryEncoderPortPins();
	InitializeSPI();
	InitializeLEDDisplay();

    // Initialize Finite State Machine (FSM) state variables.
	InitializeFSM(&RotaryEncoder_FSM);

    // Initialize active-low switch for pushbutton.
    InitializeSwitch(&RotaryEncoderReset,(char *) &PUSHBUTTON_PORT_IN,(unsigned char) PUSHBUTTON_BIT,
            Active, Inactive, ACTIVE_THRESHOLD,INACTIVE_THRESHOLD);

    // Initialize active-low switches for rotary encoder.
    InitializeSwitch(&RotaryEncoderSwitchA,(char *) &P2IN,(unsigned char) BIT4,
            Active, Inactive, ACTIVE_THRESHOLD,INACTIVE_THRESHOLD);
    InitializeSwitch(&RotaryEncoderSwitchB,(char *) &P2IN,(unsigned char) BIT3,
            Active, Inactive, ACTIVE_THRESHOLD,INACTIVE_THRESHOLD);

    _enable_interrupts();

	// Loop forever
	while(TRUE) {

	    // Read inputs. Note that if bouncing is an issue, you may have to debounce
	    // the inputs using the DebounceSwitch() function instead of ReadSwitchStatus().
	    RotaryEncoder_FSM.Reset = ReadSwitchStatus(&RotaryEncoderReset);
	    RotaryEncoder_FSM.SwitchA = ReadSwitchStatus(&RotaryEncoderSwitchA);
        RotaryEncoder_FSM.SwitchB = ReadSwitchStatus(&RotaryEncoderSwitchB);

        // Adjust the PWM duty cycle in TA0CCR1 and update the LED display value.
        OutputFunction(&RotaryEncoder_FSM);
        //SetLEDDisplay(LEDDisplayValue);

        // Determine the next state for the rotary encoder FSM.
	    RotaryEncoder_FSM.CurrentState = NextStateFunction(&RotaryEncoder_FSM);
	}
	return 0;
}

SwitchStatus DebounceSwitch(SwitchDefine *Switch)
{
    unsigned char X1;
    unsigned char X0;
    SwitchStatus CurrentSwitchReading;
    unsigned int ElapsedTime = 0;

    // First, determine the current inputs, X1 and X0.
    ElapsedTime = (unsigned int) (g1msTimer-Switch->EventTime);
    X1 = FALSE;
    if (Switch->CurrentState == ValidateActive) {
        if (ElapsedTime > Switch->ActiveThreshold) {X1 = TRUE;}
    }
    else if (Switch->CurrentState == ValidateInactive){
        if (ElapsedTime > Switch->InactiveThreshold) {X1 = TRUE;}
    }

    CurrentSwitchReading = ReadSwitchStatus(Switch);
    X0 = FALSE;
    if (CurrentSwitchReading == Active) {X0 = TRUE;}

    // Perform the output function based on the inputs and current state.
    OutputFunctionDebounce(Switch,X0,X1);

    // Next, based on the input values and the current state, determine the next state.
    Switch->CurrentState = NextStateFunctionDebounce(Switch,X0,X1);

    return Switch->DebouncedSwitchStatus;
}

void ConfigureClockModule()
{
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations
    DCOCTL  = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
}
