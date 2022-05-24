#include "Camera_Input.h"
#include <stdio.h>
#include <iostream>
//#include <unistd.h>
#include <cstring>
#include <sys/stat.h> 
#include <fcntl.h>
#include <fstream>
#include <chrono>  

using namespace std;

class Camera_Input
{
private:
    static Camera_Input *instance;
    int xPos;
    Camera_Input();
    ~Camera_Input();
    int file_desc;
    char *buffer;
    char *myfifo_read = "tmp/cam.in";
  

public:

    static Camera_Input *GetInstance(){
        if(!instance){
            instance = new Camera_Input;
        }
            return instance;   
    }

    void Init(){
        mkfifo(myfifo_read, 0666);
        file_desc = open(myfifo_read, O_RDONLY);
    }

    int GetPos(){
        return xPos;
    }

    void SetPos(int pos){

    }

    void ReadFile(){

       
    
    int nrOfBytesToRead = readLengthIndicatorFromPipe(file_desc);

    read(file_desc, buffer, nrOfBytesToRead);

    buffer[nrOfBytesToRead] = '\0';

    cout << nrOfBytesToRead;

    }

};




Camera_Input::Camera_Input()
{
    xPos = 250;

}

Camera_Input::~Camera_Input()
{
}
