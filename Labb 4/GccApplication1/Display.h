

#ifndef _DISPLAY_
#define _DISPLAY_

#include "Pulse.h"
#include "TinyTimber.h"

typedef struct {
	Object super;
	int displayPos;
} Display;

#define initDisplay(displayPos) {initObject(),displayPos}

int setDisplayPos(Display *self, int arg);
int printNumber(Display *self, int arg);
int writeChar(Display *self, char ch);

#endif