#pragma once
#include <zmq.hpp>
#include "../service/zmq_helper.h"
#include <iostream>
#include <fstream>

using namespace std;

class ImuSenderThread{
    public:
        ImuSenderThread();
        void run(void *contextSub, zmq::socket_t *socketReq);
        void stop();
    private:
        bool stop_flag=false;
};