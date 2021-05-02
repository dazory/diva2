#pragma once
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
#include <zmq.hpp>

#include <google/protobuf/util/time_util.h>
#include <google/protobuf/text_format.h>
#include "../protobuf/sensors.pb.h"
#include "../service/Linux_keyboard.h"
#include "../service/Timestamp.h"
#include "../service/Strtok_m.h"
#include "../service/Can_serial.h"
#include "../service/Speed_spec.h"

using namespace google::protobuf::util;
using namespace std;

class GpsSensing{
   public:
      GpsSensing();
      int initialize(string devicename); //const char *
      int getBaudrate(const char *baudrate);
      //void proto_gpsReader(sensors::Gps &gps, char *cBuff);
      sensors::Gps  proto_gpsReader(char *cBuff);
      void proto_gpsDisplay(sensors::Gps &gps);  

};

