#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include "json_struct.h"
#include <fstream>
#include <chrono>

class telemetrics {
private:
    static telemetrics* instance;
    telemetrics();
public:
    struct _telemetry {
        int dc;
        int pf1, pf2, pf3, pf4;
        int pb1, pb2, pb3, pb4;

        JS_OBJ(dc, pf1, pf2, pf3, pf4, pb1, pb2, pb3, pb4);
    } telemetry;
    int xPos = -1;
    static telemetrics* getInstance();
};
