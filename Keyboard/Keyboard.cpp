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
	int throttle;
	int timing;

	//cout << "Vul een getal in om te rijden" << endl;
	//cout << "0 t/m 2047.5 om achteruit te rijden (0 is maximale snelheid)" << endl;
	//cout << "2047.5 t/m 4095 om vooruit te rijden (4095 is maximale snelheid)" << endl;
	//cin >> throttle;
	
	if(throttle > 4095)
	{
		throttle = 4095;
	}

	wiringPiSetup();
	softPwmCreate(pin, 0, 100);
	pinMode(pin_forward,OUTPUT);
	pinMode(pin_backwards,OUTPUT);
	
	Timer t;
	
	double scaling = (throttle / 4095.0) / 0.5 - 1.0; // 2047.5 0VALUE 
	double factor = scaling * max / 87.4427191;
	double forward_thrust = factor * scaling * max * 0.01;
	double backward_thrust = -factor * -scaling * max * 0.01;
	
	if(throttle >= 2097.5)
	{
    t.setInterval([&]() 
    {
		if (timing > 30){
			throttle = rand() % 2047 + 2047;
			scaling = (throttle / 4095.0) / 0.5 - 1.0; // 2047.5 0VALUE 
			factor = scaling * max / 87.4427191;
			forward_thrust = factor * scaling * max * 0.01;
			timing = 0;
		} else {
			timing++;	
			}
		
		if(forward_thrust >= scaling * max)
		{
			forward_thrust = scaling * max;
		} else {
			forward_thrust += sqrt(forward_thrust * 0.5);
		}
	
    digitalWrite(pin_forward, 1);
	digitalWrite(pin_backwards, 0);
	softPwmWrite(pin, forward_thrust);
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << forward_thrust << endl;
		cout << "Scaling: " << " " << scaling << endl;
		cout << "Throttle: " << " " << throttle << endl;
		
    }, 100); 

	} else if(throttle <= 1997.5)
	{
	    t.setInterval([&]() 
	    {
		if(backward_thrust >= -scaling * max)
		{
			backward_thrust = -scaling * max;
		} else {
			backward_thrust += sqrt(backward_thrust*0.5);
		}
	
    digitalWrite(pin_forward, 0);
	digitalWrite(pin_backwards, 1);
	softPwmWrite(pin, backward_thrust);
	timer+=0.1;
		cout << "Timer:" << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << backward_thrust << endl;
    }, 100); 
	} 
	else 
	{

	digitalWrite(pin_forward, 0);
	digitalWrite(pin_backwards, 0);
	softPwmWrite(pin, 0);
	        cout << "Brake" << endl;
		}
	std::cout << "EIND" << endl;
	
    while(true); // Keep main thread active
}
