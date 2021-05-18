#pragma once
// #include "mscl/mscl.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "../../service/zmq_helper.h"
#include "../../service/Can_serial.h"
#include "../../service/Linux_keyboard.h"
#include "../../protobuf/sensors.pb.h"

// JSON
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

using namespace std;

extern int USE_CAN;
const int HANDLE_ANGLE= 688;
const int TURN_LIGHT= 1345;
const int VEHICLE_SPEED= 790;
const int GEAR = 1322;

class CanSensingThread
{
public:
    CanSensingThread();
    static void run(zmq::socket_t *socket);
};