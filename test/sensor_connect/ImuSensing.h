#pragma once
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

#include "../service/Linux_keyboard.h"
#include "../service/Timestamp.h"
#include "../service/Strtok_m.h"
#include "../service/Can_serial.h"
#include "../service/Speed_spec.h"
#include "mscl/mscl.h"

using namespace std;

class ImuSensing{
   public:
        ImuSensing();
        mscl::InertialNode getMsclNode(const char *devicename, mscl::uint32 baudrate);
        float gyrox, gyroy, gyroz, magx, magy, magz, accelx, accely, accelz;
   private:


};

