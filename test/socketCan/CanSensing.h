#pragma once
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>
// #include "../service/Can_packet.h"

using namespace std;

class CanSensing{
   public:
      CanSensing();
      int initialize(string devicename); // vcan0
      // int getBaudrate(const char *baudrate);
      // CanPacket getCanPacket();
   private:
      // CanPacket mCanPacket;


};

