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

using namespace std;

int main(int argc, char *argv[]){

    //void *context = zmq_ctx_new();

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    const char * protocol = "tcp://*:5563";
    socket.bind(protocol);
    
    GpsSensingThread gpsSensingThread;
    std::thread sensingthread_gps(gpsSensingThread.run, "/dev/ttyACM0", "9600", &socket);

    //CamSensingThread camSensingThread;
    //thread sensingthread_cam(camSensingThread.run, 0, &context, &socket);

   // ImuSensingThread imuSensingThread;
    //std::thread sensingthread_imu(imuSensingThread.run, "/dev/ttyACM1", 115200, &socket);

    // CanSensingThread canSensingThread;
    // thread sensingthread_can(canSensingThread.run, "can0", context);

    //sensingthread_cam.join();
    sensingthread_gps.join();
    //sensingthread_imu.join();
    // sensingthread_can.join();
}