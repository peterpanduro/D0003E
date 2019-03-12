
#include "Pulse.h"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>

int	switchValue(Pulse *self, int arg){  //Changes the value to the stored value
										//Need to test the pointers before I know that everything works.
	
 	int temp = self->storedValue;
 	self->storedValue = self->value;
 	self->value = temp;
	
	SYNC(self->display, printNumber, self->id+self->value);
	
	return 0;
}


int increseValue(Pulse *self, int arg){ //Increases value by one
	
	if (self->value < 99){
		self->value++;		//Need to test the pointers before I know that everything works.
	}
	
	SYNC(self->display, printNumber, self->id + self->value);
	
	return 0;
}


int lowerValue(Pulse *self, int arg){   //Lowers value by one
	
	if (self->value > 0){
 		self->value--;   //Need to test the pointers before I know that everything works.
	}
	
	SYNC(self->display, printNumber, self->id + self->value);
	
	return 0;
}

int togglePulse(Pulse *self, int arg){
	
	SYNC(self->display, toggle, self->id);
	
	return 0;
}

int runPulse(Pulse *self, int arg){		//Changes the current from low to high and queue it self.
	if (self->id == 100){
		if ((PORTE >> PE6) & 1U){
			PORTE &= (1 << PE6);
		}else{
			PORTE |= (1 << PE6);
		}		//Can be wrong<------------------------------------------------------------------------------------------------------------------------
	}else if (self->id == 200){
		if ((PORTE >> PE4) & 1U){
			PORTE &= (1 << PE4);
			}else{
			PORTE |= (1 << PE4);
		}		//Can be wrong<------------------------------------------------------------------------------------------------------------------------
	}
	
	Display *dis = self->display;
	
	SYNC(dis, printNumber, self->id + self->value);
	
	AFTER(MSEC(self->value), self, runPulse, arg);
	return 0;
}