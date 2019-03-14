/*
 * bridge.h
 *
 * Created: 2019-03-13 20:59:19
 *  Author: jonjac-6
 */ 

#ifndef _BRIDGE_
#define _BRIDGE_

#include "TinyTimber.h"
#include "Display.h"

typedef struct {
	Object super;
	Display *display;
	int carInQNorth;
	int carInQSouth;
	int carOnNorthBridge;
	int carOnSouthBridge;
	int secondsOnBridgeNorth;
	int secondsOnBridgeSouth;
	int redLigthNorth; //1 == on, 0 == off
	int redLigthSouth; //1 == on, 0 == off
} Bridge;

#define  initBridge(display) {initObject(), display,0,0,0,0,0,0,1,1}
	
int addCarToQ(Bridge *self, int arg);			// 1 == north, 2 == south
int changeTrafficLight(Bridge *self, int arg);  // 1 == north, 2 == south
int manageCarsOnBridge(Bridge *self, int arg);	// Take care of the cars on the bridge.
int carInQ(Bridge *self, int arg);				// 1 == north, 2 == south. 1 if true, 0 false.
int checkRedLight(Bridge *self, int arg);		// 1 == north, 2 == south. 1 if true, 0 false.


#endif