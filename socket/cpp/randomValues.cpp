#include "randomValues.h"

randomValues::randomValues() {
    telemetrics* t = telemetrics::getInstance();
    dc1 = rand() % 101;
    dc2 = rand() % 101;
    dc3 = rand() % 101;
    dc4 = rand() % 101;


    (*t).telemetry.dc1 = dc1;
    (*t).telemetry.dc2 = dc2;
    (*t).telemetry.dc3 = dc3;
    (*t).telemetry.dc4 = dc4;
}

void randomValues::generate() {
    telemetrics* t = telemetrics::getInstance();
    dc1 = rand() % 101;
    dc2 = rand() % 101;
    dc3 = rand() % 101;
    dc4 = rand() % 101;


    (*t).telemetry.dc1 = dc1;
    (*t).telemetry.dc2 = dc2;
    (*t).telemetry.dc3 = dc3;
    (*t).telemetry.dc4 = dc4;
}
