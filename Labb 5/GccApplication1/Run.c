/*
 * Run.c
 *
 * Created: 2019-03-12 18:05:21
 *  Author: jonjac-6
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Run.h"



int startupSequence(Run *self, int arg){
		
	
	
//	else if (arg == 99){
// 		arg = 0;
// 	}else{
// 		arg++;
// 	}
	
// 	AFTER(MSEC(100), self, startupSequence, 0);
//	ASYNC(self->stopLight, runStopLight, 0);
//	AFTER(MSEC(100), self, startupSequence, arg);

	ASYNC(self->bridge, debugginLoop, 0);
	
//	ASYNC(self, USART_Transmit, 1);
	
	return 0;
}

int USART_Transmit(Run *self, int arg){
	//wait for empty transmit buffer
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = arg;
	ASYNC (self->display, printNumber,100 + arg);
	return 0;
}

int USART_Receive(Run *self, int arg){
	while ( !(UCSR0A & (1<<RXC0)));
	SYNC(self->display,printNumber, 300 );
	int t = UDR0;
	if (t > 0 && t < 99) { // Only shows 00 whit occasional flimmer when not using if-statement
		SYNC(self->display,printNumber, 300 + t );
	}
	return 0;
}
	