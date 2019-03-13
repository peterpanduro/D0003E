
#include "InputHandler.h"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>


int inputRecieved(InputHandler *self, int arg) {
	
	Time t = T_SAMPLE(self->timer);
	int timeSinsLastInterupt = MSEC_OF(t);
	
	if (timeSinsLastInterupt > 50){
		if (!((PINB >> PINB4) & 1U)) {//enter
// 			ASYNC(self->display, carOnNorthBrige, 0);
// 			ASYNC(self->display, carOnSouthBrige, 0);
/*			ASYNC(self->display, carOnSouthBrige, 0);*/
		}
	
		if (!((PINB >> PINB6) & 1U)) {//up
			/*ASYNC(self->display, carOnNorthBrige, 1);*/
			
			ASYNC(self->bridge, addCarToQ, 1);
		}
	
		if (!((PINB >> PINB7) & 1U)) {//down
			/*ASYNC(self->display, carOnSouthBrige, 1);*/
			
			ASYNC(self->bridge, addCarToQ, 2);
		}
	
		if (!((PINE >> PCINT2) & 1U)) {//left
			/*ASYNC(self->display, toggle1, 0);*/
			ASYNC(self->bridge, changeTrafficLight, 2);
		}
	
		if (!((PINE >> PCINT3) & 1U)) {//right
			/*ASYNC(self->display, toggle2, 0);*/
			ASYNC(self->bridge, changeTrafficLight, 1);
		}
	
		T_RESET(self->timer);
	}
	
	return 0;
}
