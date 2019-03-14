/*
 * Run.h
 *
 * Created: 2019-03-12 18:05:52
 *  Author: jonjac-6
 */ 


#ifndef _RUN_
#define _RUN_

#include "TinyTimber.h"
#include "Pulse.h"

typedef struct{
	Object super;
	Pulse *pulse1;
	Pulse *pulse2;
} Run;

#define initRun( pulse1, pulse2) {initObject(), pulse1, pulse2}

int startupSequence(Run *self, int arg);


#endif