
#include "InputHandler.h"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>

int inputRecieved(InputHandler *self, int arg) {
	
	Display *display = self->currentDisplay;
	int i = 5;
// 	LCDDR0 &= 0x00;
// 	LCDDR1 &= 0x00;
// 	LCDDR2 &= 0x00;
// 	LCDDR3 &= 0x00;
// 	LCDDR5 &= 0x00;
// 	LCDDR6 &= 0x00;
	
	
	if (!((PINB >> PINB4) & 1U)) {//enter
		/*i = 0;*/
		LCDDR3 |= 0xff;
	}
	
	if (!((PINB >> PINB6) & 1U)) {//up
		/*i = 1;*/
		LCDDR3 |= 0xff;
		/*LCDDR2 |= 0xff;*/
	}
	
	if (!((PINB >> PINB7) & 1U)) {//down
		/*i = 2;*/
		LCDDR3 |= 0xff;
		/*LCDDR1 |= 0xff;*/
	}
	
	if (!((PINE >> PCINT2) & 1U)) {//left
		/*i = 3;*/
		LCDDR3 |= 0xff;
// 		self->currentDisplay = self->nextDisplay;
// 		self->nextDisplay = display;
// 		display = self->currentDisplay;
	}
	
	if (!((PINE >> PCINT3) & 1U)) {//right
		/*i = 4;*/
		LCDDR3 |= 0xff;
// 		self->currentDisplay = self->nextDisplay;
// 		self->nextDisplay = display;
// 		display = self->currentDisplay;
	}
 	
 	ASYNC(display, writeChar, i + '0');
	return 0;
	
}