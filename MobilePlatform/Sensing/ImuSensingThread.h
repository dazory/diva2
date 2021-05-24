#pragma once
#include "GpsSensingThread.h"
// #include "ImuSensing.cpp"
// #include "ImuSensing.h"

#include <string>
#include <iostream>
//#include <czmq.h>
#include <zmq.hpp>
#include <fstream>
#include <random>

#include "../../service/zmq_helper.h"
// #include "../../service/ImuPacket.h"

// JSON
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

using namespace std;

extern int USE_IMU;

class ImuSensingThread
{
public:
    ImuSensingThread();
    static void run(zmq::socket_t *socket, const char *devicename, mscl::uint32 baudrate, mutex &m);
};
