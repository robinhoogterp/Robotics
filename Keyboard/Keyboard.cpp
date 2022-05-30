#include "Keyboard.h"

int main(void)
{
	int pin = 23;
	int pin_forward = 27;
	int pin_backwards = 28;
	int pwm_pin = 0;
	int pwmValue = 0;

	char ch;
	ch = _getch();


	wiringPiSetup();
	softPwmCreate(pin, 0, 100);

	std::cout << "Gebruik W of S om te rijden" << std::endl;
			for (pins = 0; pins < 2; ++pins)
			{
				digitalWrite(pin_forward, 0);
				digitalWrite(pin_backwards, 0);
			}

			while (true)
			{
			if (ch == 'w') {

				digitalWrite(pin_forward, 1);
				digitalWrite(pin_backwards, 0);

				pwmValue += 10;
				if (pwmValue > 100)
					pwmValue = 100;

				softPwmWrite(pwm_pin, pwmValue);
				delay(2);
			}

			if (ch == 's') {
				digitalWrite(pin_forward, 0);
				digitalWrite(pin_backwards, 1);

				pwmValue -= 10;
				if (pwmValue < 0)
					pwmValue = 0;

				softPwmWrite(pwm_pin, pwmValue);

				delay(2;
			}


			if (ch == '') {
				digitalWrite(pin_forward, 0);
				digitalWrite(pin_backwards, 0);

				pwmValue = 0;

				softPwmWrite(pwm_pin, pwmValue);

		};
	return 0;
}