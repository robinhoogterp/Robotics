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
#include "ServoClass.h"
#include "ServoClass.cpp"
#include "../socket/cpp/telemetrics.h"
#include "../socket/cpp/telemetrics.cpp"
#include "../socket/cpp/telemetryPipe.h"
#include "../socket/cpp/telemetryPipe.cpp"

class Movement {
	// PWM 
		const int pwm = 1;
	// Motor 1 Rechtsachter
		const int pin_forward1 = 4;
		const int pin_backwards1 = 24;
	// Motor 2 Rechtsvoor
		const int pin_forward2 = 21;
		const int pin_backwards2 = 22;
	// Motor 3 Linksachter
		const int pin_forward3 = 25;
		const int pin_backwards3 = 29;
	// Motor 4 Linksvoor
		const int pin_forward4 = 27;
		const int pin_backwards4 = 28;
		
		double timer = 0;
		int temporary;
		int throttle;
		double scaling;
		double factor;
		double forward_thrust;
		double backward_thrust;
		double left_thrust;
		double right_thrust;
		double current_thrust = 0;
		bool Modus = true;
		Timer d;
		Timer t;
		telemetryPipe tPipe;

		
		public:
		void setup();
		void moveStandard(double scaling, double factor, double forward_thrust, double backward_thrust , int throttle, int input2);
		void moveTank(double scaling, double factor, double left_thrust, double right_thrust , int throttle);
		void receivedata(int input1, int input2, int button);
		void updateservo(int scaler);
};
