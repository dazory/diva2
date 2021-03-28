// diva2/test/sensor_connection/gps_connect.cpp

#pragma once
#include "GpsSensing.cpp"
using namespace std;

inline static bool s_sendmore (void *context, const std::string & string) {

	zmq::socket_t socket(*(zmq::context_t*)context,ZMQ_REQ);
	socket.bind("tcp://*:5563");

	zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message, ZMQ_SNDMORE);
    return (rc);
}
inline static bool s_send (void *context, const std::string & string, int flags = 0) {

	zmq::socket_t socket(*(zmq::context_t*)context,ZMQ_REQ);
	socket.bind("tcp://*:5563");

    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message, flags);
    return (rc);
}

class GpsSensingThread{
	public:
	GpsSensingThread();
	static void run(const char *devicename, const char *baudrate, void *context);
};

GpsSensingThread::GpsSensingThread(){
}

void GpsSensingThread::run(const char *devicename, const char *baudrate, void *context){
	printf("start (in GpsSensingThread::run)\n");
	
	GpsSensing gpsThread;
	gpsThread.initialize(devicename);
	printf("gps.initialize (in GpsSensingThread::run)\n");
	
	int speed = gpsThread.getBaudrate(baudrate);
	printf("baudrate setting (in GpsSensingThread::run)\n");
	
	Can_serial cs; int iDev = 0; 
	cs.init_serial(iDev,speed);
	printf("GPS device connect setting complete! (in GpsSensingThread::run)\n");

	Linux_keyboard lk;
	lk.init_keyboard();
	printf("keyboard initialize (in GpsSensingThread::run)\n");

	int iRet = 0; char cBuff[255];
	while (1) {
        s_sendmore (context, "GPS");
		iRet = read(iDev, cBuff, 255);
		cBuff[iRet] = 0;
		printf("read 511byte from iDev (in GpsSensingThread::run/while(1))\n");
		printf("   : %s\n",cBuff);

        s_send (context, cBuff);
		printf("send data to PUB (tcp:5563) (in GpsSensingThread::run/while(1))\n");
		
        sleep (1);
    }

	lk.close_keyboard();
	cs.close_serial(iDev);
	printf("terminate complete! (in GpsSensingThread::run/while(1))\n");

}