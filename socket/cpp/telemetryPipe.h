#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include "json_struct.h"
#include "telemetrics.h"
#include <fstream>
#include <chrono>

class telemetryPipe {
public:
    char *myfifo_write = "/tmp/greppel_out";
    char *myfifo_read  = "/tmp/greppel_in";


    int fd_write;
    int fd_read;
    telemetryPipe();
    void sendState();
    void printDCS();
private:

    void createLengthIndicator(char *buffer, unsigned long int len);
    uint64_t getTimestamp();
    unsigned long int writeStringToPipe (int fd, const char* text);
    unsigned long int readLengthIndicatorFromPipe(int fd);
    int readStringFromPipe(char *buffer, int fd);
    unsigned long int writeFileToPipe(int fd, const char *path);
};

