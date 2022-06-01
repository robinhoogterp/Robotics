
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

void Servo::ChangePos(int pos)
{
    std::cout << (char) 0;
    char header  =  (char)0xFF;
    char ID      =  Servo::id;
    char length  =  (char)0x05;
    char inst    =  (char)0x03;
    char addr    =  (char)0x1E;
    // char parm1; 
    // char parm2;  
    char parm1 =  (char)(pos & 0xff);
    char parm2 = (char)(pos >> 8);
    int chksum;
    // if(pos == 0) {
    //    parm1   =  (char)100;
    //    parm2   =  (char)0x00;
      
    // }
    // else{
    //   parm1   =  (char)200;
    //   parm2   =  (char)0x00;
    // }
 
 
    chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1,parm2);
      char instruction[] = {header,header,ID,length,inst,addr,parm1,parm2,chksum};
       digitalWrite(17,HIGH);
       for(int i =0; i < 9; ++i)
       {
         serialPutchar(fs,instruction[i]);
       }
     //serialPuts(fs, instruction);
      delayMicroseconds(500);
     digitalWrite(17,LOW);
      delayMicroseconds(500);
  
     std::cout<<std::hex<<header<<"  "<<header<<"  "<<ID<<"  "<<length<<"  "<<inst<<"  "<<addr<<"  "<<parm1<<"  "<<parm2<<"  "<<chksum<<'\n';
     //std::ofstream out("output.txt");
     //out <<header<<"  "<<header<<"  "<<ID<<"  "<<length<<"  "<<inst<<"  "<<addr<<"  "<<parm1<<"  "<<parm2<<"  "<<chksum<<'\n';
     //out.close();
     //delay(5000);
    //std::cout<<std::hex<<parm2<<'\n';
    // std::cout<<"ERROR Message" <<'\n';
    // std::cout<< std::hex << serialGetchar(fs)<<"Header1"<<'\n';
    // std::cout<< std::hex << serialGetchar(fs)<<"Header2"<<'\n';
    // std::cout<< std::hex << serialGetchar(fs)<<"PacketID"<<'\n';
    // std::cout<< std::hex << serialGetchar(fs)<<"Length"<<'\n';
    // std::cout<< std::hex << serialGetchar(fs)<<"Error"<<'\n';
    // std::cout<< std::hex << serialGetchar(fs)<<"Checksum"<<'\n';
    // std::cout<<"New Message" <<'\n';
    
}

Servo::~Servo(){

}

