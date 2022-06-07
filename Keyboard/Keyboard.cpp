#include "Keyboard.h"
#include "timercpp.h"
#include <cstdlib>


using namespace std;

int main()
{
	int pin = 26;
	int pin_forward = 27;
	int pin_backwards = 28;
	double timer = 0;
	int max = 100;
	int timing;
	int throttle;
	double scaling;
	double factor;
	double forward_thrust;
	double backward_thrust;
	double goal_thrust;
	double current_thrust = 0;

	wiringPiSetup();
	softPwmCreate(pin, 0, 100);
	pinMode(pin_forward,OUTPUT);
	pinMode(pin_backwards,OUTPUT);
	
	Timer t;
	t.setInterval([&]() 
		{
			if(timing > 30){
			throttle = rand() % 4095 + 0;	
			timing = 0;		
				} else {
					timing++;
					}
			
			scaling = (throttle / 4095.0) / 0.5 - 1.0; // 2047.5 0VALUE 
			goal_thrust = scaling * max;
			factor = scaling * max / 87.4427191;
			forward_thrust = factor * scaling * max * 1.0;
			backward_thrust = -factor * -scaling * max * 1.0;
			
			if(throttle > 4095)
			{	
				throttle = 4095;
			}
	
		if(throttle >= 2097.5)
		{
			if(current_thrust >= scaling * max)
			{
				current_thrust = scaling * max;
		} else {
			
			current_thrust += sqrt(forward_thrust * 0.1);
			forward_thrust = current_thrust;
		}
	
    digitalWrite(pin_forward, 1);
	digitalWrite(pin_backwards, 0);
	softPwmWrite(pin, current_thrust);
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Scaling: " << " " << scaling << endl;
		cout << "Throttle: " << " " << throttle << endl;
		

	} else if(throttle <= 1997.5)
	{
		if(current_thrust >= -scaling * max)
		{
			current_thrust = -scaling * max;
		} else {
			current_thrust += sqrt(backward_thrust*0.1);
			backward_thrust = current_thrust;
		}
	
    digitalWrite(pin_forward, 0);
	digitalWrite(pin_backwards, 1);
	softPwmWrite(pin, current_thrust);
	timer+=0.1;
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Scaling: " << " " << scaling << endl;
		cout << "Throttle: " << " " << throttle << endl;
	} 
	else 
	{

	digitalWrite(pin_forward, 0);
	digitalWrite(pin_backwards, 0);
	softPwmWrite(pin, 0);
	current_thrust = 0;
	        cout << "Brake" << endl;
		}
}, 100); 
	
    while(true); // Keep main thread active
}
