#include "main.h"

Camera_Input *cameraInput = 0;
Controller_Input *controllerInput = 0;

int main(){
    Init();
    Update();
}

void Init(){
    cameraInput = Camera_Input::GetInstance();
    cameraInput->Init();
}

void Update(){
    while (true)
    {
        cameraInput->ReadFile();
        cout << cameraInput->GetPos();
    }
}