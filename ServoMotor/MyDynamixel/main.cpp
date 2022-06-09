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
    Servo testservo2(2);
    //testservo.FactoryReset();
    //BTclient::init();
    bool btn2 = true;
    //testservo.EnableTorque();
    testservo.ChangeMovSpd(0);
    testservo2.ChangeMovSpd(0);
    delay(1000);
    testservo.ChangeMovSpd(900);
    testservo2.ChangeMovSpd(900);
    while (true)
    { 
      
        //if(btn2){
        //    testservo.ChangePos(600);
        //}
        //else{
         //  testservo.ChangePos(800);
        //}
         //testservo2.ChangePos(600);
         //delay(1000);
         //testservo2.ChangePos(800);
         //testservo.ChangePos(800);
         //delay(1000);
         //testservo2.ChangePos(400);
         //testservo.ChangePos(400);
         //delay(1000);

        //delay(5000);
        delay(1000);
        testservo.SyncWrite(1,400,2,400);
        std::cout << "Current Speed: " << testservo2.Read(32) << std::endl;
        //testservo2.ChangePos(800);
        delay(1000);
        testservo.SyncWrite(1,600,2,600);
        /*
       std::cout <<"start" << std::endl;
    
        testservo.ChangePos(740);
        
        std::cout << "Goalpos: " << testservo.Read(32) << std::endl;
        delay(1000);
        testservo.ChangePos(500);
         std::cout << "Goalpos: " << testservo.Read(30) << std::endl;
        delay(1000);
        */
       //BTclient::loop();
      //btn2 = (bool)BTclient::GetBtn2();
     
            
         
    }
    
}