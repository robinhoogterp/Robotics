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
    Servo test(2);
    Servo test2(3);
    Servo armservoL(4);
    Servo armservoR(5);
    Servo stuurservo(6);
    arm arm1;
    
    // armservoL.ChangePos(1023);
    // armservoR.ChangePos(0);
    
    bool connected = BTclient::init();
    bool btn2 = true;


    while (connected)
    {
       inputArr = BTclient::loop();
       for(int i = 0;i < 8;i++){
           std::cout << inputArr[i] << ", ";
       }    
       std::cout << '\n' << '\n' << std::endl;
 
    // std::cout << "pos1" << test.Read(36);
    //   std::cout << "pos2" << test2.Read(36);
    //    std::cout << "pos3" << armservoL.Read(36);
    //    std::cout << "pos4" <<  armservoR.Read(36);
       //test2.ChangePos(0);

    // check arm modus
    if(inputArr[6] == 1){
    arm1.takeinput(inputArr[0],inputArr[3]);
        if((bool)inputArr[7]){
            testservo.ChangePos(250);
        }
        else{
            testservo.ChangePos(500);
        }
    }
    //check drive modus
    if(inputArr[6]== 0){

    }
    //check tank modus
    if(inputArr[6]== 3){

    }
    //check line dance
    if(inputArr[6]== 2){

    }
    //check open CV modus
    if(inputArr[6]== 4)
    delay(200);
    
   
     
    // int pos = stuurservo.Read(36);
    // std::cout << "Starting Pos Stuur Servo "<< pos  << std::endl; 
    // std::cout << "Speed Pos Stuur Servo " << stuurservo.Read(38) << std::endl;    
    // std::cout << "Starting Pos Arm links: " << armservoL.Read(36) << std::endl;
    // std::cout << "Starting Pos Arm Rechts: " << armservoR.Read(36) << std::endl;
    //     delay(1000);
    //     arm1.takeinput(4000,4000);
    //     delay(500);

    //     armservoL.SyncWrite(2,1023,3,0);
    //     delay(5000);
        

    //     stuurservo.ChangePos(pos-100);
    //     delay(5000);
        
      



     
            
         
    }
    
}