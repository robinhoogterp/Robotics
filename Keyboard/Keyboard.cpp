#include "Keyboard.h"
#include "timercpp.h"

using namespace std;

int main()
{
	int pin = 26;
	int pin_forward = 27;
	int pin_backwards = 28;
	int pwmValue = 0;
	
	int throttle;


	wiringPiSetup();
	softPwmCreate(pin, 0, 100);
	pinMode(pin_forward,OUTPUT);
	pinMode(pin_backwards,OUTPUT);
	
	std::cout << "Percentage vooruit";
	std::cin >> throttle;
		
	Timer t;

    t.setInterval([&]() {
    digitalWrite(pin_forward, 1);
	digitalWrite(pin_backwards, 0);
	softPwmWrite(pin, pwmValue+=5);
		cout << "Snelheid nu:" << pwmValue << endl;
    }, 100); 

    t.setTimeout([&]() {
        cout << "Stoppen" << endl;
        t.stop();
    digitalWrite(pin_forward, 0);
	digitalWrite(pin_backwards, 0);
    }, 3000); 


    while(true); // Keep main thread active
}
