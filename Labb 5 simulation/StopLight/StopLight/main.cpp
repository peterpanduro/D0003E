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
#include "Communication.h"

#define NUM_THREADS 2

using namespace std;

StopLight light;

void *run(void *threadid) {
	light.runStopLight();
}

int main() {
	
	Communication communication = Communication();
	light.communication = communication;
	
	pthread_t thread_1;
	int i1 = pthread_create(&thread_1, NULL, run, (void*) NULL);
	pthread_join(thread_1, NULL);
	
	//thread run(run());
	//pthread_t threads[NUM_THREADS];
	//int16_t rc0 = pthread_create(thread, NULL, run, (void *)0);
	
	while(1){
		int recieved = communication.recieve();
		if (recieved >= 0) {
			cout << "Read " << recieved << "\n";
		}		
		
		if (GetAsyncKeyState('S') & 0x8000) {
			communication.transmit(1);
//			light.addToQ(2);
			while (GetAsyncKeyState('S') & 0x8000);
		}
		if (GetAsyncKeyState('N') & 0x8000) {
			communication.transmit(2);
//			light.addToQ(1);
			while (GetAsyncKeyState('N') & 0x8000);
		}
		if (GetAsyncKeyState('T') & 0x8000) {
			communication.transmit(3);
//			light.toggleLight(1);
			while (GetAsyncKeyState('T') & 0x8000);
		}
		if (GetAsyncKeyState('Y') & 0x8000) {
			communication.transmit(4);
//			light.toggleLight(2);
			while (GetAsyncKeyState('Y') & 0x8000);
		}
	}
}

