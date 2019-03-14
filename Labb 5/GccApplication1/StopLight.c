/*
 * StopLight.c
 *
 * Created: 2019-03-13 20:38:02
 *  Author: jonjac-6
 */ 

#include "StopLight.h"

int runStopLight(StopLight *self, int arg){
	
	int carInNorthQ = SYNC(self->bridge, carInQ, 1);
	int carInSouthQ = SYNC(self->bridge, carInQ, 2);
	int northenRedLight = SYNC(self->bridge, checkRedLight, 1);
	int southernRedLight = SYNC(self->bridge, checkRedLight, 2);
	SYNC(self->bridge, manageCarsOnBridge, 0);
	
	if (self->counter == 295 || self->counter == 594){
		SYNC(self->bridge, changeTrafficLight, 3); //Closes both lanes so that the other opens after 5 min of quing
	}
	
	if (self->timeUntillCarHasPassed <= 0){
		if (carInNorthQ == 0 && carInSouthQ == 0){
			SYNC(self->bridge, changeTrafficLight, 4); //Opens both lanes when all cars has passed
			self->counter = 0;
		} else if (carInNorthQ > 0  && (self->counter < 300 || self->counter > 599)){
			SYNC(self->bridge, changeTrafficLight, 1); //Prioritize the northern lane but if five minutes passes it changes to the southern 
			self->counter = 0;
			self->timeUntillCarHasPassed = 4;
		} else{
			SYNC(self->bridge, changeTrafficLight, 2);
			self->counter = 300;
			self->timeUntillCarHasPassed = 4;
		}
	}else{
		if (southernRedLight == 0 && carInSouthQ == 0){
			self->timeUntillCarHasPassed--;
		}else if (northenRedLight == 0 && carInNorthQ == 0){
			self->timeUntillCarHasPassed--;
		}else{
			self->timeUntillCarHasPassed = 4;
		}
	}
	
	
	
	if (carInNorthQ == 0 && carInSouthQ == 0 && self->timeUntillCarHasPassed <= 0){
		AFTER(MSEC(50), self, runStopLight, 0);
	} else{
		AFTER(SEC(1), self, runStopLight, 0);
	}
	return 0;
}
