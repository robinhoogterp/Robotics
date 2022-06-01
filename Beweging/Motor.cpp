#include "Motor.h"

using namespace std;

int main()
{
	int pin = 26;
	int pwmValue = 0;

	wiringPiSetup();

	softPwmCreate(pin, 0, 100);

	for (;;) {
		std::cout << "Enter snelheid:";
		std::cin >> pwmValue;

		softPwmWrite(pin, pwmValue);
		cout<<"Snelheid nu:" << pwmValue << '\n';

	}
}
