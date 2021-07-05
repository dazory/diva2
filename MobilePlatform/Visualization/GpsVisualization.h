#pragma once
#include <zmq.hpp>
#include "../../../service/zmq_helper.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "unistd.h"

using namespace std;

class GpsVisualization{
    public:
        GpsVisualization();
        void run(void *contextSub);
    private:
        bool stop_flag=false;
};