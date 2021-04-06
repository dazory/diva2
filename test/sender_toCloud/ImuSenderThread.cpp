#include "ImuSenderThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include "../service/ImuPacket.h"
#include <fstream>

#define PACKET_SIZE 1024
// 참고(txt file): https://github.com/BehaviorTree/BehaviorTree.CPP/blob/725eba7e0abbc704284dec393706e5404f1472e3/tools/bt_recorder.cpp
using namespace std;

ImuSenderThread::ImuSenderThread(){}

void ImuSenderThread::run(void *contextSub, zmq::socket_t *socketReq){
    printf("start (in ImuSenderThread::run)\n");
    
    // Connect with socket SUB with Sensing Process
    zmq::socket_t socketSub(*(zmq::context_t*)contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    // socketSub.setsockopt(ZMQ_SUBSCRIBE, "IMU", 3);
    printf("socket connected (in ImuSenderThread::run)\n");

    vector<ImuPacket> mImuPackets;

    int cnt=0;
    while(1){//!stop_flag){
        printf("while!\n");
        // size_t size = sizeof(ImuPacket);
        // zmq::message_t zmqDatas(size);
        // printf("size=%d (Imu:%d)\n", zmqDatas.size(),size);
        
        // ImuPacket tmpImuPacket;
        // memcpy(zmqDatas.data(), &tmpImuPacket, size);

        string msg = "Hello World!";
        size_t size = sizeof(msg)+1;
        zmq::message_t zmqData(size);
        memcpy(zmqData.data(), msg.c_str(), size);
        int rc = s_send(*socketReq,zmqData);
        printf("send complete![%d]\n",rc);
        
        zmq::message_t msgRecv = s_recv(*socketReq);
        printf("Reply:%s\n", msgRecv.data());

        cnt++;
    }

    
    /*
    // Send to Cloud
    //file.close();
    //fclose(file);
    printf("file.close (in ImuSenderThread::run)\n");

    s_send_idx(*socketReq, SENSOR_Imu);
    printf("send_idx complete (in ImuSenderThread::run)\n");

    FILE *infile;
    //infile = fopen(fname.c_str(), "r"); // binary파일 읽기 형식으로 열기
    //printf("open file to read (in ImuSenderThread::run)\n");

    fseek(infile, 0, SEEK_END); // 끝으로 가서
    long file_size = ftell(infile); //사이즈 재고
    //fseek(file, 0, SEEK_END); // 끝으로 가서
    //long file_size = ftell(file); //사이즈 재고
    printf("size of file to read = %d (in ImuSenderThread::run)\n", file_size);

    fseek(infile, 0, SEEK_SET); //처음으로 다시 와서
    //fseek(file, 0, SEEK_SET); //처음으로 다시 와서
    char buf[PACKET_SIZE]; // 데이터 저장 버퍼
    snprintf(buf, PACKET_SIZE-1, "%d", file_size); // 사이즈 값을 buf에다가 넣기, sizeof(buf)
    printf("buf = %s (in ImuSenderThread::run)\n", buf);
    
    zmq::message_t zmqData(file_size);
    memcpy(zmqData.data(), buf, file_size);
    s_send(*socketReq, zmqData);
    string strData = (const char*)zmqData.data();
    printf("send: %s (in ImuSenderThread::run)\n", strData.c_str());

    int sendBytes;
    while((sendBytes==fread(buf, sizeof(char), sizeof(buf), infile))>0){
        s_send(*socketReq, zmqData);
        //while((sendBytes==fread(buf, sizeof(char), sizeof(buf), file))>0) s_send(*socketReq, zmqData);
        printf("send: %s (in ImuSenderThread::run)\n", strData.c_str());
    }
    */
    

}