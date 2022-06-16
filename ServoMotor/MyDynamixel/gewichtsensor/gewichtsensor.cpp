#include "gewichtsensor.h"
#include <iostream>
unsigned long x = 0, y = 0;
unsigned long dataArray[10];
int fs = 0;
const int PIN_IN = 27;
const int PIN_OUT = 22;
const int Base = 0;
const float slope = 0;


gewichtsensor::gewichtsensor() {
    initPins();
}

void gewichtsensor::initPins() {
    pinMode(PIN_IN, INPUT);
    pinMode(PIN_OUT, OUTPUT);

}
void gewichtsensor::sample() {
    for (int j = 0; j < 10; j++)
    {
        digitalWrite(PIN_OUT, LOW);
        while (digitalRead(PIN_IN) != LOW)
            ;
        {
            for (int i = 0; i < 24; i++)  //read 24-bit data from HX711
            {
                clk();     
                bitWrite(x, 0, digitalRead(PIN_IN));
                x = x << 1;
            }
            clk();  //25th pulse
            
            y = x;
            x = 0;
            delay(1000);
        }
        dataArray[j] = y;
    }

 
    unsigned long sum = 0;

    for (j = 0; j < 10; j++)
    {
        sum += dataArray[j];
    }
    
    sum = sum / 10;
    std::cout << "gemiddelde waarde =" << sum << std::endl;
    //float calcSlope = (993 - Base)/ sum;
    //float Weight = (slope * sum) + Base;
    //std::cout << calcSlope << " slope" << std::endl;
    //std::cout << Weight << " gram" << std::endl;
}

void gewichtsensor::clk()
{
    digitalWrite(PIN_OUT, HIGH);
    digitalWrite(PIN_OUT, LOW);
}
}
