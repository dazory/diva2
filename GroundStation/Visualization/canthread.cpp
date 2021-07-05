#include "canthread.h"
#include <zmq.hpp>
#include <sys/time.h>

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

canThread::canThread(QObject *parent) : QThread(parent)
{  			 
}

void canThread::run(){
	zmq::context_t ctx(1);
    zmq::socket_t can_sub(ctx, ZMQ_SUB);
    can_sub.connect("tcp://10.8.0.8:5563");
    can_sub.setsockopt(ZMQ_SUBSCRIBE, "CAN", 3);

    file.open("can_delay.csv");

    while(!stop_flag){
        sensors::Can can;
        string topic=s_recv(can_sub);
        zmq::message_t msg;
        can_sub.recv(&msg);

        //protobuf parsing
        can.ParseFromArray(msg.data(), msg.size());

        //전송 delay 측정
        struct timeval tv;
        gettimeofday(&tv, NULL);
        double cur=1000000*tv.tv_sec + tv.tv_usec;
        file<<cur-can.timestamp()<<",us\n";

        //type에 따른 signal 전송
        int data_type=can.type();
        switch (data_type){
            case 688:
                emit send_handle(QString::number(can.data()));
                break;
            case 790:
                emit send_speed(can.data());
                break;
            case 1322:
                emit send_gear((int)can.data());
                break;
            case 1345:
                emit send_turn((int)can.data());
                break;
        }
    }
}

void canThread::stop(){
	stop_flag = true;
    file.close();
}