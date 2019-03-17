
#include "pch.h"
#include "StopLight.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//stopLight::stopLight() {
//	redNorthenLight = false;
//	redSouthernLight = false;
//	carsInNorhtenQ = 0;
//	carsInSouthernQ = 0;
//	carsOnBridgeFromNorth = 0;
//	carsOnBridgeFromSouth = 0;
//	timeUntilEmptyNorh = 0;
//	timeUntilEmptySouth = 0;
//}

StopLight::StopLight() {
	redNorthenLight = true;
	redSouthernLight = true;
	carsInNorhtenQ = 0;
	carsInSouthernQ = 0;
	carsOnBridgeFromNorth = 0;
	carsOnBridgeFromSouth = 0;
	timeUntilEmptyNorh = 0;
	timeUntilEmptySouth = 0;
}

// 1 = darkblue
// 0 = black
// 3 = lightblue
// 4 = red
// 5 = pruple
// 6 = yellow/orange
// 15 = white
// 8 = gray
// 9 = blue
//
//
//


void Color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void StopLight::printStopLight() {

	for (int i = 0; i < 5; i++) {
		std::cout << "\n";
	}

	Color(8); std::cout << "\n                                             ________________________";
	Color(6); std::cout << "                                \\          /       \n";
	Color(15); std::cout << "             ^^                             ";
	Color(8); std::cout << "/                        \\        _";
	Color(6); std::cout << "                       \\  ____  /       \n";
	Color(15); std::cout << "           ^^  ^^";
	Color(8); std::cout << "                          /                          \\      |";

	if (redNorthenLight) {
		Color(4);
	}
	else {
		Color(0);
	}
	std::cout << "0";

	Color(8); std::cout << "|";
	Color(6); std::cout << "                        /    \\         \n";
	Color(8); std::cout << "                                          / __________________________ \\     |";

	if (redNorthenLight) {
		Color(0);
	}
	else {
		Color(10);
	}
	std::cout << "0";

	Color(8); std::cout << "|";
	Color(6); std::cout << "                 ----- /      \\ -----  \n";
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
		std::cout << " -ERROR-ERROR-ERROR-";
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
		std::cout << " -ERROR-ERROR-ERROR-";
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
		std::cout << " -ERROR-ERROR-ERROR-";
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
		std::cout << " -ERROR-ERROR-ERROR-";
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
	
	if (redSouthernLight) {
		Color(4);
	} else {
		Color(0);
	}
	std::cout << "0";

	Color(8); std::cout << "|____________________________ \\____";
	Color(6); std::cout << "_  __  __| __  __  __  __  __  __  __   \n";
	
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
	
	if (redSouthernLight) {
		Color(0);
	}else {
		Color(10);
	}
	std::cout << "0";
	
	Color(8); std::cout << "|";
	Color(3); std::cout << "                         ~~       ";
	Color(8); std::cout << "\\                                       \n";

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

	for (int i = 0; i < 60; i++) {
		std::cout << "\n";
	}
}

void StopLight::addToQ(int i){//1 == northen Q, 2 == soutern Q.
	if (i == 1) {
		carsInNorhtenQ++;
	}else if(i == 2){
		carsInSouthernQ++;
	}
}

void StopLight::toggleLight(int i) {//togglels the stoplight. If 1 == nort, 2 == south
	if (1 == i) {
		redNorthenLight = (true == redNorthenLight) ? false : true;
	}else if (i == 2){
		redSouthernLight = (true == redSouthernLight) ? false : true;
	}
	
	
}