#pragma once
#include "wiringPi.h"
#include "wiringSerial.h"
 

class Servo{
    public:
        int id = 0;
        
        static void CreateConnection();
        int CalculateChecksum(int id, int length,int inst, int param1, int param2,int param3);
        void ChangePos(int pos);
        static void InitPins();
        Servo(int servonumber);
        ~Servo();
    
};
