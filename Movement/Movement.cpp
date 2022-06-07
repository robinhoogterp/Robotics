#include "Movement.h"

using namespace std;

void Movement::setup(){
	wiringPiSetup();
	softPwmCreate(pin, 0, 100);
	pinMode(pin_forward,OUTPUT);
	pinMode(pin_backwards,OUTPUT);
}
void Movement::moveDC(double scaling, double factor, double forward_thrust, double backward_thrust , int throttle)
{
	Timer t;
	t.setInterval([&]() //0.1 seconde interval
		{
	
		if(throttle >= 2097.5)
		{
			if(current_thrust >= scaling * 100) // Doelsnelheid bereikt
			{
				current_thrust = scaling * 100; // Maximaliseren op doelsnelheid
		} else {
			
			current_thrust += sqrt(forward_thrust * 0.35); // Lagere snelheid, hogere value zodat opbouw tijd korter is bij lagere snelheid en hoger bij hogere snelheid. 
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
		if(current_thrust >= -scaling * 100)
		{
			current_thrust = -scaling * 100;
		} else {
			current_thrust += sqrt(backward_thrust * 0.35);
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

void Movement::receivedata(int input1, int input2){
	if(input1 > 4095)
		{	
			input1 = 4095;
		}
	
	scaling = (input1 / 4095.0) / 0.5 - 1.0; // Joystick value bruikbaar maken, getal van 0 tot 1
	factor = scaling * 100 / 87.4427191; // Scaling kleiner maken, voor een goede versnelling
	forward_thrust = factor * scaling * 100 * 1.5; // Forward_thrust bepalen
	backward_thrust = -factor * -scaling * 100 * 1.5; // Backward_thrust bepalen
	setup();
	moveDC(scaling, factor, forward_thrust , backward_thrust , input1);	
	
}
	
int main()
{
	Movement mv;
	mv.receivedata(4095,3000);
	return 0;
}
