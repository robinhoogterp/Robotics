#include "main.h"

#include "BTclient.h"
#include <iostream>
#include <cstdio>
#include <stdio.h>


int main()
{
    int* inputArr;
    Servo::InitPins();
    Servo::CreateConnection();
    Servo testservo(1);
    Servo armservoL(4);
    Servo armservoR(5);
    Servo stuurservo(6);
    arm arm1;
    
    
    bool connected = BTclient::init();
    bool btn2 = true;
    //testservo.EnableTorque();
    //testservo.ChangeMovSpd(0);
    //testservo2.ChangeMovSpd(0);
    //delay(1000);
    //testservo.ChangeMovSpd(900);
    //testservo2.ChangeMovSpd(900);
    //testservo.ChangePos(0);
    //testservo2.ChangePos(0);
    //armservoL.ChangePos(1023);
    //armservoR.ChangePos(0);

    while (connected)
    { 
       

       inputArr = BTclient::loop();
       for(int i = 0;i < 8;i++){
           std::cout << inputArr[i] << ", ";
       }    
       std::cout << '\n' << '\n';
 
    
    arm1.takeinput(inputArr[0],inputArr[3]);
    delay(200);
    
   
     
    // int pos = stuurservo.Read(36);
    // std::cout << "Starting Pos Stuur Servo "<< pos  << std::endl; 
    // std::cout << "Speed Pos Stuur Servo " << stuurservo.Read(38) << std::endl;    
    //std::cout << "Starting Pos Arm links: " << armservoL.Read(36) << std::endl;
    //std::cout << "Starting Pos Arm Rechts: " << armservoR.Read(36) << std::endl;
        //delay(1000);
        //arm1.takeinput(4000,4000);
        //delay(500);

        //armservoL.SyncWrite(2,1023,3,0);
        //delay(5000);
        

        // stuurservo.ChangePos(pos-100);
        // delay(5000);
        
      



     
            
         
    }
    
}