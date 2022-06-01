
#include "ServoClass.h"
#include <iostream>
#include <termios.h>
#include <math.h>
#include <unistd.h>
#include <fstream>

#define HEADER 0xFF

int fs = 0;

Servo::Servo(int servonumber){
  id = servonumber;
}

void Servo::InitPins(){
  wiringPiSetupGpio();
  pinMode(17,OUTPUT);
}

void Servo::CreateConnection(){
  fs = serialOpen("/dev/ttyAMA0",1000000);
}



int Servo::CalculateChecksum(int id, int length,int inst, int param1 = 0, int param2 = 0,int param3 = 0){
  int temp = id + length + inst + param1 + param2 + param3;
  int temp2 = temp &  0xFF;

  return 255 -temp2;

}
int Servo::Read(int address)
{
    int ID      =  Servo::id;
    int length  =  0x04;
    int inst    =  0x02;
    int addr    =  address;
    int parm1   =  0x02;
    int chksum;
    chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1);
    int instruction[] = {HEADER,HEADER,ID,length,inst,addr,parm1,chksum};
    size_t count = sizeof(instruction)/4;
    Servo::SendPacket(instruction, count);
    int result = Servo::HandleError();
    return result;
}

void Servo::Reboot(){
    int ID      =  Servo::id;
    int length  =  0x02;
    int inst    =  0x08;
    
    int chksum;
 
    chksum  = Servo::CalculateChecksum(ID,length,inst);
    int instruction[] = {HEADER,HEADER,ID,length,inst,chksum};
    size_t count = sizeof(instruction)/4;

    Servo::SendPacket(instruction, count);
    Servo::HandleError();

}


void Servo::SyncWrite()
{
 
  
}

int Servo::HandleError()
{
  delay(100);
  int count = serialDataAvail(fs);

  

  char a;
  serialGetchar(fs);
  serialGetchar(fs);
  serialGetchar(fs);
  serialGetchar(fs);
  a = serialGetchar(fs);
  if(a & 1){
    std::cout << "Input voltage Error" << '\n';
  }
   if(a >> 1 & 1){
    std::cout << "Angle limit Error" << '\n';
  }
   if(a >> 2 & 1){
    std::cout << "Overheating Error" << '\n';
  }
   if(a >> 3 & 1){
    std::cout << "Range Error" << '\n';
  }
   if(a >> 4 & 1){
    std::cout << "Checksum Error" << '\n';
  }
   if(a >> 5 & 1){
    std::cout << "Overload Error" << '\n';
  }
   if(a >> 6 & 1){
    std::cout << "Instruction Error" << '\n';
  }
  if(count == 8){
    std::cout << "test";
    int a = (int) serialGetchar(fs);
    int b = (int) serialGetchar(fs);
    serialFlush(fs);
    return a + (b * 255);
  }
  serialFlush(fs);
  return 0;
}

void Servo::ChangePos(int pos)
{
    int ID      =  Servo::id;
    int length  =  (int)0x05;
    int inst    =  (int)0x03;
    int addr    =  (int)0x1E;
    int parm1 =  (int)(pos & 0xff);
    int parm2 = (int)(pos >> 8);
    int chksum;
 
    chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1,parm2);
    int instruction[] = {HEADER,HEADER,ID,length,inst,addr,parm1,parm2,chksum};
    size_t count = sizeof(instruction)/4;

    Servo::SendPacket(instruction, count);
    Servo::HandleError();
   
       
}

void Servo::SendPacket(int instruction[], int count){
    digitalWrite(17,HIGH);  
    for(int i =0; i < count; ++i)
    {
      serialPutchar(fs,instruction[i]);
    }
      
    delayMicroseconds(400);
    digitalWrite(17,LOW);
    delayMicroseconds(900);
     
    
}

Servo::~Servo(){

}

