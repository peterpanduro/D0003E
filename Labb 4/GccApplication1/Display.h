

#ifndef _DISPLAY_
#define _DISPLAY_

#include "TinyTimber.h"

typedef struct {
	Object super;
	int displayPos1;
	int displayPos2;
} Display;

#define initDisplay(displayPos1, displayPos2) {initObject(),displayPos1, displayPos2}

int toggle(Display *self, int arg);	//change and shows witch pulse is active
int printNumber(Display *self, int arg);	//Prints wanted number according to Id.

#endif