#pragma once
#include "wiringPi.h"
#include "wiringSerial.h"
 

class Servo{
    public:
        int id = 0;
        
        static void CreateConnection();
        int CalculateChecksum(int id, int length,int inst, int param1, int param2,int param3);
        void ChangePos(int pos);
        int HandleError();
        void Reboot();
        void SyncWrite();
        void SendPacket(int instruction[], int count);
        int Read(int adress);
        static void InitPins();
        Servo(int servonumber);
        ~Servo();
    
};
