#pragma once
#include <zmq.hpp>
#include "../../service/zmq_helper.h"
#include <iostream>
#include <fstream>
#include <string>
#include "unistd.h"

using namespace std;

class ImuVisualization{
    public:
        ImuVisualization();
        void run(void *contextSub);
    private:
        bool stop_flag=false;
};