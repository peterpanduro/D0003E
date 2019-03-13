

#ifndef _DISPLAY_
#define _DISPLAY_

#include "TinyTimber.h"

typedef struct {
	Object super;
} Display;

#define initDisplay() {initObject()}

int toggle(Display *self, int arg);	//change and shows witch pulse is active
int printNumber(Display *self, int arg);	//Prints wanted number according to Id.

#endif