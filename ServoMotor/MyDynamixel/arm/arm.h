#pragma once

class arm
{
public:
	
	arm();
	void updateservo(int* ptr);
	void updatearray(int scaler1, int scaler2, int* ptr);
	int* getpositions();
	void scaledposition(float x);
	void takeinput(int joystick1, int joystick2);
	
	int positions[4];
	int range = 4095;
	int* ptr;
};

