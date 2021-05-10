#pragma once
#include <iostream>
#include <thread>
#include <zmq.hpp>

#include "../../service/global_name.hpp"
#include "GpsSensingThread.h"
#include "LiDARSensingThread.h"

using namespace std;

// [Global Variables]
// 1 = REAL, 2 = Test, 0 = Not used
int USE_GPS =0; int USE_IMU =0; int USE_CAM =0; int USE_LiDAR =0; int USE_CAN =0; 

int main(int argc, char *argv[]){
    // sudo chmod 777 /dev/ttyACM0
    
    // [Sensing Process]
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    // zmq::socket_t socket_LiDAR(context, ZMQ_PUB);
    socket.bind(protocol::SENSING_PUB);
    // socket_LiDAR.bind(protocol::SENSING_PUB); //address already in use -> 서로 다른 주소 사용해야함
    printf("[MobilePlatform/Sensing] binding\n");

    // USE_GPS = 0;
    // GpsSensingThread mGpsSensingThread;
    // std::thread sensingthread_gps(mGpsSensingThread.run, &socket); // , "/dev/ttyACM0", "9600"
    
    // USE_CAM = 1;
    // CamSensingThread camSensingThread;
    // std::thread sensingthread_cam(camSensingThread.run, &socket); // , "/dev/ttyACM0", "9600"
    
    // USE_CAN = 2;
    // CanSensingThread canSensingThread;
    // std::thread sensingthread_can(canSensingThread.run, &socket); // , "/dev/ttyACM0", "9600"
  
    USE_LiDAR = 1;
    LiDAR_SensingThread mLiDARSensingThread;
    thread sensingthread_LiDAR(mLiDARSensingThread.run, &socket);

    // sensingthread_can.join();
    //sensingthread_gps.join();
    sensingthread_LiDAR.join();
    // sensingthread_cam.join();

}