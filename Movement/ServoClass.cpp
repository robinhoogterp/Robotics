
#include "ServoClass.h"
#include <iostream>
#include <termios.h>
#include <math.h>
#include <unistd.h>
#include <fstream>

const int HEADER = 0xFF;
const int PIN = 17;
const int DELAY = 100;
const int BROADCAST = 0xFE;
 
int fs = 0;


// Constructor creates servo with id as parameter
Servo::Servo(int servonumber){
  id = servonumber;
}

// 
void Servo::InitPins(){
  wiringPiSetupGpio();
  pinMode(PIN,OUTPUT);
}

// Creates connection to serialport ttyAMA0 with 100000 Baudrate
void Servo::CreateConnection(){
  fs = serialOpen("/dev/ttyAMA0",1000000);
}


// Calculates all the parameters and adds them up, after bitwise to be no larger then 0xFF (255)
int Servo::CalculateChecksum(int id, int length,int inst, int param1 = 0, int param2 = 0,int param3 = 0){
  int temp = id + length + inst + param1 + param2 + param3;
  int temp2 = temp &  0xFF;

  return 0xFF -temp2;

}

int Servo::CalcChecksumArr(int arr[],int size){
  int total = 0;
  for(int x = 0;x < size; x++){
      total += arr[x];
  }
  int temp = total & 0xFF;
  return 0xFF - temp;

}

// Read packet to read out a specific value from the servo
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

// Sends reboot packet to the servo
void Servo::Reboot(){
  std::cout << "reboot in" << std::endl;
    int curPos = Servo::Read(36);

    //TODO misschien positie +1
    Servo::ChangePos(curPos);
    int val = 1023;
    int ID      =  Servo::id;
    int length  =  0x05;
    int inst    =  0x03;
    int addr    =  34;
    int parm1 =  (int)(val & 0xff);
    int parm2 = (int)(val >> 8);
    

    int chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1,parm2);
    int instruction[] = {HEADER,HEADER,ID,length,inst,addr,parm1,parm2,chksum};
    size_t count = sizeof(instruction)/4;
     
    Servo::SendPacket(instruction, count);

}


void Servo::SyncWrite(int motor1id,int position1, int motor2id, int position2)
{
 int ID = BROADCAST;
 int length = 0x0A;
 int inst = 0x83;
 int tableAddr = 0X1E;
 int lMotor1 = 0x02; 
 int Motor1parm1 =  (int)(position1 & 0xff);
 int Motor1parm2 = (int)(position1 >> 8);
 int lMotor2 = 0x04; 
 int Motor2parm1 =  (int)(position2 & 0xff);
 int Motor2parm2 = (int)(position2 >> 8);

 int parmArr[14] = {0,0,ID,length,inst,tableAddr,lMotor1,motor1id,Motor1parm1,Motor1parm2,motor2id,Motor2parm1,Motor2parm2,0};

 size_t arrSize = sizeof(parmArr)/4;

 parmArr[13] = Servo::CalcChecksumArr(parmArr, arrSize);
 parmArr[0] = HEADER;
 parmArr[1] = HEADER;

for(int x : parmArr){
  std::cout << "test: "<<x << ' ';
}
std::cout << std::endl;


    
 Servo::SendPacket(parmArr, arrSize);
      
 delay(DELAY);
    
 Servo::HandleError();


  
}


