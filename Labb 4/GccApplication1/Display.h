#include "Pulse.h"

#ifndef _DISPLAY_
#define _DISPLAY_

typedef struct {
} Display;

#define initDisplay();

void setActiveCounterId(int counterId);
void setDisplay(Pulse *pulse, int counterId);
void printAt(long num, int pos);

#endif