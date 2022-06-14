#include "Movement.h"
using namespace std;
telemetrics* telemetrics::instance = 0;
Servo knik_punt(6);
		
void Movement::setup(){
	
	telemetrics* tm = telemetrics::getInstance();
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
void Movement::updateservo(int scaler){
	if (knik_punt.Read(36) < 400) {
		
	} else if(knik_punt.Read(36) < 700) {	
		

	} else {
		knik_punt.ChangePos(knik_punt.Read(36) + scaler);
	}
}
void Movement::moveStandard(double scaling, double factor, double forward_thrust, double backward_thrust , int throttle, int input2)
{
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
	telemetrics* tm = telemetrics::getInstance();

	
    digitalWrite(pin_forward1, 1);
    (*tm).telemetry.pf1 = pin_forward1;
	digitalWrite(pin_backwards1, 0);
	(*tm).telemetry.pb1 = pin_backwards1;
	digitalWrite(pin_forward2, 1);
	(*tm).telemetry.pf2 = pin_forward2;
	digitalWrite(pin_backwards2, 0);
	(*tm).telemetry.pb2 = pin_backwards2;
    digitalWrite(pin_forward3, 1);
    (*tm).telemetry.pf3 = pin_forward3;
	digitalWrite(pin_backwards3, 0);
	(*tm).telemetry.pb3 = pin_backwards3;
    digitalWrite(pin_forward4, 1);
    (*tm).telemetry.pf4 = pin_forward4;
	digitalWrite(pin_backwards4, 0);
	(*tm).telemetry.pb4 = pin_backwards4;
	softPwmWrite(pwm, current_thrust);
	(*tm).telemetry.dc1 = current_thrust;
	
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
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 0);
    (*tm).telemetry.pf1 = pin_forward1;
	digitalWrite(pin_backwards1, 1);
	(*tm).telemetry.pb1 = pin_backwards1;
	digitalWrite(pin_forward2, 0);
	(*tm).telemetry.pf2 = pin_forward2;
	digitalWrite(pin_backwards2, 1);
	(*tm).telemetry.pb2 = pin_backwards2;
    digitalWrite(pin_forward3, 0);
    (*tm).telemetry.pf3 = pin_forward3;
	digitalWrite(pin_backwards3, 1);
	(*tm).telemetry.pb4 = pin_backwards3;
    digitalWrite(pin_forward4, 0);
    (*tm).telemetry.pf4 = pin_forward4;
	digitalWrite(pin_backwards4, 1);
	(*tm).telemetry.pb4 = pin_backwards4;
	softPwmWrite(pwm, current_thrust);
	timer+=0.1;
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Throttle: " << " " << throttle << endl;
	} 
	else 
	{
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 1);
    (*tm).telemetry.pf1 = pin_forward1;
	digitalWrite(pin_backwards1, 1);
	(*tm).telemetry.pb1 = pin_backwards1;
	digitalWrite(pin_forward2, 1);
	(*tm).telemetry.pf2 = pin_forward2;
	digitalWrite(pin_backwards2, 1);
	(*tm).telemetry.pb2 = pin_backwards2;
    digitalWrite(pin_forward3, 1);
    (*tm).telemetry.pf3 = pin_forward3;
	digitalWrite(pin_backwards3, 1);
	(*tm).telemetry.pb4 = pin_backwards3;
    digitalWrite(pin_forward4, 1);
    (*tm).telemetry.pf4 = pin_forward4;
	digitalWrite(pin_backwards4, 1);
	(*tm).telemetry.pb4 = pin_backwards4;
	softPwmWrite(pwm, 0);
	current_thrust = 0;
	(*tm).telemetry.dc1 = current_thrust;
	        cout << "Remmen" << endl;
		}
		
}, 100); 
	
    while(true); // Keep main thread active
}

