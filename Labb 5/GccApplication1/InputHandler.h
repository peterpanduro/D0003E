
#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include "TinyTimber.h"
#include "Display.h"
#include "Bridge.h"
#include "Run.h"

typedef struct {
	Object super;
	Run	*run;
 	Display *display;
// 	Time *timer;
// 	Bridge *bridge;
} InputHandler;

#define  initInputHandler(run, display/*, timer, bridge*/) {initObject(), run, display/*, timer, bridge*/}

int inputRecieved(InputHandler *self, int arg);
int signalRecieved(InputHandler *self, int arg);

#endif