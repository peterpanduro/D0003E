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

/************************************************************************/
/*                     Standalone methods                               */
/************************************************************************/

void writeChar(char ch, uint16_t position) {
	if (position > 5) {
		return;
	}
	int shift = position%2 ? 4 : 0; //If position is an even number its the UPPER nibbles that changes AKA shift left 4
									//and use OR in the new bits
	
	int shift2 = position%2 ? 0 : 4;//If position is an even number the LOWER nibbles are kept. So the same thing happens
									// but reversed.

	uint8_t *d1 = &LCDDR0;			//Makes pointers to the different initial segments of the LCD-display
	uint8_t *d2 = &LCDDR5;
	uint8_t *d3 = &LCDDR10;
	uint8_t *d4 = &LCDDR15;
	d1 += position/2;				//Moves the pointer so that it points to the corresponding segment that displays the number.
	d2 += position/2;
	d3 += position/2;
	d4 += position/2;
	
	//Blank position of the new number. This depends on the nibbles and position. 
	if (shift == 4) {
		LCDDR0 = 0x6f & LCDDR0; //LCDDR0 also corresponds to bits used by Blink() and button()
	} else {
		LCDDR0 = 0xf6 & LCDDR0;
	}
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

void writeLong(long i){
	int index = 5;  //Index of where the number should be printed
	int printNumber;
	do {
		printNumber = i%10;
		i = i/10;
		writeChar(printNumber+'0', index); //0 == 48 in ASCII
		index = index - 1;
	} while (i > 0 && index > -1);
}

void printPrim(void){
	long number = 3;
	while (1){
		if (isPrime(number) == 1){
			writeLong(number);
		}
		number +=1;
	}
}

int isPrime(long number){
	for (int i = 2; i<number; i+=1){
		if (number%i == 0){
			return 0;
		}
	}
	return 1;
}

void blink(void){
	while(1){
		if (TCNT1 > 0xFFFF/2) {
			LCDDR0 = 0x22;
			LCDDR1 = 0x44;
			LCDDR3 = 0x66;
		} else {
			LCDDR0 = 0x0;
			LCDDR1 = 0x0;
			LCDDR3 = 0x0;
		}
	}
}

void button(void) {
	LCDDR0 = 0x04;
	while (1) {
		while (((PINB >> 7) & 1U) == 1) {}		// busy-wait for push down on joystick
		while (((PINB >> 7) & 1U) == 0) {}		// busy-wait for release of joystick
		LCDDR0 = LCDDR0 == 0x40 ? 0x04 : 0x40;	// swap the display number 1 and 2
	}
}

/************************************************************************/
/* Concurrent methods                                                   */
/************************************************************************/

static int buttonPressed = 0;

int isPrime_2(long number){
	for (int i = 2; i<number; i+=1){
		if (number%i == 0){
			return 0;
		}
	}
	return 1;
}


void blink_2(void){
	if (TCNT1 > 0xFFFF/2) {
		LCDDR0 = 0x22 | LCDDR0;
		LCDDR1 = 0x44 | LCDDR1;
		LCDDR3 = 0x66 | LCDDR3;
	} else {
		LCDDR0 = 0xdd & LCDDR0;
		LCDDR1 = 0xbb & LCDDR1;
		LCDDR3 = 0x99 & LCDDR3;
	}
}

void button_2(void) {
	if ((((PINB >> 7) & 1U) == 0) && !buttonPressed) {
		// Button down first time
		buttonPressed = 1;
	} else if ((((PINB >> 7) & 1U) == 1) && buttonPressed) {
		// Button is just released
		buttonPressed = 0;
		if ((LCDDR0 >> 2) & 1U) {
			LCDDR0 = LCDDR0 & 0xbb;
			LCDDR0 = LCDDR0 | 0x40;
		} else  {
			LCDDR0 = LCDDR0 & 0xbb;
			LCDDR0 = LCDDR0 | 0x4;
		}
	}
}

void concurrent(void) {
	// Light number 1 on LCD
	LCDDR0 = 0x04;
	int number = 25000;
	while (1) {
		if (isPrime(number) == 1){
			writeLong(number);
		}
		number += 1;
		button_2();
		blink_2();
	}
}

int main(void)
{
	PORTB = 0x80 | PORTB;
    setupLCD();
	setupCLK();
	
	
	//Del 1
	//printPrim();
	
	
	//Del 2
	//blink();
	
	
	//Del 3
	//button();
	
	
	//Del 4
	concurrent();
}

