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
#include "../service/gps_packet.h"

using namespace std;

class GpsSensing{
   public:
      GpsSensing();
      int initialize(string devicename); //const char *
      int getBaudrate(const char *baudrate);
      GpsPacket getGpsPacket();
   private:
      GpsPacket mGpsPacket;


};

