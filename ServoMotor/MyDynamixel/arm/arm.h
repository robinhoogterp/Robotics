#pragma once
#include "../ServoClass.h"
class arm
{
public:
	
	arm();
	void updateservo2de(int* ptr);
	void updateservo1ste(int* ptr);
	void updatearrayknikpunt1(int scaler1, int* ptr);
	void updatearrayknikpunt2(int scaler1, int* ptr);
	int* getpositions();
	void scaledposition(float x);
	void takeinput(int joystick1, int joystick2);
	
	int positions[4];
	int range = 4095;
	int* ptr;
	int goal1;
	int goal2;

};

