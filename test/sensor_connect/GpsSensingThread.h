// diva2/test/sensor_connection/gps_connect.cpp

#pragma once
#include "GpsSensing.cpp"
#include "service/zmq_helper.h"

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
	//iDev = gpsThread.initialize(devicename);
	printf("gps.initialize (in GpsSensingThread::run)\n");
	
	//int speed = gpsThread.getBaudrate(baudrate);
	printf("baudrate setting (in GpsSensingThread::run)\n");
	
	Can_serial cs; 
	//cs.init_serial(iDev,speed);
	printf("GPS device connect setting complete! (in GpsSensingThread::run)\n");

	Linux_keyboard lk;
	lk.init_keyboard();
	printf("keyboard initialize (in GpsSensingThread::run)\n");

	while (1) {
		printf("while(1) start! (in GpsSensingThread::run/while(1))\n");
		int iRet = 0; char cBuff[255];


		string s_index = "GPS";
		size_t sizeofindex = s_index.size()+1;
    	zmq::message_t m_index(sizeofindex);
    	memcpy(m_index.data(), s_index.c_str(), sizeofindex);
		s_sendmore (*socket, m_index);
		cout<<"s_sendmore: index = "<<(const char *)m_index.data()<<"  (in GpsSensingThread::run/while(1))"<<endl;

		// iRet = read(iDev, cBuff, 255);
		// cBuff[iRet] = 0;
		// printf("read 511byte from iDev (in GpsSensingThread::run/while(1))\n");
		// printf("   : %s\n",cBuff);
		string test_gpsdata = "$GPGGA,015442.00,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,*61";
		memcpy(cBuff,"$GPGGA,015442.00,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,*61",test_gpsdata.size()+1);
		cBuff[test_gpsdata.size()] = 0;
		printf("   cBuff: %s\n",cBuff);

        // //zmq::message_t msg(&cBuff, sizeof(char)*255, NULL);
		// zmq::message_t msg(sizeof(char)*255);
    	// memcpy(msg.data(), cBuff, sizeof(char)*255);
        // s_send (*socket, msg);
		// printf("send data to PUB (tcp:5563) (in GpsSensingThread::run/while(1))\n");
		
		size_t sizeofdata = test_gpsdata.size()+1;
    	zmq::message_t m_data(sizeofdata);
    	memcpy(m_data.data(), cBuff, sizeofdata);
		s_send (*socket, m_data);
		cout<<"s_send: data = "<<(const char *)m_data.data()<<"  (in GpsSensingThread::run/while(1))"<<endl;
		// string gpsdata = "$GPGGA,015442.00,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,*61";
		// size_t size2 = gpsdata.size()+1;
		// zmq::message_t msg_dd(size2);
    	// memcpy(msg_dd.data(), gpsdata.c_str(), size2);
		// s_send_str (*socket, msg_dd);
		// cout<<"sending: msg_dd = "<<(const char *)msg_dd.data()<<endl;


		//int rc=0;
		// rc = s_sendmore (*socket, gps);
		//rc = s_send_str (*socket, message);
		
        sleep (1);
    }

	lk.close_keyboard();
	cs.close_serial(iDev);
	printf("terminate complete! (in GpsSensingThread::run/while(1))\n");

}