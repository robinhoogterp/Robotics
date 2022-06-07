#include "main.h"
#include "BTclient.h"
#include <iostream>
#include <cstdio>
#include <stdio.h>


int main()
{
    Servo::InitPins();
    Servo::CreateConnection();
    Servo testservo(1);
    //Servo testservo2(2);
    //testservo.FactoryReset();
    //BTclient::init();
    bool btn2 = true;
    while (true)
    {
        //  BTclient::loop();
        //  int btn2 = (bool)BTclient::GetBtn2();
        // std::cout << "BTN2:  "<< btn2 << '\n';
       testservo.ChangePos(800);
       int a = testservo.Read(30);
         std::cout << "goalpos:  " << a << "\n";
  
       delay(1000);
       testservo.ChangePos(300);
        //btn2 = !btn2;
        //if(btn2)
        //{
         // testservo2.ChangePos(500);
               int b = testservo.Read(30);
         std::cout << "goalpos2:  " << b << "\n";
        //else 
        //{
         //testservo2.ChangePos(800);
        //}
        delay(1000);
        //testservo2.Reboot();
        // //testservo2.ChangePos(200);
        
        
  
    
        // delay(2000); 
       
        // testservo2.ChangePos(800);
      
        //  int a = testservo2.Read(34);
        // std::cout << "Maxtorque2:   " << a << "\n";
        
        // delay(2000);

        
         
    }
    
}