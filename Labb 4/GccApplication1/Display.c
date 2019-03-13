
#include "Display.h"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>

int writeChar(char ch, int position) {
	if (position > 5) {
		return 0;
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
	return 0;
}


//argument should have 3 digits between 100-299. The first digit decides if it is displayPos1 of displayPos2.
int printNumber(Display *self, int arg){ 
	int num = arg;
	int pos;
	
	if (num/100 == 1){
		pos = 0;
	}else if (num/100 == 2){
		pos = 3;
	}else{
		LCDDR0 |= 0xff;//If this happens something wrong happened in pulse with the Id.
		pos = 2;
	}
	
	writeChar( (num % 100) / 10 + '0', pos);
	pos++;
	writeChar( num % 10 + '0', pos);
	return 0;
}

int toggle(Display *self, int arg) {
	
	if (arg == 100){
		LCDDR0 &= 0xbb;
		LCDDR0 |= 0x04;
	}else{
		LCDDR0 &= 0xbb;
		LCDDR0 |= 0x40;
	}
	
	return 0;
}
