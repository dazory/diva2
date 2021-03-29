#include <iostream>
#include <thread>
#include "GpsSensing.h"
#include "GpsSensingThread.h"
#include "ImuSensing.h"
#include "ImuSensingThread.h"
#include "CanSensing.h"
#include "CanSensingThread.h"

using namespace std;

int main(int argc, char *argv[]){

    void *context = zmq_ctx_new();
    
    // GpsSensingThread gpsSensingThread;
    // std::thread sensingthread_gps(gpsSensingThread.run, "/dev/ttyACM0", "9600", context);

    //ImuSensingThread imuSensingThread;
    //std::thread sensingthread_imu(imuSensingThread.run, "/dev/ttyACM1", 115200, context);

    CanSensingThread canSensingThread;
    thread sensingthread_can(canSensingThread.run, "can0", context);

    //sensingthread_gps.join();
    //sensingthread_imu.join();
    sensingthread_can.join();
}