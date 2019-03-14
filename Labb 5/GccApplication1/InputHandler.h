
#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include "TinyTimber.h"
#include "Display.h"
#include "Bridge.h"

typedef struct {
	Object super;
	Display *display;
	Time *timer;
	Bridge *bridge;
} InputHandler;

#define  initInputHandler(display, timer, bridge) {initObject(), display, timer, bridge}

int inputRecieved(InputHandler *self, int arg);

#endif