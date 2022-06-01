#include "main.h"
#include <iostream>
#include <cstdio>



int main()
{
    Servo::InitPins();
    Servo::CreateConnection();
    Servo testservo(43);
    Servo testservo2(2);
    while (true)
    {
       
        testservo.ChangePos(400);
        delay(50); 
        testservo2.ChangePos(400);
        delay(1000); 
        testservo2.ChangePos(600);
        delay(50);
        testservo.ChangePos(600);
        delay(1000);

        // int delaytime =250;
        //  Servo::ChangePos(100);
        //  delay(delaytime);
        //  Servo::ChangePos(200);
        //  delay(delaytime); 
        //  Servo::ChangePos(300);
        //  delay(delaytime);
        //  Servo::ChangePos(400);
        //  delay(delaytime);  
        //  Servo::ChangePos(500);
        //  delay(delaytime);
        //  Servo::ChangePos(600);
        //  delay(delaytime);
        //  Servo::ChangePos(700);
        //  delay(delaytime);
        //  Servo::ChangePos(800);
        //  delay(delaytime);
        //  Servo::ChangePos(900);
        //  delay(delaytime);
        //  Servo::ChangePos(1000);
        //  delay(2000); 
         
    }
    
}