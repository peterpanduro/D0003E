#include "tinythreads.h"
#include "mytest.h"
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>

mutex *mutexButton;
mutex *mutexBlink;

int timesPressedDown = 0;

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
	*d1 &= (0xf<<shift2) | (0x6<<shift);
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

int is_prime(long number) {
	for (int i = 2; i<number; i+=1) {
		if (number%i == 0) {
			return 0;
		}
	}
	return 1;
}

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
	
	// Enable logical interrupt for joystick down. Source PCINT15 (7th bit on PORTB)
	PORTB = 0x80 | PORTB;
	PCMSK1 = 0x80 | PCMSK1;
	EIMSK |= (1<<PCIE1);
	
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
	CLKPR = 0x80;
	CLKPR = 0x00;
}

//mutex *m;
void printAt(long num, int pos) {
    writeChar( (num % 100) / 10 + '0', pos);
    pos++;
    writeChar( num % 10 + '0', pos);
}

void computePrimes(int pos) {
    long n;

    for(n = 1; ; n++) {
        if (is_prime(n)) {
            printAt(n, pos);
        }
    }
}


//Make the lines switch on the display.
void blink(int i){
	
	mutexBlink->locked = 1;
	mutexBlink->waitQ = 0;
	
	while(1){
		lock(&mutexBlink);
		if ((LCDDR0 >> 1) & 1U) {
			LCDDR0 &= 0xdd;
			LCDDR1 &= 0xbb;
		} else {
			LCDDR0 |= 0x22;
			LCDDR1 |= 0x44;
		}
	}
}


void button(int pos){
	
	mutexButton->locked = 1;
	mutexButton->waitQ = 0;
	printAt(timesPressedDown,pos);
	LCDDR0 &= 0xbb;
	LCDDR0 |= 0x40;
	while (1) {		
		lock(&mutexButton);
		printAt(timesPressedDown,pos);
		if ((LCDDR0 >> 6) & 1U) {
			LCDDR0 &= 0xbb;
			LCDDR0 |= 0x04;
		} else  {
			LCDDR0 &= 0xbb;
			LCDDR0 |= 0x40;
		}
	}
}


ISR(PCINT1_vect) {
	if (!((PINB >> PINB7) & 1U)) {
		timesPressedDown++;
		unlock(&mutexButton);
	}
}




ISR(TIMER1_COMPA_vect) {
	unlock(&mutexBlink);
}

int main() {
	setupSettings();
	
	spawn(blink, 0);
	yield();
 	spawn(button, 4);
 	yield();
	
	computePrimes(0);
}