void Movement::moveTank(double scaling, double factor, double left_thrust, double right_thrust , int throttle)
{
	d.setInterval([&]() //0.1 seconde interval
		{
	
		if(throttle >= 2097.5)
		{
			if(current_thrust >= scaling * 100)
			{
				current_thrust = scaling * 100;
		} else {
			
			current_thrust += sqrt(left_thrust * 0.35);
			left_thrust = current_thrust;
		}
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 0);
    (*tm).telemetry.pf1 = pin_forward1;
	digitalWrite(pin_backwards1, 1);
	(*tm).telemetry.pb1 = pin_backwards1;
	digitalWrite(pin_forward2, 0);
	(*tm).telemetry.pf2 = pin_forward2;
	digitalWrite(pin_backwards2, 1);
	(*tm).telemetry.pb2 = pin_backwards2;
    digitalWrite(pin_forward3, 1);
    (*tm).telemetry.pf3 = pin_forward3;
	digitalWrite(pin_backwards3, 0);
	(*tm).telemetry.pb3 = pin_backwards3;
    digitalWrite(pin_forward4, 1);
    (*tm).telemetry.pf4 = pin_forward4;
	digitalWrite(pin_backwards4, 0);
	(*tm).telemetry.pb4 = pin_backwards4;
	softPwmWrite(pwm, current_thrust);
	(*tm).telemetry.dc1 = current_thrust;
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
			current_thrust += sqrt(right_thrust * 0.35);
			right_thrust = current_thrust;
		}
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 1);
    (*tm).telemetry.pf1 = pin_forward1;
	digitalWrite(pin_backwards1, 0);
	(*tm).telemetry.pb1 = pin_backwards1;
	digitalWrite(pin_forward2, 1);
	(*tm).telemetry.pf2 = pin_forward2;
	digitalWrite(pin_backwards2, 0);
	(*tm).telemetry.pb2 = pin_backwards2;
    digitalWrite(pin_forward3, 0);
    (*tm).telemetry.pf3 = pin_forward3;
	digitalWrite(pin_backwards3, 1);
	(*tm).telemetry.pb3 = pin_backwards3;
    digitalWrite(pin_forward4, 0);
    (*tm).telemetry.pf4 = pin_forward4;
	digitalWrite(pin_backwards4, 1);
	(*tm).telemetry.pb4 = pin_backwards4;
	softPwmWrite(pwm, current_thrust);
	(*tm).telemetry.dc1 = current_thrust;
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Throttle: " << " " << throttle << endl;
	} 
	else 
	{
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 1);
    (*tm).telemetry.pf1 = pin_forward1;
	digitalWrite(pin_backwards1, 1);
	(*tm).telemetry.pb1 = pin_backwards1;
	digitalWrite(pin_forward2, 1);
	(*tm).telemetry.pf2 = pin_forward2;
	digitalWrite(pin_backwards2, 1);
	(*tm).telemetry.pb2 = pin_backwards2;
    digitalWrite(pin_forward3, 1);
    (*tm).telemetry.pf3 = pin_forward3;
	digitalWrite(pin_backwards3, 1);
	(*tm).telemetry.pb3 = pin_backwards3;
    digitalWrite(pin_forward4, 1);
    (*tm).telemetry.pf4 = pin_forward4;
	digitalWrite(pin_backwards4, 1);
	(*tm).telemetry.pb4 = pin_backwards4;
	softPwmWrite(pwm, 0);
	current_thrust = 0;
	(*tm).telemetry.dc1 = current_thrust;
	        cout << "Wachten op nieuwe input, Remmen" << endl;
		}		
}, 100); 
	
    while(true);
}

void Movement::receivedata(int input1, int input2, int button){
	if(input1 > 4095)
		{	
			input1 = 4095;
		};
		
	if(button == 1){
		Modus = !Modus;
		};
	
	if(Modus == true){
	
	scaling = (input1 / 4095.0) / 0.5 - 1.0; // Joystick value bruikbaar maken, getal van 0 tot 1
	factor = scaling * 100 / 87.4427191; // Scaling kleiner maken, voor een goede versnelling
	forward_thrust = factor * scaling * 100 * 1.5; // Forward_thrust bepalen
	backward_thrust = -factor * -scaling * 100 * 1.5; // Backward_thrust bepalen
	setup();
	if(input2 > 3000) {
		updateservo(50);
	} else if(input2 < 2000){
		updateservo(-50);
	} 
	moveStandard(scaling, factor, forward_thrust , backward_thrust , input1, input2);	
	d.stop();
} else {
	setup();
	scaling = (input2 / 4095.0) / 0.5 - 1.0;
	factor = scaling * 100 / 87.4427191;
	left_thrust = factor * scaling * 100 * 1.5;
	right_thrust = -factor * -scaling * 100 * 1.5;
	moveTank(scaling, factor, left_thrust , right_thrust , input2);
	t.stop();
	}
}

int main()
{
	Movement mv;
	
	mv.receivedata(4095,4095,0);
	return 0;
}


