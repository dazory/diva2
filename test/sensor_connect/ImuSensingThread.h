// test/sensor_connect/ImuSensingThread.h
#pragma once
#include <string>
#include <iostream>
#include "ImuSensing.cpp"

#include "../service/zmq_helper.h"

#include "mscl/mscl.h"
#include <czmq.h>
#include <fstream>
using namespace std;

#define CHUNK_SIZE  250000

class ImuSensingThread{
	public:
	ImuSensingThread();
	static void run(const char *devicename, mscl::uint32 baudrate, zmq::socket_t *socket);
};

ImuSensingThread::ImuSensingThread(){

}

void ImuSensingThread::run(const char *devicename, mscl::uint32 baudrate, zmq::socket_t *socket){
	printf("start (MSCL ver: %s)(in ImuSensingThread::run)\n",mscl::MSCL_VERSION.str());
    //printf("start (MSCL)(in ImuSensingThread::run)\n");

    ImuSensing imuThread;
    mscl::InertialNode msclNode = imuThread.getMsclNode(devicename,baudrate);
	printf("imu.getMsclNode (in ImuSensingThread::run)\n");

    while(1){
        mscl::MipDataPackets msclPackets = msclNode.getDataPackets(500);
        printf("getDataPackets (in ImuSensingThread::run/while(1))\n");
              

        // for(mscl::MipDataPacket msclPacket : msclPackets){
        //     int count = 0;
        //     msclPacket.descriptorSet();
        //     mscl::MipDataPoints msclPoints = msclPacket.data();

        //     for(mscl::MipDataPoint msclPoint : msclPoints){
        //         size_t size = sizeof(msclPoint) + 1;
        //         zmq::message_t zmqData(size);
        //         memcpy(zmqData.data(), msclPoint.c_str(), size);
                
        //     }
        // }


        s_send_idx(*socket,SENSOR_IMU);
        send_one(*socket, msclPackets, 0);

        
        // zmq::message_t msg(&packets, sizeof(mscl::MipDataPackets), NULL);
        // s_send(context,msg);
		// printf("send complete! (in GpsSensingThread::run/while(1))\n");

        sleep (1);
    }
}
