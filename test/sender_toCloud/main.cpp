#pragma once
#include "GpsSenderThread.h"
#include "../service/global_name.hpp"
#include <thread>

using namespace std;

int main(int argc, char *argv[]){
    
    // PUB
    zmq::context_t contextPub(1);
    zmq::socket_t socketPub(contextPub, ZMQ_PUB);
    socketPub.bind(protocol::SENDER_TOCLOUD_PUB);
    printf("pub socket connected (in main)\n");

    // SUB
    zmq::context_t contextSub(1);
    printf("sub context generated (in main)\n");

    

    // GPS
    GpsSenderThread mGpsSenderThread;
    thread gpsSenderThread(&GpsSenderThread::run, &mGpsSenderThread, &contextSub, &socketPub);
    gpsSenderThread.join();


}