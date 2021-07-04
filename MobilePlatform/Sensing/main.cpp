#pragma once
#include <iostream>
#include <thread>
#include <zmq.hpp>

#include "../../service/global_name.hpp"
#include "GpsSensingThread.h"
#include "CamSensingThread.h"
#include "ImuSensingThread.h"
#include "CanSensingThread.h"
#include "LiDAR_SensingThread.h"

#include <mutex>

using namespace std;

// [Global Variables]
// 1 = REAL, 2 = Test, 0 = Not used
int USE_GPS = 0;
int USE_IMU = 0;
int USE_CAM = 0;
int USE_LiDAR = 0;
int USE_CAN = 0;


int main(int argc, char *argv[])
{
    ///[USB 포트연결] : (IMU, GPS, CAN, CAM)
    //sudo chmod 777 /dev/ttyACM0

    time_t system_time;
    struct tm* systime;
    system_time = time(NULL);
    systime = localtime(&system_time);

    string tm_year = to_string(systime->tm_year + 1900);
    string tm_month = to_string(systime->tm_mon+1);
    string tm_date = to_string(systime->tm_mday);
    if(tm_date.size() == 1){
        tm_date = "0"+tm_date;
    }

    string timestamp;
    timestamp = tm_year + tm_month + tm_date;


    string command = "mkdir -p /home/diva2/DIVA2_DATA/"+timestamp+"_0/CAM/JPG"+ " /home/diva2/DIVA2_DATA/"+timestamp+"_0/LiDAR/PCD" + " /home/diva2/DIVA2_DATA/"+timestamp+"_0/GPS" + " /home/diva2/DIVA2_DATA/"+timestamp+"_0/IMU" + " /home/diva2/DIVA2_DATA/"+timestamp+"_0/CAN";
    const char *c = command.c_str();
    system(c);
    cout<<"makedirectory"<<endl;

    // string command2 = "mkdir -p /home/diva2/DIVAdata/"+timestamp+"_0/CAM/JPG";
    // const char *c2 = command2.c_str();
    // system(c2);	

    // string command3 = "mkdir -p /home/diva2/DIVAdata/"+timestamp+"_0/LiDAR/PCD";
    // const char *c3 = command3.c_str();
    // system(c3);	

    mutex m;

    //(bef)
    // [Sensing Process]
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    socket.bind(protocol::SENSING_PUB);

    USE_GPS = 1;
    GpsSensingThread mGpsSensingThread;
    std::thread sensingthread_gps(mGpsSensingThread.run, &socket, "/dev/ttyACM0", ref(m)); 

    USE_CAM = 1;
    CamSensingThread camSensingThread;
    std::thread sensingthread_cam(camSensingThread.run, &socket, ref(m), timestamp); 

    USE_IMU = 1;
    ImuSensingThread imuSensingThread;
    std::thread sensingthread_imu(imuSensingThread.run, &socket, "/dev/ttyACM1", 115200, ref(m));

    USE_CAN = 1;
    CanSensingThread canSensingThread;
    std::thread sensingthread_can(canSensingThread.run, &socket, ref(m)); 

    USE_LiDAR = 1;
    LiDAR_SensingThread mLiDARSensingThread;
    thread sensingthread_LiDAR(mLiDARSensingThread.run, &socket, ref(m), 0.1f);

    sensingthread_can.join();
    sensingthread_gps.join();
    sensingthread_cam.join();
    sensingthread_imu.join();
    sensingthread_LiDAR.join();
}
