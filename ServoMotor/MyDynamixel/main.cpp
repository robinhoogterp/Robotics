#include "main.h"

#include "BTclient.h"
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include "Movement/Movement.h"
#include "gewichtsensor/gewichtsensor.h"

telemetrics* telemetrics::instance = 0;
float gewicht;
int main()
{
    int prevpos = 330;
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
    gewichtsensor sensor;
    Movement mv;
    bool first = true;
    
     std::cout << "Pos1:  " <<linkerknikpunt.Read(36) << std::endl;
     std::cout << "Pos2:  " << rechterknikpunt.Read(36) << std::endl;

    bool connected = BTclient::init();
    bool btn2 = true;
    mv.setup();

    grijper.ChangeMovSpd(300);
    rechterknikpunt.ChangeMovSpd(80);
    linkerknikpunt.ChangeMovSpd(80);
    armservoR.ChangeMovSpd(50);
    armservoL.ChangeMovSpd(50);
    stuurservo.ChangeMovSpd(150);

    while (connected)
    {
        tPipe.sendState();
        inputArr = BTclient::loop();
        for(int i = 0;i < 8;i++){
        std::cout << inputArr[i] << ", ";
       }    
      
       std::cout << '\n' << '\n' << std::endl;

    // check modus
    switch (inputArr[6])
    {
    case 0: // Rijden 
    first = true;
    mv.receivedata(inputArr[0],inputArr[4],0);
  
    
    break;
    case 1: // Arm
    if(first){
        std::cout << "Grijper Pos: " << grijper.Read(36) << std::endl;
        std::cout << "LinkerKnik Pos: " << linkerknikpunt.Read(36) << std::endl;
        std::cout << "RechterKnik Pos: " << rechterknikpunt.Read(36) << std::endl;
        std::cout << "ArmLinks Pos: " << armservoL.Read(36) << std::endl;
        std::cout << "ArmRechts Pos: " << armservoR.Read(36) << std::endl;
        std::cout << "StuurServo Pos: " << stuurservo.Read(36) << std::endl;
        first = false;
    }

    arm1.takeinput(inputArr[0],inputArr[3]);
    if((bool)inputArr[7])
    {
        grijper.ChangePos(300);
    }
    else
    {
        grijper.ChangePos(650);
    }
    break;
    case 2: // Linedance
        first = true;
        gewicht = sensor.sample();
        std::cout << gewicht << std::endl;
        std::cout << "Eind Gewicht" << std::endl;
        
    break;
    case 3: // Tank Besturing
        first = true;
        mv.receivedata(inputArr[0],inputArr[4],1);
      
    break;
    case 4: // OpenCV
    first = true;
    telemetrics* tm = telemetrics::getInstance();
    int x = (*tm).xPos;
    if (x == -1)
    { 
        }
        else if (prevpos < x)
        { mv.receivedata(2000,4000,0);
            prevpos = x;
            }
            else if (prevpos > x)
            
        { mv.receivedata(2000,1000,0);
              prevpos = x;
            }
        
    break;

    } 
    



     
            
         
    }
 
    
}
