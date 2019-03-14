
#include "InputHandler.h"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>


int inputRecieved(InputHandler *self, int arg) {
	
	Pulse *pulse = self->currentPulse;
	
	if (!((PINB >> PINB4) & 1U)) {//enter
		ASYNC(pulse, switchValue, 0);
	}
	
	if (!((PINB >> PINB6) & 1U)) {//up
		ASYNC(pulse, increseValue, 0);
		ASYNC(self->holdButton, checkIfHoldButton, 1);
	}
	
	if (!((PINB >> PINB7) & 1U)) {//down
		ASYNC(pulse, lowerValue, 0);
		ASYNC(self->holdButton, checkIfHoldButton, 2);
	}
	
	if (!((PINE >> PCINT2) & 1U)) {//left
		self->currentPulse = self->nextPulse;
		self->nextPulse = pulse;
		pulse = self->currentPulse;
		ASYNC(self->holdButton, switchPulse, 0);
	}
	
	if (!((PINE >> PCINT3) & 1U)) {//right
		self->currentPulse = self->nextPulse;
		self->nextPulse = pulse;
		pulse = self->currentPulse;
		ASYNC(self->holdButton, switchPulse, 0);
	}
	
	return 0;
}
