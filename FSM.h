#ifndef FSM_H_
#define FSM_H_

#include "debounce.h"
#include "LED_display.h"
#include "timerA.h"

#define MAX_DISPLAY 10
#define MIN_DISPLAY 0

#define ENC_LOOPS 48

// Type Definitions
typedef enum {AInactiveBInactive,AInactiveBActive,AActiveBInactive,AActiveBActive, ResetState} FSMState;

typedef struct {
    FSMState CurrentState;  // Current state of the FSM
    SwitchStatus SwitchA;   // Current input of the FSM
    SwitchStatus SwitchB;   // Current input of the FSM
    SwitchStatus Reset;   // Current input of the FSM
    unsigned char EncNum;
} FSMType;

// Function Prototypes
void InitializeFSM(FSMType *FSM);
FSMState NextStateFunction(FSMType *FSM);
void OutputFunction(FSMType *FSM);

#endif /* FSM_H_ */

