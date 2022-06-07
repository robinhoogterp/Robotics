#pragma once
#include <wiringPi.h>
#include "timercpp.h"
#include <cstdlib>
#include <softPwm.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <atomic>

class Movement {
		const int pin = 26;
		const int pin_forward = 27;
		const int pin_backwards = 28;
		double timer = 0;
		int temporary;
		int throttle;
		double scaling;
		double factor;
		double forward_thrust;
		double backward_thrust;
		double current_thrust = 0;
		
		public:
		void setup();
		void moveDC(double scaling, double factor, double forward_thrust, double backward_thrust , int throttle);
		void receivedata(int input1, int input2);
};
