#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include "json_struct.h"
#include <chrono>
#include "telemetryPipe.h"
#include "telemetrics.h"


class randomValues {
    int dc1;
    int dc2;
    int dc3;
    int dc4;


public:
    randomValues();
    void generate();
};

