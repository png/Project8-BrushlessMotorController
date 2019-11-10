# include "FSM.h"

extern int RotaryEncoderStateCount;
extern int LEDDisplayValue;

void InitializeFSM(FSMType *FSM)
{
    FSM->CurrentState = ResetState;
}

FSMState NextStateFunction(FSMType *FSM)
{
    FSMState NextState = FSM->CurrentState;;

    switch (FSM->CurrentState) {
    case ResetState:
        //if a inactive and b inactive
        if ((FSM->SwitchA == Inactive) && (FSM->SwitchB == Inactive)){
            NextState = AInactiveBInactive;
        }
        //if a inactive and b active
        else if ((FSM->SwitchA == Inactive) && (FSM->SwitchB == Active)){
            NextState = AInactiveBActive;
        }
        //if a active and b inactive
        else if ((FSM->SwitchA == Active) && (FSM->SwitchB == Inactive)){
            NextState= AActiveBInactive;
        }
        //if a active and b active
        else if ((FSM->SwitchA == Active) && (FSM->SwitchB == Active)){
        NextState = AActiveBActive;
        }
        break;

    case AInactiveBInactive:
        // if a active and b inactive
        if ((FSM->SwitchA == Active) && (FSM->SwitchB == Inactive)){
            NextState = AActiveBInactive;
        }
        // if a inactive and b active
        else if ((FSM->SwitchA == Inactive) && (FSM->SwitchB == Active)){
            NextState = AInactiveBActive;
        }
        //else
        else{
        NextState = AInactiveBInactive;
        }
        break;

    case AInactiveBActive:
        // if a active and b active
        if ((FSM->SwitchA == Active) && (FSM->SwitchB == Active)){
            NextState = AActiveBActive;
        }
        //if a inactive and b inactive
        else if ((FSM->SwitchA == Inactive) && (FSM->SwitchB == Inactive)){
            NextState = AInactiveBInactive;
        }
        //else
        else{
            NextState = AInactiveBActive;
        }
        break;

    case AActiveBInactive:
        // if a active and b active
        if ((FSM->SwitchA == Active) && (FSM->SwitchB == Active)){
            NextState = AActiveBActive;
        }
        //if a inactive and b inactive
        else if ((FSM->SwitchA == Inactive) && (FSM->SwitchB == Inactive)){
            NextState = AInactiveBInactive;
        }
        //else
        else{
            NextState = AActiveBInactive;
        }
        break;

    case AActiveBActive:
        // if a active and b inactive
        if ((FSM->SwitchA == Active) && (FSM->SwitchB == Inactive)){
            NextState = AActiveBInactive;
        }
        // if a inactive and b active
        else if ((FSM->SwitchA == Inactive) && (FSM->SwitchB == Active)){
            NextState = AInactiveBActive;
        }

        //else
        else{
            NextState = AActiveBActive;
        }
        break;

    default:
        NextState = ResetState;
    }
    if(FSM->Reset == Active){
        NextState = ResetState;
    }

    return NextState;

}

void OutputFunction(FSMType *FSM)
{
    if (FSM->CurrentState == ResetState) {
        // Insert code to initialize TA0CCR1 and the LED display value.
        TA0CCR1 = 8000;
        LEDDisplayValue = 5;
        __nop();
    }
    // Update RotaryEncoderStateCount
    switch (FSM->CurrentState) {
    case ResetState:
        RotaryEncoderStateCount = 0;
        break;
    case AInactiveBInactive:

        if(FSM->SwitchA == Inactive && FSM->SwitchB == Active){
            RotaryEncoderStateCount++;
           // FSM->SwitchB = 0;
        }
        else if(FSM->SwitchA == Active && FSM->SwitchB == Inactive){
            RotaryEncoderStateCount--;
           // FSM->SwitchA = 0;
        }
        break;
    case AInactiveBActive:
        if(FSM->SwitchA == Active && FSM->SwitchB == Active){
            RotaryEncoderStateCount++;
           // FSM->SwitchA = Inactive;
        }
        else if(FSM->SwitchA == Inactive && FSM->SwitchB == Inactive){
            RotaryEncoderStateCount--;
            //FSM->SwitchB = 1;
        }
        break;
    case AActiveBInactive:
        if(FSM->SwitchA == Inactive && FSM->SwitchB == Inactive){
            RotaryEncoderStateCount++;
            //FSM->SwitchA = Active;
        }
        else if(FSM->SwitchA == Active && FSM->SwitchB == Active){
            RotaryEncoderStateCount--;
            //FSM->SwitchB = 0;
        }

        break;
    case AActiveBActive:
        if(FSM->SwitchA == Inactive && FSM->SwitchB == Active){
            RotaryEncoderStateCount--;
            //FSM->SwitchA = Active;
        }
        else if(FSM->SwitchA == Active && FSM->SwitchB == Inactive){
            RotaryEncoderStateCount++;
            //FSM->SwitchB = Active;
        }

        break;
    default:
        RotaryEncoderStateCount = 0;
    }

    // Now, use RotaryEncoderStateCount to update the value of TA0CCR1 to modify the PWM duty cycle
    // and update the corresponding value displayed in the two 7-segment displays.
    if (FSM->CurrentState == ResetState) {
        // Insert code to initialize TA0CCR1 and the LED display value.
        TA0CCR1 = 8000;
        LEDDisplayValue = 5;
        __nop();
    }
    else {
        if (RotaryEncoderStateCount == 48) { // clockwise
            // Insert code action(s) when rotary encoder has been rotated clockwise.
//            if(LEDDisplayValue < DISPLAY_LIMIT){
//                LEDDisplayValue++;
//                TA0CCR1 += TA0CCR0/DISPLAY_LIMIT;
//            }
            RotaryEncoderStateCount = 0;
            TOGGLE_GREEN_LED;
        }

        if (RotaryEncoderStateCount == -48) { // counter-clockwise
            // Insert code for action(s) when rotary encoder has been rotated counter-clockwise.
//            if(LEDDisplayValue > 0){
//                LEDDisplayValue--;
//                TA0CCR1 -= TA0CCR0/DISPLAY_LIMIT;
//            }
            RotaryEncoderStateCount = 0;
            TOGGLE_GREEN_LED;
        }
    }
    //SetLEDDisplay(LEDDisplayValue);
}
