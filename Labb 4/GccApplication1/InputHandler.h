
#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include "TinyTimber.h"
#include "Pulse.h"

typedef struct {
	Object super;
	Pulse *currentPulse;
	Pulse *nextPulse;
} InputHandler;

#define  initInputHandler(currentPulse,nextPulse) {initObject(),currentPulse,nextPulse}

int inputRecieved(InputHandler *self, int arg);

#endif