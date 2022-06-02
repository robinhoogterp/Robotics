#include "Keyboard.h"
#include "timercpp.h"

using namespace std;

int main()
{
	int pin = 26;
	int pin_forward = 27;
	int pin_backwards = 28;
	double timer = 0;
	int max = 100;
	int throttle;


	wiringPiSetup();
	softPwmCreate(pin, 0, 100);
	pinMode(pin_forward,OUTPUT);
	pinMode(pin_backwards,OUTPUT);
	while(true){
	std::cout << "Value:" << endl;
	std::cin >> throttle;

			
	Timer t;
	
	
	double scaling = (throttle / 4095.0) / 0.5 - 1.0; // 2047.5 0VALUE 
	double factor = scaling * max / 87.4427191;
	double forward_thrust = factor * scaling * max * 0.01;
	double backward_thrust = -factor * -scaling * max * 0.01;
	
	if(throttle >= 2097.5)
	{
    t.setInterval([&]() 
    {
		if(forward_thrust >= scaling * max)
		{
			forward_thrust = scaling * max;
			t.stop();
		} else {
			forward_thrust += sqrt(forward_thrust * 0.2);
		}
	
    digitalWrite(pin_forward, 1);
	digitalWrite(pin_backwards, 0);
	softPwmWrite(pin, forward_thrust);
	timer+=0.1;
		cout << "Timer:" << timer << " Seconden" << endl;
		cout << "Forward_thrust" << forward_thrust << endl;
    }, 100); 
    
	} else if(throttle <= 1997.5)
	{
	    t.setInterval([&]() 
	    {
		if(backward_thrust >= -scaling * max)
		{
			backward_thrust = -scaling * max;
			t.stop();
		} else {
			backward_thrust += sqrt(backward_thrust*0.2);
		}
	
    digitalWrite(pin_forward, 0);
	digitalWrite(pin_backwards, 1);
	softPwmWrite(pin, backward_thrust);
	timer+=0.1;
		cout << "Timer:" << timer << " Seconden" << endl;
		cout << "Backward_thrust" << backward_thrust << endl;
    }, 100); 
	} 
	else 
	{

	digitalWrite(pin_forward, 0);
	digitalWrite(pin_backwards, 0);
	softPwmWrite(pin, 0);
	        cout << "Ooga booga" << endl;
		}
	std::cout << "EIND" << endl;
	}
	
    //while(true); // Keep main thread active
}
