/*
 * Run.c
 *
 * Created: 2019-03-12 18:05:21
 *  Author: jonjac-6
 */ 

#include "Run.h"

int startupSequence(Run *self, int arg){
	
	ASYNC(self->stopLight, runStopLight, 0);
	
	
	return 0;
}