#pragma once
class StopLight{

private:
	bool redNorthenLightOn = true;
	bool redSouthernLightOn = true;
	bool hasBeenUpdated = true;
	bool startUp = true;
	int carsInNorhtenQ;
	int carsInSouthernQ;
	int carsOnBridgeFromNorth;
	int carsOnBridgeFromSouth;
	int timeUntilEmptyNorh;
	int timeUntilEmptySouth;

	void printStopLight();

public:

	
	void addToQ(int i);
	void toggleLight(int i);
	void runStopLight();
	void updateStopLight();
};



