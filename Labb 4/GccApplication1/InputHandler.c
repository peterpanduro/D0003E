
#include "InputHandler.h"
#include "Display.h"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>

inputRecieved() {
	
	if (!((PINB >> PINB4) & 1U)) {//enter
		printAt(1, 1);
	}
	
	if (!((PINB >> PINB6) & 1U)) {//up
		printAt(2, 1);
	}
	
	if (!((PINB >> PINB7) & 1U)) {//down
		printAt(3, 1);
	}
	
	if (!((PINE >> PCINT2) & 1U)) {//left
		printAt(4, 1);
	}
	
	if (!((PINE >> PCINT3) & 1U)) {
		printAt(5, 1);
	}
}