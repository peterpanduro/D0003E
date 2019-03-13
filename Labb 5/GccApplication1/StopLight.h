/*
 * StopLighit.h
 *
 * Created: 2019-03-13 20:38:23
 *  Author: jonjac-6
 */ 

#ifndef _STOPLIGHT_
#define _STOPLIGHT_

#include "TinyTimber.h"
#include "Bridge.h"

typedef struct {
	Object super;
	Bridge *bridge;
	int counter;
	int timeUntillCarHasPassed; //Has to be zero for a switch in light can occur.
} StopLight;

#define  initStopLight(bridge) {initObject(), bridge, 0 ,0}
	
int runStopLight(StopLight *self, int arg);

#endif