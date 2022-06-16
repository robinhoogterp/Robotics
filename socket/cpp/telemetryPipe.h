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
#include <signal.h>
#include <poll.h>
#include <chrono>

class telemetryPipe {
public:
    char *myfifo_write = "/home/greppel/greppel_out";
    char *myfifo_read  = "/home/greppel/greppel_in";

    int fd_write = open(myfifo_write, O_WRONLY);
    int fd_read  = open(myfifo_read, O_RDONLY);
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
