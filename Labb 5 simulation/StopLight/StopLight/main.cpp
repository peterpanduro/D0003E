// StopLight.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "StopLight.h"
#include <windows.h>
#include <thread>
#include <pthread.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error number
#include <termios.h> // Contain POSIX terminal control definition
#include <unistd.h> // write() read() close()
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

StopLight light;


void *run(void *threadid) {
	light.runStopLight();
}

/*void *run2(void *threadid) {
	light.updateStopLight();
}*/



int main()
{
	// Open serial port
	int serial_port = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
	// Check error
	if (serial_port < 0) {
		printf("Error %i from open: %s\n", errno, strerror(errno));
	}
	// Create termios struct, named tty
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	// Read in existing settings and handle any error
	if (tcgetattr(serial_port, &tty) != 0) {
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
	// Set in/out baud rate to be 9600
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);
	// Save tty settings, also checking for error
	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
	}
	
	
	
	
	
	while (true) {
		int buf[8];
		memset(&buf, '\0', sizeof buf);
		int n = read(serial_port, &buf, sizeof buf);
		if (n < 0) {
			printf("Error reading: %s\n", strerror(errno));
			n=0;
		}
		printf("Read %i bytes. Received message: %s\n", n, buf);
		sleep(1);
	}
	
	/*
	int i = 0;
	int n = 0,
    spot = 0;
	char buf = '\0';
	//Whole response
	char response[1];
	memset(response, '\0', sizeof response);
	do {
		n = read(serial_port, &buf, 1 );
		sprintf( &response[spot], "%c", buf );
		spot += n;
		cout << n;
	} while( buf != '\r' && n > 0);
	if (n < 0) {
		std::cout << "Error reading: " << strerror(errno) << std::endl;
	} else if (n == 0) {
		std::cout << "Read nothing!" << std::endl;
	} else {
		std::cout << "Response: " << response << std::endl;
	}
	*/
	close(serial_port);
	
	
	
	
	
	/*thread run(run());
	thread run2(run2());*/
/*	pthread_t threads[NUM_THREADS];
	int16_t rc0 = pthread_create(&threads[0], NULL, run, (void *)0);
	//int16_t rc1 = pthread_create(&threads[1], NULL, run2, (void *)1);


	while (1) {
		while (1) {
			if (GetAsyncKeyState('S') & 0x8000) {
				light.addToQ(2);
				while (GetAsyncKeyState('S') & 0x8000);
			}
			if (GetAsyncKeyState('N') & 0x8000) {
				light.addToQ(1);
				while (GetAsyncKeyState('N') & 0x8000);
			}
			if (GetAsyncKeyState('T') & 0x8000) {
				light.toggleLight(1);
				while (GetAsyncKeyState('T') & 0x8000);
			}
			if (GetAsyncKeyState('Y') & 0x8000) {
				light.toggleLight(2);
				while (GetAsyncKeyState('Y') & 0x8000);
			}
		}
	}*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


