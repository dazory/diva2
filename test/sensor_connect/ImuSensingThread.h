
//imu.cpp
#pragma once
#include <string>
#include <iostream>
#include "ImuSensing.cpp"

#include "mscl/mscl.h"
#include <fstream>
using namespace std;


inline static bool s_sendmore (void *context, const void *data) {

	zmq::socket_t socket(*(zmq::context_t*)context,ZMQ_REQ);
	socket.bind("tcp://*:5563");
    bool rc = socket.send(data, ZMQ_SNDMORE);

    return (rc);
}
inline static bool s_send (void *context, zmq::message_t &data, int flags = 0) {

	zmq::socket_t socket(*(zmq::context_t*)context,ZMQ_REQ);
	socket.bind("tcp://*:5563");
    bool rc = socket.send(data, flags);

    return (rc);
}

class ImuSensingThread{
	public:
	ImuSensingThread();
	static void run(const char *devicename, mscl::uint32 baudrate, void *context);
};

ImuSensingThread::ImuSensingThread(){

}

void ImuSensingThread::run(const char *devicename, mscl::uint32 baudrate, void *context){
	//printf("start (MSCL ver: %s)(in ImuSensingThread::run)\n",mscl::MSCL_VERSION.str());
    printf("start (MSCL)(in ImuSensingThread::run)\n");

    ImuSensing imuThread;
    mscl::InertialNode node = imuThread.getMsclNode(devicename,baudrate);
	printf("imu.getMsclNode (in ImuSensingThread::run)\n");

    while(1){
        mscl::MipDataPackets packets = node.getDataPackets(500);
        printf("getDataPackets (in ImuSensingThread::run/while(1))\n");
        
        s_sendmore (context, "IMU");
        printf("sendmore: \"IMU\" (in ImuSensingThread::run/while(1))\n");
        
        zmq::message_t msg(&packets, sizeof(mscl::MipDataPackets), NULL);
        s_send(context,msg);
		printf("send complete! (in GpsSensingThread::run/while(1))\n");

        sleep (1);
    }
}
