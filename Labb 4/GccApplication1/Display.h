

#ifndef _DISPLAY_
#define _DISPLAY_

#include "TinyTimber.h"

typedef struct {
	Object super;
	int displayPos1;
	int displayPos2;
} Display;

#define initDisplay(displayPos1, displayPos2) {initObject(),displayPos1, displayPos2}

int changePulseSate(Display *self, int arg);
int printNumber(Display *self, int arg);

#endif