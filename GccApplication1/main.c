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
	//LCDCRA = (LCDEN<<1) | (LCDAB<<1);
	LCDCRA = 0xc0;
	// External clock. 1/4 Duty. 25 segments port mask
	//LCDCRB = (LCDCS<<1) | (LCDMUX1<<1) | (LCDMUX0<<1) | (LCDPM2<<1) | (LCDPM1<<1) | (LCDPM0<<1);
	LCDCRB = 0xb7;//= 0xa6;
	// Frame rate
	//LCDFRR = (LCDCD2<<1) | (LCDCD1<<1) | (LCDCD0<<1);
	LCDFRR = 0x06;
	// Drive time 300?s. Contrast 3,35V
	//LCDCCR = (LCDCC3<<1) | (LCDCC2<<1) | (LCDCC1<<1) | (LCDCC0<<1);
	LCDCCR = 0x0f;
}

void writeChar(char ch, uint16_t pos) {
	if (pos > 5) {
		return;
	}
	int shift = pos%2 ? 4 : 0;
	int shift2 = pos%2 ? 0 : 4;

	uint8_t *d1 = &LCDDR0;
	uint8_t *d2 = &LCDDR5;
	uint8_t *d3 = &LCDDR10;
	uint8_t *d4 = &LCDDR15;
	d1 += pos/2;
	d2 += pos/2;
	d3 += pos/2;
	d4 += pos/2;
	
	// Blank the new number
	*d1 &= (0xf<<shift2);
	*d2 &= (0xf<<shift2);
	*d3 &= (0xf<<shift2);
	*d4 &= (0xf<<shift2);

	switch (ch) {
		case '0':
			*d1 |= (0x1<<shift);
			*d2 |= (0x5<<shift);
			*d3 |= (0x5<<shift);
			*d4 |= (0x1<<shift);
			break;
		case '1':
			*d2 |= (0x1<<shift);
			*d3 |= (0x1<<shift);
			break;
		case '2':
			*d1 |= (0x1<<shift);
			*d2 |= (0x1<<shift);
			*d3 |= (0xe<<shift);
			*d4 |= (0x1<<shift);
			break;
		case '3':
			*d1 |= (0x1<<shift);
			*d2 |= (0x1<<shift);
			*d3 |= (0xb<<shift);
			*d4 |= (0x1<<shift);
			break;
		case '4':
			*d2 |= (0x5<<shift);
			*d3 |= (0xb<<shift);
			break;
		case '5':
			*d1 |= (0x1<<shift);
			*d2 |= (0x4<<shift);
			*d3 |= (0xb<<shift);
			*d4 |= (0x1<<shift);
			break;
		case '6':
			*d1 |= (0x1<<shift);
			*d2 |= (0x4<<shift);
			*d3 |= (0xf<<shift);
			*d4 |= (0x1<<shift);
			break;
		case '7':
			*d1 |= (0x1<<shift);
			*d2 |= (0x1<<shift);
			*d3 |= (0x1<<shift);
			break;
		case '8':
			*d1 |= (0x1<<shift);
			*d2 |= (0x5<<shift);
			*d3 |= (0xf<<shift);
			*d4 |= (0x1<<shift);
			break;
		case '9':
			*d1 |= (0x1<<shift);
			*d2 |= (0x5<<shift);
			*d3 |= (0xb<<shift);
			*d4 |= (0x1<<shift);
		default:
			break;
	}
}

int main(void)
{
	CLKPR = 0x80;
	CLKPR = 0x00;
    setupLCD();
	
	writeChar('0', 0);
	writeChar('1', 1);
	writeChar('2', 2);
	writeChar('3', 3);
	writeChar('4', 4);
	writeChar('5', 5);
	writeChar('6', 0);
	writeChar('7', 1);
	writeChar('8', 2);
	writeChar('9', 3);
	
    while (1) 
    {
    }
}

