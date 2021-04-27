#pragma once
#include <zmq.hpp>
#include "../service/zmq_helper.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CamSenderThread{
    public:
        CamSenderThread();
        void run(void *contextSub, zmq::socket_t *socketReq);
    private:
        bool stop_flag=false;
};