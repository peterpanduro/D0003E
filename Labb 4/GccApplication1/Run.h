/*
 * Run.h
 *
 * Created: 2019-03-11 16:55:06
 *  Author: jonjac-6
 */ 


#ifndef _RUN_
#define _RUN_

#include "Pulse.h"
#include "TinyTimber.h"

typedef struct {
	Object super;
} Run;

#define initRun() {initObject()}

void coolFunction(Run *self, int arg);

#endif
