#include "start.h"
telemetrics* telemetrics::instance = 0;
int main() {
    std::cout << "in main" << std::endl;

    telemetrics* t = telemetrics::getInstance();
    randomValues rv;
    telemetryPipe tPipe;


    while(true) {
        rv.generate();
        tPipe.printDCS();
        tPipe.sendState();
//        sleep();
    }

    return 0;
}
