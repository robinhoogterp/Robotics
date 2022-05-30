#include "Keyboard.h"

TCHAR GetKey() //returns ASCII code if you press a character(a, ? , * ,j, ~ , and so on), and
{              //returns Virtual key code if you dont press a character( VK_UP(up arrow),VK_LEFT(left arrow),VK_SPACE(space), and so on)
	INPUT_RECORD InputRecord;
	DWORD Writtten;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	while (true)
	{
		ReadConsoleInputA(hStdIn, &InputRecord, 1, &Writtten);
		if (InputRecord.EventType == KEY_EVENT && InputRecord.Event.KeyEvent.bKeyDown) break;
	}
	char ASCII = InputRecord.Event.KeyEvent.uChar.AsciiChar;
	if (ASCII) return ASCII;
	return InputRecord.Event.KeyEvent.wVirtualKeyCode;
}



int main(void)
{
	int pin = 23;
	int pin_forward = 27;
	int pin_backwards = 28;
	int pwm_pin = 0;
	int pwmValue = 0;

	char a;

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
			a = GetKey();
			if (a == 'w') {

				digitalWrite(pin_forward, 1);
				digitalWrite(pin_backwards, 0);

				pwmValue += 10;
				if (pwmValue > 100)
					pwmValue = 100;

				softPwmWrite(pwm_pin, pwmValue);
				delay(2);
			}

			if (a == 's') {
				digitalWrite(pin_forward, 0);
				digitalWrite(pin_backwards, 1);

				pwmValue -= 10;
				if (pwmValue < 0)
					pwmValue = 0;

				softPwmWrite(pwm_pin, pwmValue);

				delay(2;
			}


			if (a == '') {
				digitalWrite(pin_forward, 0);
				digitalWrite(pin_backwards, 0);

				pwmValue = 0;

				softPwmWrite(pwm_pin, pwmValue);

		};
	GetKey();
	return 0;
}