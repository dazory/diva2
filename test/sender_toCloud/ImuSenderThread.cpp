#include "ImuSenderThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include "../service/ImuPacket.h"
#include <fstream>

#define PACKET_SIZE 1024
// 참고(txt file): https://github.com/BehaviorTree/BehaviorTree.CPP/blob/725eba7e0abbc704284dec393706e5404f1472e3/tools/bt_recorder.cpp
// 포트 열기: sudo iptables -I INPUT 1 -p tcp --dport 5564 -j ACCEPT
using namespace std;

extern int USE_IMU;

ImuSenderThread::ImuSenderThread(){}

void ImuSenderThread::run(void *contextSub, zmq::socket_t *socketReq){
    printf("start (in ImuSenderThread::run)\n");
    
    // Connect with socket SUB with Sensing Process
    zmq::socket_t socketSub(*(zmq::context_t*)contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "IMU", 3);
    printf("socket connected (in ImuSenderThread::run)\n");

    vector<ImuPacket> mImuPackets;

    int cnt=0;
    while(1){//!stop_flag){
        printf("while!\n");
        int rc;
        if(USE_IMU==1){
            ImuPacket mImuPacket;
            zmq::message_t imuData;
            socketSub.recv(&imuData);
            // memcpy(&mImuPacket, imuData.data(), imuData.size());
            
            size_t size = sizeof(ImuPacket);
            zmq::message_t zmqDatas(size);
            ImuPacket tmpImuPacket;
            memcpy(zmqDatas.data(), &tmpImuPacket, size);
            // rc = s_send(*socketReq, zmqDatas);
            rc = s_send(*socketReq, imuData);
            if(rc==1){printf("send complete![%d] (size=%d)\n",rc, zmqDatas.size());}

            zmq::message_t zmqRep = s_recv(*socketReq);
            
            char *pmsg = new char[zmqRep.size()+1];
            memcpy(pmsg,zmqRep.data(),zmqRep.size());
            cout<<"recv "<<" msg:"<<pmsg<<endl;
            if(strcmp(pmsg, "send ok")==0) { printf("complete to receive at Server: %s\n");}
            else {printf("fail\n"); };
            delete []pmsg; pmsg=NULL;
            
        }else if(USE_IMU==0){
            string msg = "Hello World!";
            size_t size = sizeof(msg)+1;
            zmq::message_t zmqData(size);
            memcpy(zmqData.data(), msg.c_str(), size);
            int rc = s_send(*socketReq,zmqData);
            string data = (const char *)zmqData.data();
            printf("send complete![%d] :%s\n",rc, data.c_str());
            
            zmq::message_t msgRecv = s_recv(*socketReq);
            printf("Reply:%s\n", msgRecv.data());
        }
        
    }

}