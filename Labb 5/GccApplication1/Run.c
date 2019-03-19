/*
 * Run.c
 *
 * Created: 2019-03-12 18:05:21
 *  Author: jonjac-6
 */ 
#include <avr/io.h>
#include "Run.h"

#define FOSC 8000000 // Clock speed
#define BAUD 9600
#define UBER FOSC/16/BAUD-1
int unsigned uber = UBER;
int startUp = 1;


int startupSequence(Run *self, int arg){
	
	
	
	if (startUp){
		UCSR0B |= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0);
		UCSR0C = (3 << UCSZ00) & ~(1 << USBS0);
	
		UBRR0H = (unsigned char)(uber >> 8);
		UBRR0L = (unsigned char)(uber);
		startUp = 0;
	}
	
	UDR0 |= /*0b1111*/0x0;
	
	
	AFTER(MSEC(1000), self, startupSequence, 0);

	
/*	ASYNC(self->stopLight, runStopLight, 0);*/
	
	
	return 0;
}