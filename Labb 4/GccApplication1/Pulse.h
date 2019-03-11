
#ifndef _PULSE_
#define _PULSE_

#include "TinyTimber.h"

typedef struct {
	Object super;
	int id;
	int value;
	int storedValue;
} Pulse;

#define initPulse(id) {initObject(),id, 0, 0}

void switchState();
void setValue(int value);

#endif