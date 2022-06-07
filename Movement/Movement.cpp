#include "Movement.h"
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
	int temporary;
	int throttle;
	double scaling;
	double factor;
	double forward_thrust;
	double backward_thrust;
	double current_thrust = 0;

	wiringPiSetup();
	softPwmCreate(pin, 0, 100);
	pinMode(pin_forward,OUTPUT);
	pinMode(pin_backwards,OUTPUT);
	
	Timer t;
	t.setInterval([&]() //0.1 seconde interval
		{
			if(temporary> 30){ 
			throttle = rand() % 4095 + 0;	
			temporary = 0;		
				} else {
					temporary++;
					}
			
			scaling = (throttle / 4095.0) / 0.5 - 1.0; // Joystick value bruikbaar maken, getal van 0 tot 1
			factor = scaling * max / 87.4427191; // Scaling kleiner maken, voor een goede versnelling
			forward_thrust = factor * scaling * max * 1.5; // Forward_thrust bepalen
			backward_thrust = -factor * -scaling * max * 1.5; // Backward_thrust bepalen
			
			if(throttle > 4095)
			{	
				throttle = 4095;
			}
	
		if(throttle >= 2097.5)
		{
			if(current_thrust >= scaling * max) // Doelsnelheid bereikt
			{
				current_thrust = scaling * max; // Maximaliseren op doelsnelheid
		} else {
			
			current_thrust += sqrt(forward_thrust * 0.1); // Lagere snelheid, hogere value zodat opbouw tijd korter is bij lagere snelheid en hoger bij hogere snelheid. 
			forward_thrust = current_thrust; // Nieuwe snelheid in forward_thrust zetten
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
			current_thrust += sqrt(backward_thrust * 0.1);
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
	        cout << "Remmen" << endl;
		}
}, 100); 
	
    while(true); // Keep main thread active
}
