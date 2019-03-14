/*
 * HoldButton.h
 *
 * Created: 2019-03-11 16:55:06
 *  Author: jonjac-6
 */ 


#ifndef _HOLDBUTTON_
#define _HOLDBUTTON_

#include "Pulse.h"
#include "TinyTimber.h"

typedef struct {
	Object super;
	Pulse *currentPulse;
	Pulse *nextPulse;
} HoldButton;

#define initHoldButton(currentPulse, nextPulse) {initObject(), currentPulse, nextPulse}

int checkIfHoldButton(HoldButton *self, int arg);
int switchPulse(HoldButton *self, int arg);
int holdUp(HoldButton *self, int arg);
int holdDown(HoldButton *self, int arg);

#endif
