#include "tinythreads.h"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>

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

int is_prime(long number){
	for (int i = 2; i<number; i+=1){
		if (number%i == 0){
			return 0;
		}
	}
	return 1;
}

void printAt(long num, int pos) {
    int pp = pos;
    writeChar( (num % 100) / 10 + '0', pp);
    pp++;
    writeChar( num % 10 + '0', pp);
}

void computePrimes(int pos) {
    long n;

    for(n = 1; ; n++) {
        if (is_prime(n)) {
            printAt(n, pos);
        }
    }
}

int main() {
    spawn(computePrimes, 0);
    computePrimes(3);
}
