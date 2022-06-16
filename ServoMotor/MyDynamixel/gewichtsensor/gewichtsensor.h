#pragma once
#include "wiringPi.h"

class gewichtsensor
{
	void initPins();
	void sample();
	void clk();
};

