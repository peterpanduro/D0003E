#pragma once
class StopLight{

private:
	bool redNorthenLight;
	bool redSouthernLight;
	int carsInNorhtenQ;
	int carsInSouthernQ;
	int carsOnBridgeFromNorth;
	int carsOnBridgeFromSouth;
	int timeUntilEmptyNorh;
	int timeUntilEmptySouth;

public:

	StopLight(void);

	void printStopLight();
};



