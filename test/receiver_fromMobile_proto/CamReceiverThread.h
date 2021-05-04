#pragma once
#include <zmq.hpp>
#include "../service/zmq_helper.h"
#include <iostream>
#include <fstream>

using namespace std;

class CamReceiverThread{
    public:
        CamReceiverThread();
        void run(void *contextRep);
        void stop();
    private:
        bool stop_flag=false;
};
