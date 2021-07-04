#pragma once
#include "mscl/mscl.h"

#include <iostream>
#include <sstream>
#include <time.h>
#include <sys/timeb.h>

#include "../../service/zmq_helper.h"
#include "../../service/Can_serial.h"
#include "../../service/Linux_keyboard.h"
#include "../../protobuf/sensors.pb.h"
#include "jsoncpp/json/json.h"
#include "mscl/mscl.h"
#include "../../service/Timestamp.h"

// JSON
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

using namespace std;

extern int USE_GPS;

class GpsSensingThread
{
public:
    GpsSensingThread();
    static void run(zmq::socket_t *socket, const char *devicename, mutex &m);
};
