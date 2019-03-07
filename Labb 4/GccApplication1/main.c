/*
 * GccApplication1.c
 *
 * Created: 2019-01-30 08:43:26
 * Author : larpet-5
 */ 

#include <avr/io.h>
#include <math.h>
#include <stdint.h>

void setupLCD(void) {
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
}

void setupCLK(void) {
	CLKPR = 0x80;
	CLKPR = 0x00;
	TCCR1B |= (1<<CS12);
}


int main(void)
{
	PORTB = 0x80 | PORTB;
    setupLCD();
	setupCLK();
	
	while(1){
	
	}
}

