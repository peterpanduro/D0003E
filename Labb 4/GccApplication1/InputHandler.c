
#include "InputHandler.h"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>

int inputRecieved(InputHandler *self, int arg) {
	
	Pulse *pulse = self->currentPulse;
	int i = 0;
	
	LCDDR3 |= 0x00;
	
	
	if (!((PINB >> PINB4) & 1U)) {//enter
		LCDDR3 |= 0xff;
		ASYNC(pulse, switchValue, 0);
	}
	
	if (!((PINB >> PINB6) & 1U)) {//up
		i = 2;
		LCDDR3 |= 0xff;
		ASYNC(pulse, increseValue, 0);
	}
	
	if (!((PINB >> PINB7) & 1U)) {//down
		i = 3;
		LCDDR3 |= 0xff;
		ASYNC(pulse, lowerValue, 0);
	}
	
	if (!((PINE >> PCINT2) & 1U)) {//left
		LCDDR3 |= 0xff;
		self->currentPulse = self->nextPulse;
		self->nextPulse = pulse;
		pulse = self->currentPulse;
		ASYNC(self->currentPulse, togglePulse, 0);
	}
	
	if (!((PINE >> PCINT3) & 1U)) {//right
		LCDDR3 |= 0xff;
		self->currentPulse = self->nextPulse;
		self->nextPulse = pulse;
		pulse = self->currentPulse;
		ASYNC(self->currentPulse, togglePulse, 0);
	}
 	
	if (i == 2 || i == 3){
		/*AFTER(*self,1);*/
	}
	return 0;
}

int buttonStillPressed(InputHandler *self, int arg){
	//Do something
	return 0;
}