
#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include "TinyTimber.h"
#include "Pulse.h"
#include "HoldButton.h"

typedef struct {
	Object super;
	Pulse *currentPulse;
	Pulse *nextPulse;
	HoldButton *holdButton;
} InputHandler;

#define  initInputHandler(currentPulse, nextPulse, holdButton) {initObject(), currentPulse, nextPulse, holdButton}

int inputRecieved(InputHandler *self, int arg);

#endif