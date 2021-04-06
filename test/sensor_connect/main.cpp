#pragma once
#include <iostream>
#include <thread>
#include "GpsSensing.h"
#include "GpsSensingThread.h"
#include "ImuSensing.h"
#include "ImuSensingThread.h"
#include "CanSensing.h"
#include "CanSensingThread.h"
#include "CamSensing.h"
#include "CamSensingThread.h"
#include "../service/global_name.hpp"

using namespace std;
// 1 = REAL, 2 = Test, 0 = Not used
int USE_GPS =0; int USE_IMU =0; int USE_CAM =0; int USE_LIDAR =0; int USE_CAN =0;
map<string, tuple<string, int>> SensorInfoMap;

int main(int argc, char *argv[])
{

    // sudo chmod 777 /dev/ttyACM1
    /* Sensing Process */
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    socket.bind("tcp://127.0.0.1:5564");
    
    USE_GPS = 2;
    GpsSensingThread gpsSensingThread;
    std::thread sensingthread_gps(gpsSensingThread.run, &socket); // , "/dev/ttyACM0", "9600"
    
    USE_CAM=0;
    // CamSensingThread camSensingThread;
    // thread sensingthread_cam(camSensingThread.run, 0, &context, &socket);

    // USE_IMU=1;
    // ImuSensingThread imuSensingThread;
    // std::thread sensingthread_imu(imuSensingThread.run, "/dev/ttyACM0", 115200, &socket);


    // CanSensingThread canSensingThread;
    // thread sensingthread_can(canSensingThread.run, "can0", context);

    // sensingthread_cam.join();
    sensingthread_gps.join();
    // sensingthread_imu.join();
    // sensingthread_can.join();
}