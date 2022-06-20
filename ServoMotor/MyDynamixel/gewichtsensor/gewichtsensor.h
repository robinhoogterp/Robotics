#pragma once
#include "wiringPi.h"

class gewichtsensor
{
	public:
	gewichtsensor();
	void initPins();
	float sample();
	void clk();
};

