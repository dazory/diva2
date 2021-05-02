#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>


// #include <sstream>
// #include <time.h>
// #include "unistd.h"
// #include <sys/timeb.h>
// #include <cstddef>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "../protobuf/sensors.pb.h"
#include "../service/zmq_helper.h"

using namespace cv;
using namespace std;

extern int USE_CAN;

class CanSensingThread
{

public:
    CanSensingThread();
    static void run(zmq::socket_t *publisher); //const int devicename, zmq::context_t *context,
};
