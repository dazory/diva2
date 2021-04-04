// test/sensor_connect/ImuSensingThread.h
#pragma once
#include <string>
#include <iostream>
#include "ImuSensing.cpp"
#include "ImuSensing.h"
#include "../service/zmq_helper.h"

#include "mscl/mscl.h"
#include <czmq.h>
#include <fstream>
using namespace std;

#define CHUNK_SIZE  250000
class IMUdata {
public:
    float gyrox, gyroy, gyroz, magx, magy, magz, accelx, accely, accelz;
};


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

    ImuSensing mImuSensing;
    mscl::InertialNode msclNode = mImuSensing.getMsclNode(devicename,baudrate);
	printf("imu.getMsclNode (in ImuSensingThread::run)\n");

    
    Init();

    while(1){
        mscl::MipDataPackets msclPackets = msclNode.getDataPackets(500);
        printf("getDataPackets (in ImuSensingThread::run/while(1))\n");
        
        for(mscl::MipDataPacket packet : msclPackets){ //
            // printf("MipDataPacket for loop start  (in ImuSensingThread::run/while(1))\n");

            packet.descriptorSet();
            mscl::MipDataPoints points = packet.data();
            for(mscl::MipDataPoint dataPoint : points)
            {
                // printf("dataPoint for loop start  (in ImuSensingThread::run/while(1))\n");
                const char *cName = dataPoint.channelName().c_str();
                printf("cName =%s, %d : ",cName, ImuMap[cName]);

                mImuSensing.read_imuPacket(ImuMap[cName], dataPoint);
            } // End to read a packet line

            mImuSensing.displayImuPacket();

            s_send_idx(*socket, SENSOR_IMU);
            size_t size = mImuSensing.getImuPacketSize();
            zmq::message_t zmqData(size);
            memcpy(zmqData.data(), &(mImuSensing.getImuPacket()), size);
            s_send(*socket, zmqData);
            printf("send complete! (in ImuSensingThread::run/while(1))\n");
            
        } // End to read all packet lines

        sleep (1);
    }
}
