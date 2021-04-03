#pragma once
#include <zmq.hpp>
#include "../service/zmq_helper.h"
#include <iostream>
#include <fstream>

using namespace std;

class GpsSenderThread{
    public:
        GpsSenderThread();
        void run(void *contextSub, zmq::socket_t *socketPub);
        void stop();
    private:
        bool stop_flag=false;
};