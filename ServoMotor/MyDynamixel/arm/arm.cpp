#include "arm.h"
#include <iostream>
Servo Links(2);
Servo Rechts(3); 
Servo Links2(4);
Servo Rechts2(5);
const int MAX = 1020;
const int MIN = 0;
const int SCALER = 35;

arm::arm() {
   range = 4095;
   positions[0] = Links.Read(36);
   positions[1] = Rechts.Read(36);
   positions[2] = Links2.Read(36);
   positions[3] = Rechts2.Read(36);
   ptr = positions;
  

}
void arm::updateservo2de(int* ptr) {
   std::cout <<"P[2]" << ptr[2]<<" "<< "P[3]" << ptr[3] << std::endl;
   Links.SyncWrite(Links2.id, ptr[2], Rechts2.id, ptr[3]);
 
}
void arm::updateservo1ste(int* ptr) {
   std::cout <<"P[0]" << ptr[0]<<" "<< "P[1]" << ptr[1] << std::endl;
   Links.SyncWrite(Links.id, ptr[0], Rechts.id, ptr[1]);
 
}
void arm::updatearrayknikpunt1(int scaler1, int* ptr) {
    int links1 = ptr[0];
    int rechts1 = ptr[1];
    
    std::cout << "links: "<<links1<<"rechts: " << rechts1 << std::endl;
    if(links1 == 0 && rechts1 ==0){
       
    }
    else if ((links1 - scaler1) < MIN && scaler1 < 0 || (rechts1 + scaler1) < MIN && scaler1 < 0 )
    {
        std::cout << "if1" << std::endl;
        
    }
    else if ((links1 - scaler1) > MAX && scaler1 > 0|| (rechts1 + scaler1) > MAX && scaler1 > 0) 
    {
            std::cout << "if2" << std::endl;
        
    }
    else
    { 
        std::cout << "yeet" << std::endl;
        ptr[0] = ptr[0] - scaler1;
        ptr[1] = ptr[1] + scaler1;
     updateservo1ste(ptr);
    }
    

    
}
void arm::updatearrayknikpunt2(int scaler1, int* ptr) {
    int links1 = ptr[2];
    int rechts1 = ptr[3];
    
    std::cout << "links: "<<links1<<"rechts: " << rechts1 << std::endl;
    if(links1 == 0 && rechts1 ==0){
       
    }
    else if ((links1 - scaler1) < MIN && scaler1 < 0 || (rechts1 + scaler1) < MIN && scaler1 < 0 )
    {
        std::cout << "if1" << std::endl;
        
    }
    else if ((links1 - scaler1) > MAX && scaler1 > 0|| (rechts1 + scaler1) > MAX && scaler1 > 0) 
    {
            std::cout << "if2" << std::endl;
        
    }
    else
    { 
        std::cout << "yeet" << std::endl;
        ptr[2] = ptr[2] - scaler1;
        ptr[3] = ptr[3] + scaler1;
        updateservo2de(ptr);
    }
    
    
}
int* arm::getpositions() {
    return this->positions;
}

void arm::scaledposition(float x) {
    double percent = x / 4095;
    int servodata = MAX * percent;
    std::cout << servodata;
}
void arm::takeinput(int input, int input2) {
    for (int i = 0;sizeof(this->positions) / 4 > i; i++) {
        std::cout << this->positions[i]<< std::endl;
    }
    if(input > 1747 && input < 2347){
    
    }
    else if (this->range / 2 > input) {
    
        updatearrayknikpunt1(-SCALER,this->ptr);
       
    }
    else if (this->range / 2 < input ) {
     
        updatearrayknikpunt1(SCALER,this->ptr);
    }
 

    if(input2 > 1747 && input2 < 2347){

    }
    else if (this->range / 2 > input2) {
        
        updatearrayknikpunt2(-SCALER,this->ptr);
       

    }
    else if (this->range / 2 < input2) {
     
       
        updatearrayknikpunt2(SCALER,this->ptr);
    }
  
}

