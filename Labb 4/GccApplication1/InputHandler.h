
#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include "TinyTimber.h"
#include "Display.h"

typedef struct {
	Object super;
	Display *currentDisplay;
	Display *nextDisplay;
} InputHandler;

#define  initInputHandler(currentDisplay,nextDisplay) {initObject(),currentDisplay,nextDisplay}

int inputRecieved(InputHandler *self, int arg);

#endif