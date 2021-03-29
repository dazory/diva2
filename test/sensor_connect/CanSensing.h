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

#include "service/Linux_keyboard.h"
#include "service/Timestamp.h"
#include "service/Strtok_m.h"
#include "service/Can_serial.h"
#include "service/Speed_spec.h"

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

using namespace std;

class CanSensing{
   public:
      CanSensing();
      int getSocket(const char *devicename); // devname = "can0" (or dev1, vcan0 etc.)
   private:


};

