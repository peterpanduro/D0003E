

#ifndef _DISPLAY_
#define _DISPLAY_

#include "TinyTimber.h"

typedef struct {
	Object super;
} Display;

#define initDisplay() {initObject()}

int toggle1(Display *self, int arg);		//Turn 1 on/off
int toggle2(Display *self, int arg);		//Turn 2 on/off (on is equal to red light)
int updateCarOnNorthBridge(Display *self, int arg);	//1 for true, 0 for false
int updateCarOnSouthBridge(Display *self, int arg);	//1 for true, 0 for false

int printNumber(Display *self, int arg);	//Prints wanted number according to Id.

#endif