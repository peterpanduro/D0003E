/*
 * bridge.c
 *
 * Created: 2019-03-13 20:59:11
 *  Author: jonjac-6
 */ 

#include "Bridge.h"

int addCarToQ(Bridge *self, int arg){			// 1 == north, 2 == south
	if (arg == 1){
		self->carInQNorth++;
		ASYNC(self->display, printNumber, 300 + self->carInQNorth);
	} else if (arg == 2){
		self->carInQSouth++;
		ASYNC(self->display, printNumber, 100 + self->carInQSouth);
	}
	return 0;
}
	
int changeTrafficLight(Bridge *self, int arg){  // 1 == green north, 2 == green south, 3 == red both, 4 == green both.
	if (arg == 1){
		self->redLigthNorth = 0;
		self->redLigthSouth = 1;
		SYNC(self->display, toggle1, self->redLigthSouth);
		SYNC(self->display, toggle2, self->redLigthNorth);
	} else if (arg == 2){
		self->redLigthNorth = 1;
		self->redLigthSouth = 0;
		SYNC(self->display, toggle1, self->redLigthSouth);
		SYNC(self->display, toggle2, self->redLigthNorth);
	}else if (arg == 3){
		self->redLigthNorth = 1;
		self->redLigthSouth = 1;
		SYNC(self->display, toggle1, self->redLigthSouth);
		SYNC(self->display, toggle2, self->redLigthNorth);
	}else if (arg == 4){
		self->redLigthNorth = 0;
		self->redLigthSouth = 0;
		SYNC(self->display, toggle1, self->redLigthSouth);
		SYNC(self->display, toggle2, self->redLigthNorth);
	}
	return 0;
}


int manageCarsOnBridge(Bridge *self, int arg){	// Take care of the cars on the bridge.
	
	if (self->carOnNorthBridge > 0 && self->secondsOnBridgeNorth >= 5){
		self->carOnNorthBridge--;
	} else if (self->secondsOnBridgeNorth >= 5){
		self->secondsOnBridgeNorth = 0;
	}
	
	if (self->carOnSouthBridge > 0 && self->secondsOnBridgeSouth >= 5){
		self->carOnSouthBridge--;
		} else if (self->secondsOnBridgeSouth >= 5){
		self->secondsOnBridgeSouth = 0;
	}
	
	if (self->carInQNorth > 0  && self->redLigthNorth == 0){
		self->carInQNorth--;
		self->carOnNorthBridge++;
	}
	
	if (self->carInQSouth > 0  && self->redLigthSouth == 0){
		self->carInQSouth--;
		self->carOnSouthBridge++;
	}
	
	if (self->carOnNorthBridge > 0){
		self->secondsOnBridgeNorth++;
	}
	
	if (self->carOnSouthBridge > 0){
		self->secondsOnBridgeSouth++;
	}
	
	if(self->carOnNorthBridge > 0){
		SYNC(self->display, updateCarOnNorthBridge, 1);
	}else{
		SYNC(self->display, updateCarOnNorthBridge, 0);
	}
	
	if(self->carOnSouthBridge > 0){
		SYNC(self->display, updateCarOnSouthBridge, 1);
	}else{
		SYNC(self->display, updateCarOnSouthBridge, 0);
	}
	
	SYNC(self->display, printNumber, 300 + self->carInQNorth);
	SYNC(self->display, printNumber, 100 + self->carInQSouth);
	
	return 0;
}


int checkRedLight(Bridge *self, int arg){// 1 == north, 2 == south. 1 if on, 0 if off.
	if (arg == 1){
		return self->redLigthNorth;
	}else if (arg == 2){
		return self->redLigthSouth;
	}
	return 9;
}

int carInQ(Bridge *self, int arg){		// 1 == north, 2 == south. 1 if true, 0 false.
	if (arg == 1 && self->carInQNorth > 0){
		return 1;
	}else if (arg == 2 && self->carInQSouth > 0){
		return 1;
	}
	return 0;
}