//Prints Error to the console and returns a message if read was called
int Servo::HandleError()
{
  delay(DELAY);
  int count = serialDataAvail(fs);
 
  char a;
  if(count == 0){
    std::cout << "No Data  " << std::endl;
    return 0;
  }
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
    std::cout << "Overload Error" << std::endl;
    
   // Servo::Reboot();
  }
   if(a >> 6 & 1){
    std::cout << "Instruction Error" << '\n';
  }



  if(count == 8){
    int a = (int) serialGetchar(fs);
    int b = (int) serialGetchar(fs);
    serialFlush(fs);
    return a + (b * 255);  
  }
  else if(count == 7){
    int a = (int) serialGetchar(fs);
    serialFlush(fs);
    return a;

  }

  
  serialFlush(fs);
  return 0;
}
// Send Packet to change CW to 0
void Servo::ChangeCW()
{
    int ID      =   Servo::id;
    int length  =  (int)0x05;
    int inst    =  (int)0x03;
    int addr    =  (int)0x06;
    int parm1 =  0;
    int parm2 = 0;
    int chksum;
 
    chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1,parm2);
    int instruction[] = {HEADER,HEADER,ID,length,inst,addr,parm1,parm2,chksum};
    size_t count = sizeof(instruction)/4;
    
    Servo::SendPacket(instruction, count);
      
    delay(DELAY);
    
}

// Send Packet to change CCW to 1023
void Servo::ChangeCCW()
{
    int ID      =   Servo::id;
    int length  =  (int)0x05;
    int inst    =  (int)0x03;
    int addr    =  (int)0x08;
    int parm1 =  0xFF;
    int parm2 = 0x03;
    int chksum;
 
    chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1,parm2);
    int instruction[] = {HEADER,HEADER,ID,length,inst,addr,parm1,parm2,chksum};
    size_t count = sizeof(instruction)/4;
    
    Servo::SendPacket(instruction, count);
      
    delay(DELAY);
    
}

// Sends a packet to change servo position to parameter pos
void Servo::ChangePos(int pos)
{
    int ID      =   Servo::id;
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
      
    delay(DELAY);
    
    Servo::HandleError();
}

// Sends packet to change movement speed of the servo
void Servo::ChangeMovSpd(int speed)
{
    int ID      =   Servo::id;
    int length  =  (int)0x05;
    int inst    =  (int)0x03;
    int addr    =  (int)0x20;
    int parm1 =  (int)(speed & 0xff);
    int parm2 = (int)(speed >> 8);
    int chksum;
 
    chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1,parm2);
    int instruction[] = {HEADER,HEADER,ID,length,inst,addr,parm1,parm2,chksum};
    size_t count = sizeof(instruction)/4;
    
    Servo::SendPacket(instruction, count);
      
    delay(DELAY);
    Servo::HandleError();
}

// Sends Packet to factory reset the servo
void Servo::FactoryReset(){
    int ID      =   Servo::id;
    int length  =  (int)0x02;
    int inst    =  (int)0x06;
    int chksum;
 
    chksum  = Servo::CalculateChecksum(ID,length,inst);
    int instruction[] = {HEADER,HEADER,ID,length,inst,chksum};
    size_t count = sizeof(instruction)/4;
    
    Servo::SendPacket(instruction, count);
      
    delay(DELAY);
    Servo::HandleError();   

}

// Sends packet to enable/disable the torque of the servo.
void Servo::EnableTorque(){
    int ID      =   Servo::id;
    int length  =  (int)0x04;
    int inst    =  (int)0x03;
    int addr    =  (int)24;
    int parm1 =  1;
 
    int chksum;

    chksum  = Servo::CalculateChecksum(ID,length,inst,addr,parm1);
    int instruction[] = {HEADER,HEADER,ID,length,inst,addr,parm1,chksum};
    size_t count = sizeof(instruction)/4;
     
    Servo::SendPacket(instruction, count);
      
    delay(DELAY);
    Servo::HandleError();   

}

// Function to send the packet to the servo via the PIN
void Servo::SendPacket(int instruction[], int count){
    digitalWrite(PIN,HIGH);  
    for(int i =0; i < count; ++i)
    {
      //std::cout << i << ": " << instruction[i]<< " ";
      serialPutchar(fs,instruction[i]);
    }
    //std::cout << std::endl;
      
    delayMicroseconds(400);
    digitalWrite(PIN,LOW);
    delayMicroseconds(900);
     
    
}

// Deconstructor
Servo::~Servo(){

}

