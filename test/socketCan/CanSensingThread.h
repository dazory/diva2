// diva2/test/sensor_connection/Can_connect.cpp

#pragma once
#include "CanSensing.cpp"
#include "../service/zmq_helper.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <sys/timeb.h>

using namespace std;

extern int USE_CAN;

class CanSensingThread{
	public:
	CanSensingThread();
	static void run(zmq::socket_t *socket); // const char *devicename, const char *baudrate, 
};

CanSensingThread::CanSensingThread(){
}

void CanSensingThread::run(zmq::socket_t *socket){
	printf("start (in CanSensingThread::run)\n");
	
	CanSensing mCanSensing;

    int iDev;
	if(USE_CAN==1){
        iDev = mCanSensing.initialize("/dev/ttyACM0");
		printf("Can.initialize (in CanSensingThread::run)\n");
	}	

	while (1) {
		printf("while(1) start! (in CanSensingThread::run/while(1))\n");
		
		if(USE_CAN==1){
			// printf("======= REAL Can DATA ========\n");
			// s_send_idx(*socket, SENSOR_CAN);

			// // Read 255bytes from Can
			// int nRet = 0; char cBuff[255];
			// nRet = read(iDev, cBuff, 255);
			// cBuff[nRet] = 0;
			// CanPacket mCanPacket = mCanSensing.getCanPacket();

			// mCanPacket.readCanPacket(cBuff);
			// mCanPacket.displayCanPacket();
			
			// size_t size = sizeof(mCanPacket);
            // zmq::message_t zmqData(size);
            // memcpy(zmqData.data(), &mCanPacket, size);
            // s_send(*socket, zmqData);
            // printf("send complete! (in CanSensingThread::run/while(1))\n");
		}
		
		/* OPTION */
		sleep(1);
    }

	printf("terminate complete! (in CanSensingThread::run/while(1))\n");

}