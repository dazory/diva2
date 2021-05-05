#pragma once
#include "../service/global_name.hpp"
#include "GpsReceiverThread.h"
#include "CamReceiverThread.h"
#include <zmq.hpp>
#include <thread> 
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    
    // REP
    zmq::context_t contextRep(1);
    // zmq::socket_t socketRep(contextRep, ZMQ_REP);
    // socketRep.connect(protocol::RECEIVER_FROMMOBILE_REP_TEST);
    // printf("rep socket connected (in main)\n");

    // GPS
    // GpsReceiverThread mGpsReceiverThread;
    // thread gpsReceiverThread(&GpsReceiverThread::run, &mGpsReceiverThread, &contextRep);
    
    // CAM
    CamReceiverThread mCamReceiverThread;
    thread camReceiverThread(&CamReceiverThread::run, &mCamReceiverThread, &contextRep);

    camReceiverThread.join();
    // gpsReceiverThread.join();

}