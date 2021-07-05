#include "imuthread.h"
#include <zmq.hpp>
#include <sys/time.h>
#include <cmath>

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

imuThread::imuThread(QObject *parent) : QThread(parent)
{	
}

void imuThread::run() {

    zmq::context_t ctx(1);
    zmq::socket_t imu_sub(ctx, ZMQ_SUB);
    imu_sub.connect( "tcp://10.8.0.8:5563");
    imu_sub.setsockopt(ZMQ_SUBSCRIBE,  "IMU", 3);
    
    file.open("imu_delay.csv");

    while(!stop_flag) {
        sensors::Imu imu;
        string topic=s_recv(imu_sub);
        zmq::message_t msg;
        imu_sub.recv(&msg);
        cout<<"recived\n";

        //protobuf parsing
        imu.ParseFromArray(msg.data(), msg.size());
        accel_x=imu.scaledaccelx();
        accel_y=imu.scaledaccely();
        accel_z=imu.scaledaccelz();
        
        //전송 delay 측정
        struct timeval tv;
        gettimeofday(&tv, NULL);
        double cur=1000000*tv.tv_sec + tv.tv_usec;
        file<<cur-imu.timestamp()<<",us\n";

        //signal
        emit send_acc(accel_x, accel_y, accel_z);
    }
}


void imuThread::stop(){
	stop_flag = true;
    file.close();
}