
#include "pch.h"
#include "StopLight.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Communication.h"
#include <pthread.h>

using namespace std; // I startdet using this too late :(


/*StopLight() {
	redNorthenLight = true;
	redSouthernLight = true;
	carsInNorhtenQ = 0;
	carsInSouthernQ = 0;
	carsOnBridgeFromNorth = 0;
	carsOnBridgeFromSouth = 0;
	timeUntilEmptyNorh = 0;
	timeUntilEmptySouth = 0;
}*/

// 1 = darkblue
// 0 = black
// 3 = lightblue
// 4 = red
// 5 = pruple
// 6 = yellow/orange
// 15 = white
// 8 = gray
// 9 = blue

StopLight::StopLight() {}
Communication communication;
pthread_mutex_t transmiterMutex = communication.transmiterMutex;
pthread_mutex_t reciverMutex = communication.reciverMutex;


void StopLight::Color(int16_t color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Prints everything. DONT MESS WITH IT! YOU WILL BREAK IT! Ja, jag menar dig Jonas Jacobsson!
void StopLight::printStopLight() {
	
	int carsOnBridgeFromNorth = getCarsFromBridge(1);
	int carsOnBridgeFromSouth = getCarsFromBridge(2);
/*	cout << "-----------------------\n";
	cout << "[N]Queue: " << carsInNorhtenQ << "\n";
	cout << "[N]Redlight: " << redNorthenLightOn << "\n";
	cout << "[N]Cars on bridge: " << carsOnBridgeFromNorth << "\n";
	cout << "[S]Queue: " << carsInSouthernQ << "\n";
	cout << "[S]Redlight: " << redSouthernLightOn << "\n";
	cout << "[S]Cars on bridge: " << carsOnBridgeFromNorth << "\n";
	cout << "-----------------------\n";*/

	if (startUp) {
		startUp = false;
		for (int i = 0; i < 9000; i++) {
				std::cout << "\n";
			}
	}

	
	

	Color(8); std::cout << "\n                                             ________________________";
	Color(2); std::cout << "                                \\          /       \n";
	Color(15); std::cout << "             ^^                             ";
	Color(8); std::cout << "/                        \\        _";
	Color(6); std::cout << "                       \\  ____  /       \n";
	Color(15); std::cout << "           ^^  ^^";
	Color(8); std::cout << "                          /                          \\      |";

	
	std::cout << "0";

	Color(8); 

	

	std::cout << "|";
	Color(6); 
	if (StopLight::redNorthenLightOn) {
		Color(200);
	}
	else {
		Color(8);
	}
	std::cout << "                        /    \\         \n";
	Color(8); std::cout << "                                          / __________________________ \\     |";

	
	std::cout << "0";

	Color(8); std::cout << "|";
	Color(6); 
	
	if (redNorthenLightOn) {
		Color(8);
	}
	else {
		Color(160);
	}
	std::cout << "                 ----- /      \\ -----  \n";
	Color(3); std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	Color(8); std::cout << "/";
	Color(3); std::cout << "~";
	Color(8); std::cout << "/";
	Color(3); std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~";
	Color(8); std::cout << "\\";
	Color(3); std::cout << "~";
	Color(8); std::cout << "\\";
	Color(3); std::cout << "~~~~~";
	Color(8); std::cout << "|";
	Color(3); std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
	Color(14); std::cout << "________________________________________";
	Color(8); std::cout << "/_/____";

	if (carsOnBridgeFromNorth > 0 && carsOnBridgeFromSouth > 0) {
		Color(190); std::cout << " -ERROR-ERROR-ERROR-";
	}else if (carsOnBridgeFromNorth > 0) {
		Color(1); std::cout << "/__.|"; 
		Color(16); std::cout << "               ";
		Color(1); std::cout << "|";
	}else if (carsOnBridgeFromSouth > 0) {
		Color(1); std::cout << "|";
		Color(16); std::cout << "               ";
		Color(1); std::cout << "|.__\\";
	}else {
		std::cout << "_____________________";
	}

	Color(8); std::cout << "___\\_\\"; 
	Color(14); std::cout << "____"; 
	Color(8); std::cout << "|"; 
	Color(14); std::cout << "_______________________________________ \n";
	Color(8); std::cout << "                                        "; 
	Color(8); std::cout << " /     "; 
	
	if (carsOnBridgeFromNorth > 0 && carsOnBridgeFromSouth > 0) {
		Color(192); std::cout << " -ERROR-ERROR-ERROR-";
	} else if (carsOnBridgeFromNorth > 0) {
		Color(1); std::cout << "|__||";
		Color(16); std::cout << " Cars passing: "; 
		Color(1); std::cout << "|";
	} else if (carsOnBridgeFromSouth > 0) {
	Color(1); std::cout << "|";
		Color(16); std::cout << " Cars passing: ";
		Color(1); std::cout << "||__|";
	} else {
		std::cout << "                     ";
	}
	
	Color(8); std::cout << "    \\ "; 
	Color(8); std::cout << "               ";
	Color(6); std::cout << "|";
	
	if (carsInNorhtenQ > 1) {
		Color(12); std::cout << "   __";
		Color(2); std::cout << "           ____          \n";
	} else if (carsInNorhtenQ == 1) {
		Color(12); std::cout << "   __                         \n";
	}else {
		std::cout << "                              \n";
	}

	Color(2); std::cout << "         Cars in southern Q:           ";
	Color(8); std::cout << " /      ";
	
	if (carsOnBridgeFromNorth > 0 && carsOnBridgeFromSouth > 0) {
		Color(190); std::cout << " -ERROR-ERROR-ERROR-";
	} else if (carsOnBridgeFromNorth > 0) {
		Color(1); std::cout << "|___|";
		Color(16); std::cout << "       ";
		Color(16); std::cout << carsOnBridgeFromNorth;
		Color(16); std::cout << "       ";
		Color(1); std::cout << "|";
	} else if (carsOnBridgeFromSouth > 0) {
	Color(1); std::cout << "|";
		Color(16); std::cout << "       ";
		Color(16); std::cout << carsOnBridgeFromSouth;
		Color(16); std::cout << "       ";
		Color(1); std::cout << "|___|";
	} else {
		std::cout << "                     ";
	}
	
	Color(8); std::cout << "     \\               ";
	Color(6); std::cout << "|";
	
	if (carsInNorhtenQ > 1) {
		Color(12); std::cout << "__/__|___";
		Color(2); std::cout << "    __/_|__\\__      \n";
	}else if (carsInNorhtenQ == 1) {
		Color(12); std::cout << "__/__|___                    \n";
	}else {
		std::cout << "                              \n";
	}


	
	Color(8); std::cout << "                 "; 
	Color(2); std::cout << carsInSouthernQ;
	if (carsInSouthernQ < 10){ 
		Color(8); std::cout << "                     /    _  "; 
	}else if (carsInSouthernQ < 100){
		Color(8); std::cout << "                    /    _  ";
	}else {
		Color(8); std::cout << "                   /    _  ";
	}

	if (carsOnBridgeFromNorth > 0 && carsOnBridgeFromSouth > 0) {
		Color(192); std::cout << " -ERROR-ERROR-ERROR-";
	}else if (carsOnBridgeFromNorth > 0) {
		Color(15); std::cout << "  O  ";
		Color(8); std::cout << "========="; 
		Color(15); std::cout << "  O O  ";
	}else if (carsOnBridgeFromSouth > 0) {
		Color(15); std::cout << "  O O"; 
		Color(8); std::cout << "  =========";
		Color(15); std::cout << "  O  ";
	}else {
		std::cout << "                     ";
	}

	Color(8); std::cout << "      \\              ";
	Color(6); std::cout << "|";

	if (carsInNorhtenQ > 1) {
		Color(12); std::cout << "-";
		Color(15); std::cout << "O";
		Color(12); std::cout << "-----";
		Color(15); std::cout << "O";
		Color(12); std::cout << "-";
		Color(15); std::cout << "    "; 
		Color(2); std::cout << "-";
		Color(15); std::cout << "O";
		Color(2); std::cout << "-----";
		Color(15); std::cout << "O";
		Color(2); std::cout << "--       \n";
	}else if (carsInNorhtenQ == 1) {
		Color(12); std::cout << "-";
		Color(15); std::cout << "O";
		Color(12); std::cout << "-----";
		Color(15); std::cout << "O";
		Color(12); std::cout << "-\n";
	}else {
		std::cout << "                              \n";
	}

	Color(6); std::cout << "  __  __  __  __  __  __  __  __"; 
	Color(8); std::cout << " _____/____|";
	
	
	std::cout << "0";

	Color(8); std::cout << "|____________________________ \\____";
	Color(6); 
	
	
	if (redSouthernLightOn) {
		Color(200);
	} else {
		Color(8);
	}
	std::cout << "_  __  __| __  __  __  __  __  __  __   \n";
	
	if (carsInSouthernQ > 1) {
		Color(5); std::cout << "  .";
		Color(6); std::cout << "           ___    ";
	}
	else if (carsInSouthernQ == 1) {
		Color(6); std::cout << "              ___    ";
	}
	else {
		std::cout << "                     ";
	}
	Color(6); std::cout << "|          ";
	
	Color(8); std::cout << "/";
	Color(3); std::cout << "    ~~~~~ ";
	Color(8); std::cout << "|";
	
	
	std::cout << "0";
	
	Color(8); std::cout << "|";
	Color(3); std::cout << "                         ~~       ";
	
	
	if (redSouthernLightOn) {
		Color(8);
	}else {
		Color(160);
	}
	std::cout << "\\                                       \n";

	if (carsInSouthernQ > 1) {
		Color(5); std::cout << "  _\\_";
		Color(14); std::cout << "0";
		Color(5); std::cout << "_\\___";
		Color(6); std::cout << "  /_|_\\_  ";
	}
	else if (carsInSouthernQ == 1) {
		Color(6); std::cout << "             /_|_\\_  ";
	}
	else {
		std::cout << "                     ";
	}

	Color(6); std::cout << "|         ";
	Color(8); std::cout << "/            |          ";
	Color(3); std::cout << "~~";
	Color(8); std::cout << "                        \\       ";
	Color(2); std::cout << "Cars in northren Q:              \n";

	if (carsInSouthernQ > 1) {
		Color(5); std::cout << "  -";
		Color(15); std::cout << "O";
		Color(5); std::cout << "-----";
		Color(15); std::cout << "O";
		Color(5); std::cout << "-";
		Color(6); std::cout << "  -"; 
		Color(15); std::cout << "o"; 
		Color(6); std::cout << "--";
		Color(15); std::cout << "o";
		Color(6); std::cout << "-  ";
	}
	else if (carsInSouthernQ == 1) {
		Color(6); std::cout << "             -";
		Color(15); std::cout << "o";
		Color(6); std::cout << "--";
		Color(15); std::cout << "o";
		Color(6); std::cout << "-  ";
	}
	else {
		std::cout << "                     ";
	}

	Color(6); std::cout << "|        ";

	Color(8); std::cout << "/             |                  ";
	Color(3); std::cout << "~~";
	Color(8); std::cout << "                 \\              ";
	Color(2); std::cout << carsInNorhtenQ;
	Color(8); std::cout << "\n";
	std::cout << "_____________________";
	Color(6); std::cout << "|";
	Color(8); std::cout << "_______/";
	Color(3); std::cout << "            ~~~~                       ~~            ";
	Color(8); std::cout << "\\___________________________________ \n";

	for (int i = 0; i < 50; i++) {
		std::cout << "\n";
	}
}

void StopLight::io() {
	while(1){
		pthread_mutex_lock(&reciverMutex);
		int recieved = communication.recieve();
		pthread_mutex_unlock(&reciverMutex);
		if (recieved >= 0) {
			setLight(recieved);
			printStopLight();
		}		
		
		if (GetAsyncKeyState('S') & 0x8000) {
			pthread_mutex_lock(&transmiterMutex);
			communication.transmit(0b0100);
			pthread_mutex_unlock(&transmiterMutex);
			addToQ(2);
			printStopLight();
			while (GetAsyncKeyState('S') & 0x8000);
		}
		if (GetAsyncKeyState('N') & 0x8000) {
			pthread_mutex_lock(&transmiterMutex);
			communication.transmit(0b0001);
			pthread_mutex_unlock(&transmiterMutex);
			addToQ(1);
			printStopLight();
			while (GetAsyncKeyState('N') & 0x8000);
		}
	}
}

void StopLight::setLight(int i) {
	if (i == 9) { // North green
		redNorthenLightOn = false;
		redSouthernLightOn = true;
	} else if (i == 6) { // South green
		redNorthenLightOn = true;
		redSouthernLightOn = false;
	} else if (i == 10) { // RED
		redNorthenLightOn = true;
		redSouthernLightOn = true;
	} else if (i == 5) { // GREEN
		redNorthenLightOn = false;
		redSouthernLightOn = false;
	}
}

int StopLight::getCarsFromBridge(int i) {
	int returnValue = 0;
	if (i == 1) {
		for (int j = 0; j < 5; j++) {
			returnValue = bridgeNorth[j] + returnValue;
		}
	} else if (i == 2) {
		for (int j = 0; j < 5; j++) {
			returnValue = bridgeSouth[j] + returnValue;
		}
	}
	return returnValue;
}

void StopLight::addToQ(int16_t i){//1 == northen Q, 2 == soutern Q.
	if (i == 1) {
		carsInNorhtenQ++;
	}else if(i == 2){
		carsInSouthernQ++;
	}
}

void StopLight::runStopLight() {
	while (true) {
		// Move cars on bridge
		for (int i = 0; i < 4; i++) {
			bridgeNorth[i] = bridgeNorth[i + 1];
			bridgeSouth[i] = bridgeSouth[i + 1];
		}
		
		// Add car from queue
		if (carsInNorhtenQ > 0  && redNorthenLightOn == 0) {
			bridgeNorth[4] = 1;
			carsInNorhtenQ--;
			pthread_mutex_lock(&transmiterMutex);
			communication.transmit(0b0010);
			pthread_mutex_unlock(&transmiterMutex);
		} else {
			bridgeNorth[4] = 0;
		}
		
		if (carsInSouthernQ > 0  && redSouthernLightOn == 0) {
			bridgeSouth[4] = 1;
			carsInSouthernQ--;
			pthread_mutex_lock(&transmiterMutex);
			communication.transmit(0b1000);
			pthread_mutex_unlock(&transmiterMutex);
		} else {
			bridgeSouth[4] = 0;
		}
		
		printStopLight();
		Sleep(950);
	}
}
