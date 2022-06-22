#include "gewichtsensor.h"
#include <iostream>
int x = 0, y = 0;
float dataArray[10];
//int fs = 0;
const int PIN_IN = 22;
const int PIN_OUT = 27;
const int Base = 1916410;
const float slope = 0.000229075;


gewichtsensor::gewichtsensor() {
    initPins();
}

void gewichtsensor::initPins() {
    pinMode(PIN_IN, INPUT);
    pinMode(PIN_OUT, OUTPUT);

}
float gewichtsensor::sample() {
    
    for (int j = 0; j < 10; j++)
    {
        digitalWrite(PIN_OUT, LOW);
        std::cout << "Meting: "  << j <<std::endl;
        delay(1000);
        while (digitalRead(PIN_IN) != HIGH)
        {
            
            for (int i = 0; i < 24; i++)  //read 24-bit data from HX711
            {
                clk();     
                //delayMicroseconds(1);
                //bitWrite(x, 0, digitalRead(PIN_IN));
                x += digitalRead(PIN_IN);
                //std::cout << "XWAARDE" << x << std::endl;
                //std::cout << "I = " << i << std::endl;
                x = x << 1;
            }
            clk();  //25th pulse
            
            y = x;
            x = 0;
            
            break;
        }
        dataArray[j] = y;
    }

 
    float sum = -1;

    for (int j = 0; j < 10; j++)
    {
        sum += dataArray[j];
    }
    
    sum = sum / 10;
    std::cout << "gemiddelde waarde =" << sum << std::endl;
    float Weight = slope * (sum - Base);
    std::cout << Weight << " gram" << std::endl;
    return sum;
}

void gewichtsensor::clk()
{
    digitalWrite(PIN_OUT, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN_OUT, LOW);
    delayMicroseconds(1);
}

