// #pragma once
// #include <iostream>
// #include <thread>
// #include "CanSensing.h"
// #include "CanSensingThread.h"
// #include "../service/global_name.hpp"

// using namespace std;
// // 1 = REAL, 2 = Test, 0 = Not used
// int USE_GPS =0; int USE_IMU =0; int USE_CAM =0; int USE_LIDAR =0; int USE_CAN =0;

// int main(int argc, char *argv[])
// {

//     // sudo chmod 777 /dev/ttyACM1
//     /* Sensing Process */
//     zmq::context_t context(1);
//     zmq::socket_t socket(context, ZMQ_PUB);
//     socket.bind("tcp://127.0.0.1:5564");
    
//     USE_CAN = 1;
//     CanSensingThread canSensingThread;
//     std::thread sensingthread_can(canSensingThread.run, &socket); 
//     sensingthread_can.join();
// }