/*
 * Run.c
 *
 * Created: 2019-03-12 18:05:21
 *  Author: jonjac-6
 */ 

#include "Run.h"

int startupSequence(Run *self, int arg){
	
	//Start up the screen
	ASYNC(self->pulse1, switchValue, 0);
	ASYNC(self->pulse2, switchValue, 0);
	ASYNC(self->pulse1, togglePulse, 0);
	
	//Start a loop for the pulses.
	ASYNC(self->pulse1, runPulse, 0);
	ASYNC(self->pulse2, runPulse, 0);
	
	return 0;
}