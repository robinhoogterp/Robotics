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
#include "../ServoClass.h"
#include "../../../socket/cpp/telemetrics.h"
#include "../../../socket/cpp/telemetryPipe.h"



class Movement {
	// PWM 
		const int pwm = 12;
	// Motor 1 Linksvoor
		const int pin_forward1 = 19;
		const int pin_backwards1 = 13;
	// Motor 2 Linksachter
		const int pin_forward2 = 5;
		const int pin_backwards2 = 6;
	// Motor 3 Rechtsvoor
		const int pin_forward3 = 26;
		const int pin_backwards3 = 21;
	// Motor 4 Rechtsachter
		const int pin_forward4 = 20;
		const int pin_backwards4 = 16;
		
		double timer = 0;
		int throttle = 2047;
		double scaling = 0;
		double factor = 0;
		double forward_thrust = 0;
		double backward_thrust = 0;
		double left_thrust = 0;
		double right_thrust = 0;
		double current_thrust = 0;
		bool Modus = true;
		Timer d;
		Timer t;


		public:
		void setup();
		void updateMotor();
		void updateTank();
		void switchMode();
		void receivedata(int input1, int input2, int button);
		void updateservo(int scaler);
};
