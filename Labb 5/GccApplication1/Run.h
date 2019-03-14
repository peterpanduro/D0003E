/*
 * Run.h
 *
 * Created: 2019-03-12 18:05:52
 *  Author: jonjac-6
 */ 


#ifndef _RUN_
#define _RUN_

#include "TinyTimber.h"
#include "Bridge.h"
#include "Display.h"
#include "StopLight.h"

typedef struct{
	Object super;
	Bridge *bridge;
	Display *display;
	StopLight *stopLight;
} Run;

#define initRun(bridge, display, stopLight) {initObject(), bridge, display, stopLight}

int startupSequence(Run *self, int arg);


#endif