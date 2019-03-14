/*
 * HoldButton.c
 *
 * Created: 2019-03-11 16:54:52
 *  Author: jonjac-6
 */ 

#include "HoldButton.h"

#include <avr/io.h>
#include <math.h>
#include <stdint.h>


int holdUp(HoldButton *self, int arg){
	
	if (!((PINB >> PINB6) & 1U)) {//up
		ASYNC(self->currentPulse, increseValue, 0);
		AFTER(MSEC(100), self, holdUp, 0);
	}
	return 0;
}


int holdDown(HoldButton *self, int arg){
	
	if (!((PINB >> PINB7) & 1U)) {//down
		ASYNC(self->currentPulse, lowerValue, 0);
		AFTER(MSEC(100), self, holdDown, 0);
	}
	return 0;
}



int checkIfHoldButton(HoldButton *self, int arg){
	
	if (arg == 1){
		AFTER(MSEC(350), self, holdUp, 0);	
	}else if(arg == 2){
		AFTER(MSEC(350), self, holdDown, 0);	
	}
	return 0;
}


int switchPulse(HoldButton *self, int arg){
	Pulse *temp = self->currentPulse;
	self->currentPulse = self->nextPulse;
	self->nextPulse = temp;
	SYNC(self->currentPulse, togglePulse, 0);
	return 0;
}

