#pragma once
#include "GpsSenderThread.h"
#include "CamSenderThread.h"
#include "CanSenderThread.h"
#include "../service/global_name.hpp"
#include <thread> 
#include <string>

using namespace std;

int USE_GPS =0; int USE_IMU =0; int USE_CAM =0; int USE_LIDAR =0; int USE_CAN =0;

int main(int argc, char *argv[]){
    
    // REQ
    zmq::context_t contextReq(1); 
    zmq::socket_t socketReq(contextReq, ZMQ_REQ);
    socketReq.connect(protocol::SENDER_TOCLOUD_REQ_TEST);//SENDER_TOCLOUD_REQ_TEST
    printf("req socket connected (in main)\n");

    // SUB
    zmq::context_t contextSub(1);
    printf("sub context generated (in main)\n");

    // GPS
    // GpsSenderThread mGpsSenderThread;
    // thread gpsSenderThread(&GpsSenderThread::run, &mGpsSenderThread, &contextSub, &socketReq);
    
    // CAM
    // CamSenderThread mCamSenderThread;
    // thread camSenderThread(&CamSenderThread::run, &mCamSenderThread, &contextSub, &socketReq);
    
    // CAN
    CanSenderThread mCanSenderThread;
    thread canSenderThread(&CanSenderThread::run, &mCanSenderThread, &contextSub, &socketReq);
    
    // gpsSenderThread.join();
    // camSenderThread.join();
    canSenderThread.join();
    
}