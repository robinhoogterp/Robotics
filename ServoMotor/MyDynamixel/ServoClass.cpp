
#include "ServoClass.h"
#include <iostream>
#include <termios.h>
#include <math.h>
#include <unistd.h>
#include <fstream>



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



int Servo::CalculateChecksum(int id, int length,int inst, int param1, int param2,int param3 = 0){
  int temp = id + length + inst + param1 + param2 + param3;
  int temp2 = temp &  0xFF;
  std::cout <<(255-temp2)<<"checksum"<<'\n';
  return 255 -temp2;

}
/*void Servo::Read(int address){
    int header  =  0xFF;
    int ID      =  0x2B;
    int length  =  0x04;
    int inst    =  0x02;
    int addr    =  address;
    int parm1   =  0xFF;
    int parm2   =  0x00;
}
*/

void Servo::SyncWrite()
{
 
  
}

void Servo::HandleError()
{
  serialGetchar(fs);
  serialGetchar(fs);
  serialGetchar(fs);
  serialGetchar(fs);
  char a = serialGetchar(fs);
  if(a & 1){
    std::cout << "Input voltage Error";
  }
   if(a >> 1 & 1){
    std::cout << "Angle limit Error";
  }
   if(a >> 2 & 1){
    std::cout << "Overheating Error";
  }
   if(a >> 3 & 1){
    std::cout << "Range Error";
  }
   if(a >> 4 & 1){
    std::cout << "Cheksum Error";
  }
   if(a >> 5 & 1){
    std::cout << "Overload Error";
  }
   if(a >> 6 & 1){
    std::cout << "Instruction Error";
  }

}

void Servo::ChangePos(int pos)
{
    std::cout << (char) 0;
    char header  =  (char)0xFF;
    char ID      =  Servo::id;
    char length  =  (char)0x05;
    char inst    =  (char)0x03;
    char addr    =  (char)0x1E;
    char parm1 =  (char)(pos & 0xff);
    char parm2 = (char)(pos >> 8);
    int chksum;
 
 
    chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1,parm2);
      char instruction[] = {header,header,ID,length,inst,addr,parm1,parm2,chksum};
       digitalWrite(17,HIGH);
       for(int i =0; i < 9; ++i)
       {
         serialPutchar(fs,instruction[i]);
       }
      
      delayMicroseconds(500);
      digitalWrite(17,LOW);
      delayMicroseconds(500);
      Servo::HandleError();
    
     std::cout<<std::hex<<header<<"  "<<header<<"  "<<ID<<"  "<<length<<"  "<<inst<<"  "<<addr<<"  "<<parm1<<"  "<<parm2<<"  "<<chksum<<'\n';
    
}

Servo::~Servo(){

}

