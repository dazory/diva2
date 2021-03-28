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

#include "utils/Linux_keyboard.h"
#include "utils/Timestamp.h"
#include "utils/Strtok_m.h"
#include "utils/Can_serial.h"
#include "utils/Speed_spec.h"
#include "mscl/mscl.h"

using namespace std;

class ImuSensing{
   public:
        ImuSensing();
        mscl::InertialNode initialize(const char *devicename);
        int getBaudrate(const char *baudrate);
        float gyrox, gyroy, gyroz, magx, magy, magz, accelx, accely, accelz;
   private:


};

