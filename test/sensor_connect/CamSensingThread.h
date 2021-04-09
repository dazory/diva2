//#pragma once
#ifndef CAMSENSINGTHREAD_H_
#define CAMSENSINGTHREAD_H_
#include "CamSensing.cpp"
#include "../service/cam_packet.h"

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
    if(USE_CAM==1){
        open = camThread.initialize(devicename);
        printf("cam open[%d] (in CamSensingThread::run())\n");  
    } 

    vector<uchar> buffer;
    while (open)
    {
        if(USE_CAM==1){
            s_send_idx(*publisher, SENSOR_CAM);
            printf("sendmore: CAM (in CamSensingThread::run())\n");
            
            CamPacket mCamPacket;
            mCamPacket.read(camThread.cap);
            // mCamPacket.display();

            size_t size = sizeof(mCamPacket);
            zmq::message_t zmqData(size);
            memcpy(zmqData.data(), &mCamPacket, size);
            
            //publisher->send(zmq);
            s_send(*publisher,zmqData);
            
            /* TEST */
            printf("TEST!\n");
            CamPacket tmpCamPacket;
            printf("size=%d == %d\n",zmqData.size(), size);
            memcpy(&tmpCamPacket, zmqData.data(), zmqData.size());
            // tmpCamPacket.image = imdecode(Mat(tmpCamPacket.img_buff),CV_LOAD_IMAGE_COLOR);
            tmpCamPacket.display();
            
        }
        /*
        camThread.cap.read(camThread.frame);
        printf("read cap (in CamSensingThread::run())\n");
        Mat frame;
        camThread.cap  >> frame;
        printf("copy cap to frame (in CamSensingThread::run())\n");
        //imencode(".jpg", camThread.frame, buffer); //image encode -> jpg
        //S_sendmore(*publisher, "CAM");
        s_send_idx(*publisher,SENSOR_CAM);
        printf("sendmore: CAM (in CamSensingThread::run())\n");
        // send the capture image through socket
        int32_t info[3];
        info[0]=(int32_t)frame.rows;
        info[1]=(int32_t)frame.cols;
        info[2]=(int32_t)frame.type();
        for(int i=0; i<3; i++){
            zmq::message_t msg((void*)&info[i], sizeof(int32_t), NULL);
            publisher->send(msg,ZMQ_SNDMORE);
        }
        void *data = malloc(frame.total()*frame.elemSize());
        memcpy(data,frame.data, frame.total()*frame.elemSize());
        zmq::message_t msg2(data,frame.total()*frame.elemSize(), my_free,NULL);
        
        if (publisher->send(msg2))
            printf("complete to send! (in CamSensingThread::run())\n");
        */

        sleep(1);
    }
}


#endif //CAMSENSINGTHREAD_H_