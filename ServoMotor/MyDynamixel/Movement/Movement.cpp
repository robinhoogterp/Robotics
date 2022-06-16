#include "Movement.h"
using namespace std;
Servo knik_punt(6);
bool mode = false;

		
void Movement::setup(){
	
	telemetrics* tm = telemetrics::getInstance();
	
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
	t.setInterval([&]() {Movement::switchMode();} , 100); //0.1 seconde interval

}
void Movement::updateservo(int scaler){
	int pos = knik_punt.Read(36);
	
	cout << "Pos:  "<< pos << endl;
	if (pos < 300 && scaler < 0) {
		cout << "Te laag" << endl;
		
	} else if(pos > 900 && scaler > 0) {	
				cout << "Te Hoog" << endl;

	} else {
				cout << "Goed" << endl;
		knik_punt.ChangePos(pos + scaler);
	}
}
void Movement::switchMode()
{
	if (mode)
	{
		Movement::updateTank();
	}
	else
	{
		Movement::updateMotor();
	}
}

void Movement::updateMotor()
{
	if(throttle >= 2200)
		{
			if(current_thrust >= scaling * 100) // Doelsnelheid bereikt
			{
				// TODO misschien weg.
				current_thrust = scaling * 100; // Maximaliseren op doelsnelheid
				return;
		} else {
			
			current_thrust += sqrt(forward_thrust * 0.35); // Lagere snelheid, hogere value zodat opbouw tijd korter is bij lagere snelheid en hoger bij hogere snelheid. 
			forward_thrust = current_thrust; // Nieuwe snelheid in forward_thrust zetten
		}
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 1);
    (*tm).telemetry.pf1 = 1;
	digitalWrite(pin_backwards1, 0);
	(*tm).telemetry.pb1 = 0;
	digitalWrite(pin_forward2, 1);
	(*tm).telemetry.pf2 = 1;
	digitalWrite(pin_backwards2, 0);
	(*tm).telemetry.pb2 = 0;
    digitalWrite(pin_forward3, 1);
    (*tm).telemetry.pf3 = 1;
	digitalWrite(pin_backwards3, 0);
	(*tm).telemetry.pb3 = 0;
    digitalWrite(pin_forward4, 1);
    (*tm).telemetry.pf4 = 1;
	digitalWrite(pin_backwards4, 0);
	(*tm).telemetry.pb4 = 0;
	softPwmWrite(pwm, current_thrust);
	(*tm).telemetry.dc = current_thrust;
	
	//TODO kan misschien weg
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Throttle: " << " " << throttle << endl;
		

	} else if(throttle <= 1800)
	{
		if(current_thrust >= -scaling * 100)
		{
			current_thrust = -scaling * 100;
	        return;
		} else {
			current_thrust += sqrt(backward_thrust * 0.35);
			backward_thrust = current_thrust;
		}
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 0);
    (*tm).telemetry.pf1 = 0;
	digitalWrite(pin_backwards1, 1);
	(*tm).telemetry.pb1 = 1;
	digitalWrite(pin_forward2, 0);
	(*tm).telemetry.pf2 = 0;
	digitalWrite(pin_backwards2, 1);
	(*tm).telemetry.pb2 = 1;
    digitalWrite(pin_forward3, 0);
    (*tm).telemetry.pf3 = 0;
	digitalWrite(pin_backwards3, 1);
	(*tm).telemetry.pb4 = 1;
    digitalWrite(pin_forward4, 0);
    (*tm).telemetry.pf4 = 0;
	digitalWrite(pin_backwards4, 1);
	(*tm).telemetry.pb4 = 1;
	softPwmWrite(pwm, current_thrust);
	
	//TODO kan misschien weg
	timer+=0.1;
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Throttle: " << " " << throttle << endl;
	} 
	else 
	{
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 1);
    (*tm).telemetry.pf1 = 1;
	digitalWrite(pin_backwards1, 1);
	(*tm).telemetry.pb1 = 1;
	digitalWrite(pin_forward2, 1);
	(*tm).telemetry.pf2 = 1;
	digitalWrite(pin_backwards2, 1);
	(*tm).telemetry.pb2 = 1;
    digitalWrite(pin_forward3, 1);
    (*tm).telemetry.pf3 = 1;
	digitalWrite(pin_backwards3, 1);
	(*tm).telemetry.pb4 = 1;
    digitalWrite(pin_forward4, 1);
    (*tm).telemetry.pf4 = 1;
	digitalWrite(pin_backwards4, 1);
	(*tm).telemetry.pb4 = 1;
	softPwmWrite(pwm, 0);
	current_thrust = 0;
	(*tm).telemetry.dc = current_thrust;
	        cout << "Remmen" << endl;
	        return;
		}
};


