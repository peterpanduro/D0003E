// StopLight.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "StopLight.h"
#include <windows.h>
#include <thread>
using namespace std;

StopLight light;

void run() {
	light.runStopLight();
}

void run2() {
	light.updateStopLight();
}


int main()
{
	
	thread run(run);

	thread run2(run2);


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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
