#pragma once
#include <inttypes.h>
	class StopLight {

	private:
		bool redNorthenLightOn = false;
		bool redSouthernLightOn = false;
		bool startUp = true;
		int16_t carsInNorhtenQ;
		int16_t carsInSouthernQ;
		int16_t timeUntilEmptyNorh;
		int16_t timeUntilEmptySouth;
		int bridgeNorth[5] = { 0,0,0,0,0 };
		int bridgeSouth[5] = { 0,0,0,0,0 };
		int getCarsFromBridge(int);
		void printStopLight();

	public:
		StopLight();
		void Color(int16_t color);
		void addToQ(int16_t);
		void setLight(int);
		void runStopLight();
		void io();
	};