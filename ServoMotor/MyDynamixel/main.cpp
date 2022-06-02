#include "main.h"
#include <iostream>
#include <cstdio>
#include <stdio.h>


int main()
{
    Servo::InitPins();
    Servo::CreateConnection();
    Servo testservo(43);
    Servo testservo2(2);
    while (true)
    {
        //testservo2.Reboot();
        testservo2.ChangePos(200);
        int b = testservo2.Read(34);
        //std::cout << "pos:  " << b << "\n";

        delay(2000); 
       
        testservo2.ChangePos(800);
         int a = testservo2.Read(34);
        //std::cout << "pos:  " << a << "\n";
        
        delay(2000);

        
         
    }
    
}