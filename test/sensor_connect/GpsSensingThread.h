// diva2/test/sensor_connection/gps_connect.cpp

#pragma once
#include "GpsSensing.cpp"
#include "../service/zmq_helper.h"
#include "../service/gps_packet.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <sys/timeb.h>

using namespace std;

extern int USE_GPS;
extern map<string, tuple<string, int>> SensorInfoMap;

class GpsSensingThread{
	public:
	GpsSensingThread();
	static void run(zmq::socket_t *socket); // const char *devicename, const char *baudrate, 
};

GpsSensingThread::GpsSensingThread(){
}

void GpsSensingThread::run(zmq::socket_t *socket){
	printf("start (in GpsSensingThread::run)\n");
	
	int iDev = 0; int speed=0; Can_serial cs; Linux_keyboard lk;
	GpsSensing mGpsSensing;

	if(USE_GPS==1){
		//iDev = mGpsSensing.initialize(get<0>(SensorInfoMap["GPS"]));
		iDev = mGpsSensing.initialize("/dev/ttyACM0");
		printf("gps.initialize (in GpsSensingThread::run)\n");
		
		//speed = get<1>(SensorInfoMap["GPS"]);
		speed = B1200;
		printf("baudrate setting (in GpsSensingThread::run)\n");
		
		cs.init_serial(iDev,speed);
		printf("GPS device connect setting complete! (in GpsSensingThread::run)\n");

		lk.init_keyboard();
		printf("keyboard initialize (in GpsSensingThread::run)\n");
	}	

	while (1) {
		printf("while(1) start! (in GpsSensingThread::run/while(1))\n");
		
		if(USE_GPS==1){
			printf("======= REAL GPS DATA ========\n");
			s_send_idx(*socket, SENSOR_GPS);

			// Read 255bytes from GPS
			int nRet = 0; char cBuff[255];
			nRet = read(iDev, cBuff, 255);
			cBuff[nRet] = 0;
			GpsPacket mGpsPacket = mGpsSensing.getGpsPacket();

			mGpsPacket.readGpsPacket(cBuff);
			mGpsPacket.displayGpsPacket();
			
			size_t size = sizeof(mGpsPacket);
            zmq::message_t zmqData(size);
            memcpy(zmqData.data(), &mGpsPacket, size);
            s_send(*socket, zmqData);
            printf("send complete! (in GpsSensingThread::run/while(1))\n");
		}
		
		if(USE_GPS==2){
			printf("======= GPS TEST DATA ========\n");
			/* TEST */
			s_send_idx(*socket, SENSOR_GPS);

			char cBuff[255] = "$GNGGA,015442.01,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,,*61";
			GpsPacket mGpsPacket = mGpsSensing.getGpsPacket();

			mGpsPacket.readGpsPacket(cBuff);
			mGpsPacket.displayGpsPacket();
			printf("=============================\n");
			
			size_t size = sizeof(mGpsPacket);
            zmq::message_t zmqData(size);
            memcpy(zmqData.data(), &mGpsPacket, size);
            s_send(*socket, zmqData);
            printf("send complete! (size=%d)(in GpsSensingThread::run/while(1))\n",size);
		}		

		/* OPTION */
		sleep(1);
    }

	if(USE_GPS){
		lk.close_keyboard();
		cs.close_serial(iDev);
	}
	printf("terminate complete! (in GpsSensingThread::run/while(1))\n");

}