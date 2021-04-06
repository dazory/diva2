// diva2/test/sensor_connection/gps_connect.cpp

#pragma once
#include "GpsSensing.cpp"
#include "../service/zmq_helper.h"

using namespace std;


class GpsSensingThread{
	public:
	GpsSensingThread();
	static void run(const char *devicename, const char *baudrate, zmq::socket_t *socket);
};

GpsSensingThread::GpsSensingThread(){
}

void GpsSensingThread::run(const char *devicename, const char *baudrate, zmq::socket_t *socket){
	printf("start (in GpsSensingThread::run)\n");
	
	int iDev = 0; 
	GpsSensing gpsThread;
	iDev = gpsThread.initialize(devicename);
	printf("gps.initialize (in GpsSensingThread::run)\n");
	
	int speed = gpsThread.getBaudrate(baudrate);
	printf("baudrate setting (in GpsSensingThread::run)\n");
	
	Can_serial cs; 
	cs.init_serial(iDev,speed);
	printf("GPS device connect setting complete! (in GpsSensingThread::run)\n");

	Linux_keyboard lk;
	lk.init_keyboard();
	printf("keyboard initialize (in GpsSensingThread::run)\n");

	while (1) {
		printf("while(1) start! (in GpsSensingThread::run/while(1))\n");
		
		/* REAL */
		s_send_idx(*socket, SENSOR_GPS);
		
		// Read 255bytes from GPS
		int nRet = 0; char cBuff[255];
		nRet = read(iDev, cBuff, 255);
		cBuff[nRet] = 0;


		size_t size = sizeof(char)*256;
		zmq::message_t zmqData(size);
    	memcpy(zmqData.data(), cBuff, size);
        s_send (*socket, zmqData);
	 	cout<<"zmqData = "<<(const char *)zmqData.data()<<"  (in GpsSensingThread::run)"<<endl;
		
		/* TEST */
		// s_send_idx(*socket, SENSOR_GPS);
		// s_send_test(*socket, SENSOR_GPS);

		/* OPTION */
		sleep(1);
    }

	lk.close_keyboard();
	cs.close_serial(iDev);
	printf("terminate complete! (in GpsSensingThread::run/while(1))\n");

}