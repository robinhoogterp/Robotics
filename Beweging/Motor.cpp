#include "Motor.h"

using namespace std;

int main()
{
	int pin = 26;
	int pwmValue = 0;
	int pin_forward = 27;
	int pin_backwards = 28;

	wiringPiSetup();

	softPwmCreate(pin, 0, 100);
	digitalWrite(pin_forward, 1);
	digitalWrite(pin_backwards, 0);

	for (;;) {
		std::cout << "Enter snelheid:";
		std::cin >> pwmValue;

		softPwmWrite(pin, pwmValue);
		cout<<"Snelheid nu:" << pwmValue << '\n';

	}
}
