#pragma once
#include "GpsSenderThread.h"
#include "../service/global_name.hpp"
#include <thread> 

using namespace std;

int main(int argc, char *argv[]){
    
    // REQ
    zmq::context_t contextReq(1); 
    zmq::socket_t socketReq(contextReq, ZMQ_REQ);
    socketReq.connect(protocol::SENDER_TOCLOUD_REQ);//SENDER_TOCLOUD_REQ_TEST
    printf("req socket connected (in main)\n");

    // SUB
    zmq::context_t contextSub(1);
    printf("sub context generated (in main)\n");

    // GPS
    GpsSenderThread mGpsSenderThread;
    thread gpsSenderThread(&GpsSenderThread::run, &mGpsSenderThread, &contextSub, &socketReq);
    gpsSenderThread.join();


}