#include "arm.h"
#include <iostream>

arm::arm() {
   range = 4095;
   positions[0] = 0;
   positions[1] = 1000;
   positions[2] = 0;
   positions[3] = 1000;
   ptr = positions;


}
void arm::updateservo(int* ptr) {
  //  servo::SyncWrite(0, *(ptr + 0), 0, *(ptr + 1));
   // servo::SyncWrite(0, *(ptr + 2), 0, *(ptr + 3));
}
void arm::updatearray(int scaler1, int scaler2, int* ptr) {
    if (*(ptr + 0) == 0 && scaler1 < 0 || *(ptr + 2) == 0 && scaler2 < 0) {
    }
    else if (*(ptr + 0) == 1000 && scaler1 < 0 || *(ptr + 2) == 1000 && scaler2 < 0) {

    }
    else
    { 
        *(ptr + 0) += scaler1;
        *(ptr + 1) -= scaler1;
        *(ptr + 2) += scaler2;
        *(ptr + 3) -= scaler2;
    }
    updateservo(ptr);
}
int* arm::getpositions() {
    return this->positions;
}

void arm::scaledposition(float x) {
    double percent = x / 4095;
    int servodata = 1000 * percent;
    std::cout << servodata;
}
void arm::takeinput(int input, int input2) {

    for (int i = 0;sizeof(this->positions) / 4 > i; i++) {
        std::cout << this->positions[i];
    }
    scaledposition((float)input);
    if (this->range / 2 > input && this->range / 2 > input2) {
        std::cout << "1 en 2 zijn kleiner\n";
        updatearray(-10, -10, this->ptr);
        std::cout << "methode klaar\n";

    }
    else if (this->range / 2 > input && this->range / 2 < input2) {
        std::cout << "1 is kleiner 2 is groter\n";
        updatearray(-10, 10, this->ptr);

    }
    else if (this->range / 2 < input && this->range / 2 < input2) {
        std::cout << "1 en 2 is groter\n";
        updatearray(10, 10, this->ptr);
    }
    else {
        std::cout << "1 is groter en 2 is kleiner\n";
        updatearray(10, -10, this->ptr);
    }
}

