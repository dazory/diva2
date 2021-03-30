#pragma once
#include <zmq.hpp>

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
#include "mscl/mscl.h"
#include <fstream>
using namespace std;

class ImuParsingThread{
    public:
        ImuParsingThread();
        void run(void*);
        void stop();
    private:
        bool stop_flag=false;
        float accel_x=0.1;
        float accel_y=0.1;
        float accel_z=0.1;
};