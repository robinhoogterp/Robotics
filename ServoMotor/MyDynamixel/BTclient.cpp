#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <string>
#include <sstream>
#include <iostream>
#include "BTclient.h"

struct sockaddr_rc addr;
char buf[1024];
int s, status, bytes_read;
char dest[18] =  "30:C6:F7:0E:34:AA";
int filledarray[] = { 0,0,0,0,0,0,0,0};
int* ptr= filledarray;
int arrSize;


bool BTclient::init() {
    sockaddr_rc addr = { 0xB8,0x27,0xEB,0x15,0xF3,0xC2 };
    buf[1024];
    s, status, bytes_read;
    //array with recieved data
    
    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t)1;
    str2ba(dest, &addr.rc_bdaddr);

    // connect to server
    status = connect(s, (struct sockaddr*)&addr, sizeof(addr));

    memset(buf, 0, sizeof(buf));
    return true;
}

void BTclient::splitdata(char base[], int size, int* fill) {
    std::string sBase;

    int j = 0;
    for (int i = 0;size > i;i++) {
        std::stringstream ss;
        char sample = base[i];
        if (sample == ',') {
            *(fill + j) = std::stoi(sBase);
            j++;
            sBase.clear();
        }
        else if (sample == 'A') {
            *(fill + j) = std::stoi(sBase);
            sBase.clear();
            break;
        }
        else
        {
            sBase.push_back(sample);
        }

    }

}

int* BTclient::loop() {
      // send a message
   std::cout << "hallo" << std::endl;
    listen(s, 1);
   std::cout << "hallo2" << std::endl;
       bytes_read = read(s,buf, sizeof(buf));
       std::cout << "hallo3" << std::endl;
    if(bytes_read > 0){
        try{
            splitdata(buf,sizeof(buf),ptr);
            std::cout << "hallo4" << std::endl;
       
        }
        catch(...){
            std::cout<< "Help BUFFER" << '\n';
        }
 
        
    }   


   return ptr;
}








