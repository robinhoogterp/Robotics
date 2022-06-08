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
	// PWM 
		const int pwm = 26;
	// Motor 1 Linksvoor
		const int pin_forward1 = 23;
		const int pin_backwards1 = 24;
	// Motor 2 Linksachter
		const int pin_forward2 = 21;
		const int pin_backwards2 = 22;
	// Motor 3 Rechtsvoor
		const int pin_forward3 = 25;
		const int pin_backwards3 = 29;
	// Motor 4 Rechtsachter
		const int pin_forward4 = 27;
		const int pin_backwards4 = 28;
		
		double timer = 0;
		int temporary;
		int throttle;
		double scaling;
		double factor;
		double forward_thrust;
		double backward_thrust;
		double current_thrust = 0;
		bool Modus = true;
		
		public:
		void setup();
		void moveStandard(double scaling, double factor, double forward_thrust, double backward_thrust , int throttle);
		void moveTank(double scaling, double factor, double left_thrust, double right_thrust , int throttle);
		void receivedata(int input1, int input2);
};
