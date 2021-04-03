//#pragma once
#ifndef CAMSENSINGTHREAD_H_
#define CAMSENSINGTHREAD_H_
#include "CamSensing.cpp"

inline static bool S_sendmore(zmq::socket_t &publisher, const void *data)
{
    bool rc = publisher.send(data, ZMQ_SNDMORE);
    return (rc);
}

inline static bool S_send(zmq::socket_t &publisher, zmq::message_t &data, int flags = 0)
{
    bool rc = publisher.send(data, flags);
    return (rc);
}

class CamSensingThread{

public:
    CamSensingThread();
    static void run(const int devicename, zmq::context_t *context, zmq::socket_t *publisher);
};

CamSensingThread::CamSensingThread(){

}

void my_free(void *data, void *hint){
    free(data);
}
void CamSensingThread::run(const int devicename, zmq::context_t *context, zmq::socket_t *publisher){

    CamSensing camThread;
    int open = camThread.initialize(devicename);
    printf("cam open[%d] (in CamSensingThread::run())\n");

    vector<uchar> buffer;
    while (open)
    {
        camThread.cap.read(camThread.frame);
        printf("read cap (in CamSensingThread::run())\n");

        Mat frame;
        camThread.cap  >> frame;
        printf("copy cap to frame (in CamSensingThread::run())\n");

        //S_sendmore(*publisher, "CAM");
        s_send_idx(*publisher,SENSOR_CAM);
        printf("sendmore: CAM (in CamSensingThread::run())\n");

        //jpg로 인코딩해서 버퍼에 담은 다음 전송
        imencode(".jpg", camThread.frame, buffer);
        zmq::message_t msg(buffer.size());
        memcpy(msg.data(), buffer.data(), buffer.size());
        publisher->send(msg);
        
        sleep(1);
    }
}


#endif //CAMSENSINGTHREAD_H_