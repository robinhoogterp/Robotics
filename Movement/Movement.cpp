#include "Movement.h"

using namespace std;

void Movement::setup(){
	wiringPiSetup();
	// PWM
	softPwmCreate(pwm, 0, 100);
	// Motor 1
	pinMode(pin_forward1,OUTPUT);
	pinMode(pin_backwards1,OUTPUT);
	// Motor 2
	pinMode(pin_forward2,OUTPUT);
	pinMode(pin_backwards2,OUTPUT);
	// Motor 3
	pinMode(pin_forward3,OUTPUT);
	pinMode(pin_backwards3,OUTPUT);
	// Motor 4
	pinMode(pin_forward4,OUTPUT);
	pinMode(pin_backwards4,OUTPUT);

}
void Movement::moveStandard(double scaling, double factor, double forward_thrust, double backward_thrust , int throttle)
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
	
    digitalWrite(pin_forward1, 1);
	digitalWrite(pin_backwards1, 0);
	digitalWrite(pin_forward2, 1);
	digitalWrite(pin_backwards2, 0);
    digitalWrite(pin_forward3, 1);
	digitalWrite(pin_backwards3, 0);
    digitalWrite(pin_forward4, 1);
	digitalWrite(pin_backwards4, 0);
	softPwmWrite(pwm, current_thrust);
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
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
	
    digitalWrite(pin_forward1, 0);
	digitalWrite(pin_backwards1, 1);
	digitalWrite(pin_forward2, 0);
	digitalWrite(pin_backwards2, 1);
    digitalWrite(pin_forward3, 0);
	digitalWrite(pin_backwards3, 1);
    digitalWrite(pin_forward4, 0);
	digitalWrite(pin_backwards4, 1);
	softPwmWrite(pwm, current_thrust);
	timer+=0.1;
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Throttle: " << " " << throttle << endl;
	} 
	else 
	{

    digitalWrite(pin_forward1, 0);
	digitalWrite(pin_backwards1, 0);
	digitalWrite(pin_forward2, 0);
	digitalWrite(pin_backwards2, 0);
    digitalWrite(pin_forward3, 0);
	digitalWrite(pin_backwards3, 0);
    digitalWrite(pin_forward4, 0);
	digitalWrite(pin_backwards4, 0);
	softPwmWrite(pwm, 0);
	current_thrust = 0;
	        cout << "Remmen" << endl;
		}
}, 100); 
	
    while(true); // Keep main thread active
}

void Movement::moveTank(double scaling, double factor, double left_thrust, double right_thrust , int throttle)
{
	Timer d;
	d.setInterval([&]() //0.1 seconde interval
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
	
    digitalWrite(pin_forward1, 1);
	digitalWrite(pin_backwards1, 0);
	digitalWrite(pin_forward2, 1);
	digitalWrite(pin_backwards2, 0);
	digitalWrite(pin_forward3, 0);
	digitalWrite(pin_backwards3, 1);
	digitalWrite(pin_forward4, 0);
	digitalWrite(pin_backwards4, 1);
	softPwmWrite(pin, current_thrust);
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
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
	
    digitalWrite(pin_forward1, 0);
	digitalWrite(pin_backwards1, 1);
	digitalWrite(pin_forward2, 0);
	digitalWrite(pin_backwards2, 1);
	digitalWrite(pin_forward3, 1);
	digitalWrite(pin_backwards3, 0);
	digitalWrite(pin_forward4, 1);
	digitalWrite(pin_backwards4, 0);
	softPwmWrite(pin, current_thrust);
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Throttle: " << " " << throttle << endl;
	} 
	else 
	{

    digitalWrite(pin_forward1, 0);
	digitalWrite(pin_backwards1, 0);
	digitalWrite(pin_forward2, 0);
	digitalWrite(pin_backwards2, 0);
	digitalWrite(pin_forward3, 0;
	digitalWrite(pin_backwards3, 0);
	digitalWrite(pin_forward4, 0);
	digitalWrite(pin_backwards4, 0);
	softPwmWrite(pin, 0);
	current_thrust = 0;
	        cout << "Wachten op nieuwe input, Remmen" << endl;
		}		
}, 100); 
	
    while(true); // Keep main thread active
}

void Movement::receivedata(int input1, int input2, int button){
	if(input1 > 4095)
		{	
			input1 = 4095;
		};
		
	if(button = 1){
		Modus = !Modus;
		};
	
	if(Modus = True){
	
	scaling = (input1 / 4095.0) / 0.5 - 1.0; // Joystick value bruikbaar maken, getal van 0 tot 1
	factor = scaling * 100 / 87.4427191; // Scaling kleiner maken, voor een goede versnelling
	forward_thrust = factor * scaling * 100 * 1.5; // Forward_thrust bepalen
	backward_thrust = -factor * -scaling * 100 * 1.5; // Backward_thrust bepalen
	setup();
	moveStandard(scaling, factor, forward_thrust , backward_thrust , input1);	
} else {
	setup();
	moveTank(scaling, factor, left_thrust , right_thrust , input2);
	}
}
	
int main()
{
	Movement mv;
	mv.receivedata(4095,3000,1);
	return 0;
}
