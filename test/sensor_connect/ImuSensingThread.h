// test/sensor_connect/ImuSensingThread.h
#pragma once
#include <string>
#include <iostream>
#include "ImuSensing.cpp"
#include "ImuSensing.h"
#include "../service/ImuPacket.h"

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
	//printf("start (MSCL ver: %s)(in ImuSensingThread::run)\n",mscl::MSCL_VERSION.str());
    //printf("start (MSCL)(in ImuSensingThread::run)\n");

    ImuSensing imuThread;
    mscl::InertialNode msclNode = imuThread.getMsclNode(devicename,baudrate);
	printf("imu.getMsclNode (in ImuSensingThread::run)\n");

    
    Init();

    while(1){
        mscl::MipDataPackets msclPackets = msclNode.getDataPackets(500);
        printf("getDataPackets (in ImuSensingThread::run/while(1))\n");
        ImuPacket mImuPacket;
        //IMUdata temp;

        
        // for(mscl::MipDataPacket msclPacket : msclPackets){
        //     int count = 0;
        //     msclPacket.descriptorSet();
        //     mscl::MipDataPoints msclPoints = msclPacket.data();

        //     for(mscl::MipDataPoint msclPoint : msclPoints){
        //         // size_t size = sizeof(msclPoint) + 1;
        //         // zmq::message_t zmqData(size);
        //         // memcpy(zmqData.data(), msclPoint, size);
                
        //     }

        //     s_send_idx(*socket,SENSOR_IMU);
            
        //     size_t size = msclPoints.size();
        //     zmq::message_t zmqData(size);
        //     memcpy(zmqData.data(), static_cast<void *>(&msclPoints), size);
        //     s_send(*socket,zmqData);
        //     printf("send complete! (in GpsSensingThread::run/while(1))\n");

        // }

        /* DIVA */
        for(mscl::MipDataPacket packet : msclPackets){ //
        // printf("MipDataPacket for loop start  (in ImuSensingThread::run/while(1))\n");

            packet.descriptorSet();
            mscl::MipDataPoints points = packet.data();
            
            for(mscl::MipDataPoint dataPoint : points)
            {
                // printf("dataPoint for loop start  (in ImuSensingThread::run/while(1))\n");
                const char *cName = dataPoint.channelName().c_str();
                printf("cName =%s, %d : ",cName, ImuMap[cName]);
                
                switch(ImuMap[cName]){
                    case IMU_ACCELX:
                        {mImuPacket.scaledAccelX = dataPoint.as_float(); printf("IMU_ACCELX\n"); break;}
                    case IMU_ACCELY:
                        {mImuPacket.scaledAccelY = dataPoint.as_float(); printf("IMU_ACCELY\n"); break;}
                    case IMU_ACCELZ:
                        {mImuPacket.scaledAccelZ = dataPoint.as_float(); printf("IMU_ACCELZ\n"); break;}
                    case IMU_GYROX:
                        {mImuPacket.scaledGyroX = dataPoint.as_float(); printf("IMU_GYROX\n"); break;}
                    case IMU_GYROY:
                        {mImuPacket.scaledGyroY = dataPoint.as_float(); printf("IMU_GYROY\n"); break;}
                    case IMU_GYROZ:
                        {mImuPacket.scaledGyroZ = dataPoint.as_float(); printf("IMU_GYROZ\n"); break;}
                    case IMU_MAGX:
                        {mImuPacket.scaledMagX = dataPoint.as_float(); printf("IMU_MAGX\n"); break;}
                    case IMU_MAGY:
                        {mImuPacket.scaledMagY = dataPoint.as_float(); printf("IMU_MAGY\n"); break;}
                    case IMU_MAGZ:
                        {mImuPacket.scaledMagZ = dataPoint.as_float(); break;} 

                    case IMU_ESTROLL:
                        {mImuPacket.estRoll = dataPoint.as_float(); printf("IMU_ESTROLL\n"); break;}
                    case IMU_ESTPITCH:
                        {mImuPacket.estPitch = dataPoint.as_float(); printf("IMU_ESTPITCH\n"); break;}
                    case IMU_ESTYAW:
                        {mImuPacket.estYaw = dataPoint.as_float(); printf("IMU_ESTYAW\n"); break;}
                    
                    case IMU_ESTROLL_UNCERT:
                        {mImuPacket.estRollUncert = dataPoint.as_float(); printf("IMU_ESTROLL_UNCERT\n"); break;}
                    case IMU_ESTPITCH_UNCERT:
                        {mImuPacket.estPitchUncert = dataPoint.as_float(); printf("IMU_ESTPITCH_UNCERT\n"); break;}
                    case IMU_ESTYAW_UNCERT:
                        {mImuPacket.estYawUncert = dataPoint.as_float(); printf("IMU_ESTYAW_UNCERT\n"); break;}
                    


                    // case IMU_EXCEPTION:{
                    //     printf("Accel (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledAccelX,mImuPacket.scaledAccelY,mImuPacket.scaledAccelZ );
                    //     printf("Gyro (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledGyroX,mImuPacket.scaledGyroY,mImuPacket.scaledGyroZ );
                    //     //printf("Mag (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledMagX,mImuPacket.scaledMagY,mImuPacket.scaledMagZ );
                    //     break;
                    // }
                    default:
                        printf("\n");
                        break;
                }
                

                
                
            }
            printf("Accel (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledAccelX,mImuPacket.scaledAccelY,mImuPacket.scaledAccelZ );
            printf("Gyro (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledGyroX,mImuPacket.scaledGyroY,mImuPacket.scaledGyroZ );
            printf("Mag (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledMagX,mImuPacket.scaledMagY,mImuPacket.scaledMagZ );
            printf("est (Roll,Pitch,Yaw) = (%.2f, %.2f, %.2f)\n",mImuPacket.estRoll,mImuPacket.estPitch,mImuPacket.estYaw );
            printf("estUncert (Roll,Pitch,Yaw) = (%.2f, %.2f, %.2f)\n",mImuPacket.estRollUncert,mImuPacket.estPitchUncert,mImuPacket.estYawUncert );

        }
        /* DIVA END */


        /*
        s_send_idx(*socket,SENSOR_IMU);
        //send_one(*socket, msclPackets, 0);
        printf("packet.size() = %d \n", msclPackets.size());

        size_t size = msclPackets.capacity(); //msclPackets.size();
        // zmq::message_t msg(&msclPackets, size, NULL);
        zmq::message_t zmqData(size);
        memcpy(zmqData.data(), (&msclPackets), size);
        s_send(*socket,zmqData);
		printf("send complete! (in GpsSensingThread::run/while(1))\n");
        
        mscl::MipDataPackets packets;
        memcpy(&packets, zmqData.data(), size);
        // memcpy(&packets, zmqData.data(), zmqData.size());
        printf("packet.size() = %d \n", packets.size());
        */

        s_send_idx(*socket, SENSOR_IMU);
        
        size_t size = sizeof(mImuPacket);
        zmq::message_t zmqData(size);
        memcpy(zmqData.data(), &mImuPacket, size);
        s_send(*socket, zmqData);
		printf("send complete! (in GpsSensingThread::run/while(1))\n");

        //zmq::message_t msg(&c_msg, sizeof(data), NULL);
        // zmq_msg_t msg; //(%c_msg,sizeof(data),NULL);
        // int rc = zmq_msg_init_size(&msg, sizeof(c_msg));
        // printf("size: %d\n",sizeof(c_msg));
        // memcpy(zmq_msg_data (&msg), &c_msg, sizeof(c_msg));
        // printf("message make!\n");
        //sleep (1);
        usleep(50);
    }
}
