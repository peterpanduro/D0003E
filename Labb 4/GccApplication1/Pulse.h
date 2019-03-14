
#ifndef _PULSE_
#define _PULSE_

#include "TinyTimber.h"
#include "Display.h"

typedef struct {
	Object super;
	Display *display;
	int id; // Id 1 == 100, Id 2 == 200.
	int value;
	int storedValue;
} Pulse;

#define initPulse(display, id) {initObject(), display, id*100, 0, 0}
	
int	switchValue(Pulse *self, int arg);  //Changes the value to the stored value
int increseValue(Pulse *self, int arg); //Increases value by one
int lowerValue(Pulse *self, int arg);   //Lowers value by one
int togglePulse(Pulse *self, int arg); //Toggles between 1 and 2 on the display.
int runPulse(Pulse *self, int arg);		//Changes the current from low to high and queue it self.

#endif