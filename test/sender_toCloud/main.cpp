#pragma once
#include "GpsSenderThread.h"
#include "ImuSenderThread.h"
#include "../service/global_name.hpp"
#include <thread> 

using namespace std;

int USE_GPS =0; int USE_IMU =0; int USE_CAM =0; int USE_LIDAR =0; int USE_CAN =0;

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
    // GpsSenderThread mGpsSenderThread;
    // thread gpsSenderThread(&GpsSenderThread::run, &mGpsSenderThread, &contextSub, &socketReq);
    // gpsSenderThread.join();

    /*IMU*/
    USE_IMU = 1;
    ImuSenderThread mImuSenderThread;
    thread imuSenderThread(&ImuSenderThread::run, &mImuSenderThread, &contextSub, &socketReq);
    imuSenderThread.join();

}