void Movement::updateTank()
{
		if(throttle >= 2200)
		{
			if(current_thrust >= scaling * 100)
			{
				current_thrust = scaling * 100;
				return;
		} else {
			
			current_thrust += sqrt(left_thrust * 0.35);
			left_thrust = current_thrust;
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
	(*tm).telemetry.dc = current_thrust;
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Throttle: " << " " << throttle << endl;
		

	} else if(throttle <= 1800)
	{
		if(current_thrust >= -scaling * 100)
		{
			current_thrust = -scaling * 100;
		} else {
			current_thrust += sqrt(right_thrust * 0.35);
			right_thrust = current_thrust;
		}
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 0);
    (*tm).telemetry.pf1 = 1;
	digitalWrite(pin_backwards1, 1);
	(*tm).telemetry.pb1 = 0;
	digitalWrite(pin_forward2, 0);
	(*tm).telemetry.pf2 = 1;
	digitalWrite(pin_backwards2, 1);
	(*tm).telemetry.pb2 = 0;
    digitalWrite(pin_forward3, 1);
    (*tm).telemetry.pf3 = 0;
	digitalWrite(pin_backwards3, 0);
	(*tm).telemetry.pb3 = 1;
    digitalWrite(pin_forward4, 1);
    (*tm).telemetry.pf4 = 0;
	digitalWrite(pin_backwards4, 0);
	(*tm).telemetry.pb4 = 1;
	softPwmWrite(pwm, current_thrust);
	(*tm).telemetry.dc = current_thrust;
	timer+=0.1;
	
		cout << "Timer: " << " " << timer << " Seconden" << endl;
		cout << "Snelheid: " << " " << current_thrust << endl;
		cout << "Throttle: " << " " << throttle << endl;
	} 
	else 
	{
	telemetrics* tm = telemetrics::getInstance();
	
    digitalWrite(pin_forward1, 1);
    (*tm).telemetry.pf1 = 1;
	digitalWrite(pin_backwards1, 1);
	(*tm).telemetry.pb1 = 1;
	digitalWrite(pin_forward2, 1);
	(*tm).telemetry.pf2 = 1;
	digitalWrite(pin_backwards2, 1);
	(*tm).telemetry.pb2 = 1;
    digitalWrite(pin_forward3, 1);
    (*tm).telemetry.pf3 = 1;
	digitalWrite(pin_backwards3, 1);
	(*tm).telemetry.pb3 = 1;
    digitalWrite(pin_forward4, 1);
    (*tm).telemetry.pf4 = 1;
	digitalWrite(pin_backwards4, 1);
	(*tm).telemetry.pb4 = 1;
	softPwmWrite(pwm, 0);
	current_thrust = 0;
	(*tm).telemetry.dc = current_thrust;
	        cout << "Remmen tank" << endl;
		}
		
}

void Movement::receivedata(int input1, int input2, int button){
	if(input1 > 4095)
		{	
			input1 = 4095;
		}
		
	if(button == 1){
		mode = true;
		}
		else
		{
			mode = false; 
			}
	
	if(mode == false){
	throttle = input1;
	scaling = (input1 / 4095.0) / 0.5 - 1.0; // Joystick value bruikbaar maken, getal van 0 tot 1
	factor = scaling * 100 / 87.4427191; // Scaling kleiner maken, voor een goede versnelling
	forward_thrust = factor * scaling * 100 * 1.5; // Forward_thrust bepalen
	backward_thrust = -factor * -scaling * 100 * 1.5; // Backward_thrust bepalen
	if(input2 > 3000) {
		updateservo(-50);
	}
	 else if(input2 < 2000){
		updateservo(50);
	} 

} else {
	scaling = (input2 / 4095.0) / 0.5 - 1.0;
	factor = scaling * 100 / 87.4427191;
	left_thrust = factor * scaling * 100 * 1.5;
	right_thrust = -factor * -scaling * 100 * 1.5;
	throttle = input2;
	}
}




