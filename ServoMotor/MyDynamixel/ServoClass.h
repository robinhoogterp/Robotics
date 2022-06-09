#pragma once
#include "wiringPi.h"
#include "wiringSerial.h"
 

class Servo{

    public:

        int id = 0;
        
        static void CreateConnection();
        int CalculateChecksum(int id, int length,int inst, int param1, int param2,int param3);
        int CalcChecksumArr(int arr[],int size); 

        void ChangePos(int pos);
        int HandleError();

        void EnableTorque();
        void ChangeMovSpd(int speed);
        void FactoryReset();
        void Reboot();
        void SyncWrite(int motor1id,int position1, int motor2id, int position2);
        void SendPacket(int instruction[], int count);
        int Read(int adress);
        static void InitPins();
        Servo(int servonumber);
        ~Servo();
    
};
