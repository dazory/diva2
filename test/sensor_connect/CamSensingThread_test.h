//#pragma once
#ifndef CAMSENSINGTHREAD_H_
#define CAMSENSINGTHREAD_H_
#include <unistd.h>

#include "CamSensing.cpp"
#include "../service/cam_packet.h"
#include "../service/zmq_helper.h"

using namespace std;

extern int USE_CAM;

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
    int open;
    if(USE_CAM) open = camThread.initialize(devicename);
    printf("cam open[%d] (in CamSensingThread::run())\n");

    vector<uchar> buffer;
    while (open)
    {
        if(USE_CAM){
            s_send_idx(*publisher, SENSOR_CAM);
            printf("sendmore: CAM (in CamSensingThread::run())\n");
            
            CamPacket mCamPacket;
            mCamPacket.read(camThread.cap);

            zmq::message_t msg(mCamPacket.getSizeofImage());
            memcpy(msg.data(), mCamPacket.image.data(), mCamPacket.getSizeofImage());
            publisher->send(msg);
        }
        
        /*
        camThread.cap.read(camThread.frame);
        printf("read cap (in CamSensingThread::run())\n");

        Mat frame;
        camThread.cap  >> frame;
        printf("copy cap to frame (in CamSensingThread::run())\n");
        
        //jpg로 인코딩해서 버퍼에 담은 다음 전송
        imencode(".jpg", camThread.frame, buffer);
        zmq::message_t msg(buffer.size());
        memcpy(msg.data(), buffer.data(), buffer.size());
        publisher->send(msg);
        */

        /* OPTIONS */
        sleep(1);
    }
}


#endif //CAMSENSINGTHREAD_H_