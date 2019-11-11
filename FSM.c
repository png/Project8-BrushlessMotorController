# include "FSM.h"
//#include "InterruptServiceRoutines.h"

extern int RotaryEncoderStateCount;
extern int LEDDisplayValue;
extern unsigned int g1msTimer;
volatile unsigned int startTime;
void InitializeFSM(FSMType *FSM)
{
    FSM->CurrentState = ResetState;
}

FSMState NextStateFunction(FSMType *FSM)
{
    FSMState NextState = FSM->CurrentState;

    if(FSM->Reset){
        NextState = ResetState;
        return NextState;
    }

    switch (FSM->CurrentState) {
    case ResetState:
        if((FSM->SwitchA) && (FSM->SwitchB)){
            NextState = AActiveBActive;
        }
        else if ((FSM->SwitchA) && !(FSM->SwitchB)){
            NextState = AActiveBInactive;
        }
        else if (!(FSM->SwitchA) && (FSM->SwitchB)){
            NextState = AInactiveBActive;
        }
        else if (!(FSM->SwitchA) && !(FSM->SwitchB)){
            NextState = AInactiveBInactive;
        }
        break;

    case AInactiveBInactive:
        if((FSM->SwitchA) && !(FSM->SwitchB)){
            NextState = AActiveBInactive;
        }
        else if(!(FSM->SwitchA) && (FSM->SwitchB)){
            NextState = AInactiveBActive;
        }
        break;

    case AInactiveBActive:
        if((FSM->SwitchA) && (FSM->SwitchB)){
            NextState = AActiveBActive;
        }
        else if(!(FSM->SwitchA) && !(FSM->SwitchB)){
            NextState = AInactiveBInactive;
        }
        break;

    case AActiveBInactive:
        if((FSM->SwitchA) && (FSM->SwitchB)){
            NextState = AActiveBActive;
        }
        else if(!(FSM->SwitchA) && !(FSM->SwitchB)){
            NextState = AInactiveBInactive;
        }
        break;

    case AActiveBActive:
        if((FSM->SwitchA) && !(FSM->SwitchB)){
            NextState = AActiveBInactive;
        }
        else if(!(FSM->SwitchA) && (FSM->SwitchB)){
            NextState = AInactiveBActive;
        }
        break;

    default:
        NextState = ResetState;
    }

    return NextState;
}

void OutputFunction(FSMType *FSM)
{
    // Update RotaryEncoderStateCount
    switch (FSM->CurrentState) {
    case ResetState:
        RotaryEncoderStateCount = 0;
        g1msTimer=0;
        startTime = 0;
        break;

    case AInactiveBInactive:
        if((FSM->SwitchA) && !(FSM->SwitchB)){
            RotaryEncoderStateCount++;
        }
        else if(!(FSM->SwitchA) && (FSM->SwitchB)){
            RotaryEncoderStateCount--;
        }
        break;

    case AInactiveBActive:
        if((FSM->SwitchA) && (FSM->SwitchB)){
            RotaryEncoderStateCount--;
        }
        else if(!(FSM->SwitchA) && !(FSM->SwitchB)){
            RotaryEncoderStateCount++;
        }
        break;

    case AActiveBInactive:
        if((FSM->SwitchA) && (FSM->SwitchB)){
            RotaryEncoderStateCount++;
        }
        else if(!(FSM->SwitchA) && !(FSM->SwitchB)){
            RotaryEncoderStateCount--;
        }
        break;

    case AActiveBActive:
        if((FSM->SwitchA) && !(FSM->SwitchB)){
            RotaryEncoderStateCount--;
        }
        else if(!(FSM->SwitchA) && (FSM->SwitchB)){
           RotaryEncoderStateCount++;
        }
        break;

    default:
        RotaryEncoderStateCount = 0;
    }

    // Now, use RotaryEncoderStateCount to update the value of TA0CCR1 to modify the PWM duty cycle
    // and update the corresponding value displayed in the two 7-segment displays.
    if (FSM->CurrentState == ResetState) {
        // Insert code to initialize TA0CCR1 and the LED display value.
        LEDDisplayValue = 5;
        TA0CCR1 = STARTVAL;
    }
    else {
        volatile unsigned int elapsedTime;
        //volatile unsigned int g1msBak = g1msTimer;
        //volatile unsigned int startBak = startTime;
        //volatile unsigned int TA0CCR1Bak = TA0CCR1;
        if (RotaryEncoderStateCount == 48) { // clockwise
            // Insert code action(s) when rotary encoder has been rotated clockwise.
            //TOGGLE_GREEN_LED;
            //FSM->EncNum += 1;
            TOGGLE_GREEN_LED;
            RotaryEncoderStateCount = 0;
            elapsedTime= g1msTimer-startTime;
             if (elapsedTime > 41)
             {
                 TA0CCR1 += 1;
                 startTime = g1msTimer;
                 //g1msTimer = 0;
             }
             else
             {
                 TA0CCR1 -= 1;
                 startTime = g1msTimer;
                 //g1msTimer = 0;
             }

        }

        else if (RotaryEncoderStateCount == -48) { // counter-clockwise
            // Insert code for action(s) when rotary encoder has been rotated counter-clockwise.
            //TOGGLE_GREEN_LED;
            //FSM->EncNum -= 1;
            volatile unsigned int checktimer= g1msTimer;
            volatile unsigned int checkstart = startTime;
            RotaryEncoderStateCount = 0;
            TOGGLE_GREEN_LED;
            elapsedTime= g1msTimer-startTime;
            if (elapsedTime > 10)
            {
                TA0CCR1 += 50;
                startTime = g1msTimer;
                //g1msTimer = 0;
            }
            else
            {
                TA0CCR1 -= 50;
                startTime = g1msTimer;
                //g1msTimer = 0;
            }
        }

//        if ((int)(FSM->EncNum) == 48){
//            TOGGLE_GREEN_LED;
//            FSM->EncNum = 0;
//        }
    }
    SetLEDDisplay(LEDDisplayValue);
}
