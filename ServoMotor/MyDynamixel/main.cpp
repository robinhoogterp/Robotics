#include "main.h"

#include "BTclient.h"
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include "Movement/Movement.h"

telemetrics* telemetrics::instance = 0;
int main()
{

    telemetryPipe tPipe;
    int* inputArr;
    Servo::InitPins();
    Servo::CreateConnection();
    Servo grijper(1);
    Servo linkerknikpunt(2);
    Servo rechterknikpunt(3);
    Servo armservoL(4);
    Servo armservoR(5);
    Servo stuurservo(6);
    arm arm1;
    Movement mv;
    
    
    
     std::cout << "Pos1:  " <<linkerknikpunt.Read(36);
     std::cout << "Pos2:  " << rechterknikpunt.Read(36);

    bool connected = BTclient::init();
    bool btn2 = true;
    mv.setup();

    grijper.ChangeMovSpd(100);
    rechterknikpunt.ChangeMovSpd(100);
    linkerknikpunt.ChangeMovSpd(100);
    armservoR.ChangeMovSpd(100);
    armservoL.ChangeMovSpd(100);
    stuurservo.ChangeMovSpd(200);

    while (connected)
    {
        tPipe.sendState();
        std::cout << "TEST1" << std::endl;
       inputArr = BTclient::loop();
       std::cout << "TEST2" << std::endl;
       for(int i = 0;i < 8;i++){
           std::cout << inputArr[i] << ", ";
       }    
      
       std::cout << '\n' << '\n' << std::endl;
 
    // std::cout << "pos1" << test.Read(36);
    //   std::cout << "pos2" << test2.Read(36);
    //    std::cout << "pos3" << armservoL.Read(36);
    //    std::cout << "pos4" <<  armservoR.Read(36);
       //test2.ChangePos(0);

    // check modus
    switch (inputArr[6])
    {
    case 0: // Rijden 
    mv.receivedata(inputArr[0],inputArr[4],0);
    std::cout << "HELP" << std::endl;
    break;
    case 1: // Arm
    arm1.takeinput(inputArr[0],inputArr[3]);
    if((bool)inputArr[7])
    {
        grijper.ChangePos(250);
    }
    else
    {
        grijper.ChangePos(650);
    }
    break;
    case 2: // Linedance
    break;
    case 3: // Tank Besturing
    mv.receivedata(inputArr[0],inputArr[4],1);
    break;
    case 4: // OpenCV
    telemetrics* tm = telemetrics::getInstance();
    int x = (*tm).xPos;
    if (x == -1)
    { 
        }
        else if (x > 340)
        { mv.receivedata(2000,4000,0);
            }
            else if (x < 320)
        { mv.receivedata(2000,1000,0);
            }
    break;

    } 
    



     
            
         
    }
 
    
}
