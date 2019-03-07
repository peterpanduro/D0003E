
#ifndef _PULSE_
#define _PULSE_

typedef struct {
	int id;
	int value;
	int storedValue;
} Pulse;

#define initPulse(id) {id, 0, 0}

void switchState();
void setValue(int value);

#endif