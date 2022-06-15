#pragma once
#include "telemetrics.h"

telemetrics* telemetrics::getInstance()
{
    if (instance == 0)
    {
        instance = new telemetrics();
    }

    return instance;
}
telemetrics::telemetrics(){

}
