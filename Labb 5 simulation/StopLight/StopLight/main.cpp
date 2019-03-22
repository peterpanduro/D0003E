// StopLight.cpp : This file contains the 'main' function. Program execution begins and ends there.
// to run code in Cygwin
/*
 cd Documents/realtid/d0003e/Labb\ 5\ simulation/StopLight/StopLight/
 g++ main.cpp StopLight.cpp Communication.cpp -o run
 ./run
*/
#include "pch.h"
#include <iostream>
#include "StopLight.h"
#include <windows.h>
#include <pthread.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "Communication.h"

using namespace std;

StopLight light;
void *runStopLight(void *args) {
	light.runStopLight();
}

void *ioStopLight(void *args) {
	light.io();
}

int main() {
	pthread_t threadRun, threadIO;
	int16_t rc0 = pthread_create(&threadRun, NULL, runStopLight, (void *)NULL);
	int16_t rc1 = pthread_create(&threadIO, NULL, ioStopLight, (void *)NULL);
	pthread_exit(NULL);
}

