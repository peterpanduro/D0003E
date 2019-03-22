#include "Communication.h"
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error number
#include <termios.h> // Contain POSIX terminal control definition
#include <unistd.h> // write() read() close()
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

Communication::Communication() {
	// Open serial port
	int tty_td = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	// Check error
	if (tty_td < 0) {
		printf("Error %i from open: %s\n", errno, strerror(errno));
	}
	
	// Create termios struct, named tty
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	// Read in existing settings and handle any error
	if (tcgetattr(tty_td, &tty) != 0) {
		printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
	}

	//Flags
	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	tty.c_cflag |= CS8; // CS(5-8) bits per byte (8 most common)
	tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	tty.c_lflag &= ~ICANON; // Disable canonical mode (processing of input when newline is detected)
	tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
	tty.c_cc[VMIN] = 0;
	tty.c_cc[VTIME] = 0;
	
	serial_port = tty_td;
}

void Communication::transmit(int i) {
	unsigned char message[] = {(unsigned char)i};
	int n = write(serial_port, &message, 1);
}

int Communication::recieve() {
	char c = -1;
	int n = read(serial_port,&c,1);
	return (int)c;
}