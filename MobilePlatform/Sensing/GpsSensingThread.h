#pragma once
#include <iostream>
#include <sstream>
#include <time.h>
#include <sys/timeb.h>

#include "GpsSensingThread.h"
#include "../../service/zmq_helper.h"
#include "../../service/Can_serial.h"
#include "../../service/Linux_keyboard.h"
#include "../../protobuf/sensors.pb.h"

using namespace std;

extern int USE_GPS;
extern map<string, tuple<string, int>> SensorInfoMap;

class GpsSensingThread
{
public:
    GpsSensingThread();
    static void run(zmq::socket_t *socket);
};