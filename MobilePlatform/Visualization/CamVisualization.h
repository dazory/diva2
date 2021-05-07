#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <zmq.hpp>

#include "../../service/zmq_helper.h"

using namespace std;

class CamVisualization{
    public:
        CamVisualization();
        void run(void *contextSub);
    private:
        bool stop_flag=false;
};