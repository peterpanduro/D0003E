/*
 * GccApplication1.c
 *
 * Created: 2019-01-30 08:43:26
 * Author : larpet-5
 */ 

#include "InputHandler.h"
#include "Display.h"
#include "TinyTimber.h"
#include "Run.h"

#include <avr/io.h>
#include <math.h>
#include <stdint.h>

void setupSettings(void) {
	
	// Enable. Low power wave form.
	//LCDCRA = (1<<LCDEN) | (1<<LCDAB);
	LCDCRA = 0xc0;
	// External clock. 1/4 Duty. 25 segments port mask
	//LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
	LCDCRB = 0xb7;
	// Frame rate
	//LCDFRR = (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
	LCDFRR = 0x06;
	// Drive time 300?s. Contrast 3,35V
	//LCDCCR = (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);
	LCDCCR = 0x0f;
	
	// Enable logical interrupt for joystick. 
	PORTB = 0xff | PORTB;
	PORTE |=  (1<<PCINT2) | (1<<PCINT3);
	PCMSK1 = 0xff | PCMSK1;
	PCMSK0 |= (1<<PCINT2) | (1<<PCINT3);
	EIMSK |= (1<<PCIE1) | (1<<PCIE0);
	
	// Enable timer interrupt at 50 ms interval
	TCCR1A |= (1<<COM1A0); // OC1A Compare Match
	TCCR1B |= (1<<WGM12); // CTC
	TCCR1B |= (1<<CS12) | (1<<CS10); // 1024 prescaling
	// OCRnA = (fclk_io / 2*N*fOCnA) - 1 = 8*10^6/(2*1024*200) = 194,3125 ~ 0xc2
	OCR1AH = 0x0f; //OCR1A[15:8]
	OCR1AL = 0x2e; //OCR1A[7:0]
	//OCR1A=0x07a0;
	TIMSK1 |= (1<<OCIE1A); //Output Compare A Match Interrupt Enable
	//Reset CLK
// 	CLKPR = 0x80;
// 	CLKPR = 0x00;
}

void setupCLK(void) {
	CLKPR = 0x80;
	CLKPR = 0x00;
	TCCR1B |= (1<<CS12);
}


int main(void)
{
	setupSettings();
	
// 	PORTE |= (1<<PCINT6);
// 	PORTE |= (1<<PCINT4);
	
	Display display = initDisplay(0);
	Display display2 = initDisplay(3);
	InputHandler input = initInputHandler(&display,&display2);
	/*Run run = initRun();*/
	
	
	
	INSTALL(&input,inputRecieved,IRQ_PCINT1);
	INSTALL(&input,inputRecieved,IRQ_PCINT0);
	return TINYTIMBER(NULL, NULL, NULL);
}

