// StopLight.cpp : This file contains the 'main' function. Program execution begins and ends there.
// to run code in Cygwin
/*
 cd Documents/realtid/d0003e/Labb\ 5\ simulation/StopLight/StopLight/
 g++ main.cpp StopLight.cpp -o run
 ./run
*/
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




#include <string.h> // needed for memset

void transmit(int serial_port, int i) {
	unsigned char message[] = {(unsigned char)i}; // Second byte terminate the message
	int n = write(serial_port, &message, 1);
	cout << "Written " << n << " bytes with content " << (int)message[0] << "\n";
}

int recieve(int serial_port) {
	unsigned char c = 'a';
	int n = read(serial_port,&c,1);
	cout << "Read " << n << " bytes with content " << c << "\n";
	if (n > 0){
		write(STDOUT_FILENO,&c,1);
	}
	//if new data is available on the console, send it to the serial port
	int m = read(STDIN_FILENO,&c,1);
	cout << "Read2 " << m << " bytes with content " << c << "\n";
	if (m > 0) {
		write(serial_port,&c,1);
	}
}

int main()
{	
	// Open serial port
	int serial_port = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
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
	
	int i = 0;
	while(1){
		i++;
		if (i > 99) {
			i = 0;
		}
		//transmit(serial_port, i);
		recieve(serial_port);
		sleep(1);
	}
	
/*
	unsigned char c='D';

	struct termios tio;
    struct termios stdio;
	int tty_fd;
	
	memset(&stdio,0,sizeof(stdio));
	stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=0;
    stdio.c_cc[VTIME]=0;
    tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL);  // make the reads non-blocking
	
	
	memset(&tio,0,sizeof(tio));
	tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=0;
    tio.c_cc[VTIME]=0;
	
	// Set in/out baud rate to be 9600
//	cfsetispeed(&tty, B9600);
//	cfsetospeed(&tty, B9600);
	// Save tty settings, also checking for error

	tty_fd=open("/dev/ttyS0", O_RDWR );        // O_NONBLOCK might override 
	cfsetospeed(&tio,B9600);            // 115200 baud
    cfsetispeed(&tio,B9600);            // 115200 baud
    tcsetattr(tty_fd,TCSANOW,&tio);
*/

	

    close(serial_port);
}
	
//	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
//		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
//	}
	
	
	
	
/*	
	while (true) {
		char buf[256];
		memset(&buf, '\0', sizeof buf);
		int n = read(serial_port, &buf, 1);//sizeof buf
		if (n < 0) {
			printf("Error reading: %s\n", strerror(errno));
			n=0;
		}
		printf("Read %i bytes. Received message: %c\n", n, buf);
		sleep(1);
	}
*/
/*
	thread run(run());
	thread run2(run2());
	pthread_t threads[NUM_THREADS];
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
	}
}
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


