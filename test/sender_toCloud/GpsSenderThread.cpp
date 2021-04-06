#include "GpsSenderThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include "../service/gps_packet.h"
#include <fstream>

#define PACKET_SIZE 1024
// 참고(txt file): https://github.com/BehaviorTree/BehaviorTree.CPP/blob/725eba7e0abbc704284dec393706e5404f1472e3/tools/bt_recorder.cpp
using namespace std;

// http://zguide.zeromq.org/cpp:interrupt

GpsSenderThread::GpsSenderThread(){}

void GpsSenderThread::run(void *contextSub, zmq::socket_t *socketReq){
    printf("start (in GpsSenderThread::run)\n");
    
    // Connect with socket SUB with Sensing Process
    zmq::socket_t socketSub(*(zmq::context_t*)contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "GPS", 3);
    printf("socket connected (in GpsSenderThread::run)\n");

    
    vector<GpsPacket> mGpsPackets;

    int cnt=0;
    while(1){//!stop_flag){

        /* RECIEVE FROM SENSING PROCESS */
        zmq::message_t msgtopic = s_recv(socketSub);
        string topic = (const char *)msgtopic.data();
        cout<<"&msgtopic   :      "<<&msgtopic<<endl;
        cout<<"msgtopic.data:     "<<msgtopic.data()<<endl;

        zmq::message_t msggps_data = s_recv(socketSub);
        cout<<"&msggps_data:      "<<&msggps_data<<endl;
        cout<<"msggps_data.data:  "<<msggps_data.data()<<endl;

        GpsPacket *mGpsPacket = new GpsPacket();
        cout<<"mGpsPacket :       "<<mGpsPacket<<endl;
        cout<<"&mGpsPacket:       "<<&mGpsPacket<<endl;

        memcpy(mGpsPacket, msggps_data.data(), msggps_data.size());
        cout<<"mGpsPacket:        "<<mGpsPacket<<endl;
        cout<<"&mGpsPacket:       "<<&mGpsPacket<<endl;

        printf("===== GPS ====\n");
        mGpsPacket->displayGpsPacket();
        printf("==============\n");
        
        // mGpsPackets.push_back(mGpsPacket);

        /* Send to Cloud Server */
        // s_send_idx(*socketReq, SENSOR_GPS);

        size_t size = sizeof(GpsPacket);
        zmq::message_t zmqDatas(size);
        cout<<"&zmqDatas:         "<<&zmqDatas<<endl;
        cout<<"zmqDatas.data:     "<<zmqDatas.data()<<endl;

        msggps_data.copy(&zmqDatas);
        cout<<"&zmqDatas:         "<<&zmqDatas<<endl;
        cout<<"zmqDatas.data:     "<<zmqDatas.data()<<endl;

        memset(zmqDatas.data(), 0, size);
        cout<<"&zmqDatas:         "<<&zmqDatas<<endl;
        cout<<"zmqDatas.data:     "<<zmqDatas.data()<<endl;

        // memcpy(zmqDatas.data(), mGpsPacket, size);
        s_send(*socketReq, msggps_data);
        printf("send complete!\n");
        // delete mGpsPacket;

        zmq::message_t msgRecv = s_recv(*socketReq);
        printf("Reply:%s\n", msgRecv.data());

        printf("size=%d (Gps:%d)\n", zmqDatas.size(),size);
        GpsPacket *tmpGpsPacket = new GpsPacket();
        memcpy(tmpGpsPacket, zmqDatas.data(), zmqDatas.size());
        cout<<"tmpGpsPacket:       "<<tmpGpsPacket<<endl;
        cout<<"&tmpGpsPacket:      "<<&tmpGpsPacket<<endl;
        
        printf("============ SEND ============\n");
        tmpGpsPacket->displayGpsPacket();
        printf("==============================\n");
        delete tmpGpsPacket;

        // size_t size = sizeof(mGpsPackets);
        // zmq::message_t zmqDatas(size);
        // memcpy(zmqDatas.data(), &mGpsPackets, size);
        // s_send(*socketReq, zmqDatas);
        // printf("send complete!\n");

        // GpsPacket tmpGpsPacket;
        // memcpy(&tmpGpsPacket, zmqDatas.data(), zmqDatas.size());
        // printf("============ SEND ============\n");
        // tmpGpsPacket.displayGpsPacket();
        // printf("==============================\n");

        // zmq::message_t msgRecv = s_recv(*socketReq);
        // printf("Reply:%s\n", msgRecv.data());

        /* OPTIONS */
        cnt++;
    }

    
    /*
    // Send to Cloud
    //file.close();
    //fclose(file);
    printf("file.close (in GpsSenderThread::run)\n");

    s_send_idx(*socketReq, SENSOR_GPS);
    printf("send_idx complete (in GpsSenderThread::run)\n");

    FILE *infile;
    //infile = fopen(fname.c_str(), "r"); // binary파일 읽기 형식으로 열기
    //printf("open file to read (in GpsSenderThread::run)\n");

    fseek(infile, 0, SEEK_END); // 끝으로 가서
    long file_size = ftell(infile); //사이즈 재고
    //fseek(file, 0, SEEK_END); // 끝으로 가서
    //long file_size = ftell(file); //사이즈 재고
    printf("size of file to read = %d (in GpsSenderThread::run)\n", file_size);

    fseek(infile, 0, SEEK_SET); //처음으로 다시 와서
    //fseek(file, 0, SEEK_SET); //처음으로 다시 와서
    char buf[PACKET_SIZE]; // 데이터 저장 버퍼
    snprintf(buf, PACKET_SIZE-1, "%d", file_size); // 사이즈 값을 buf에다가 넣기, sizeof(buf)
    printf("buf = %s (in GpsSenderThread::run)\n", buf);
    
    zmq::message_t zmqData(file_size);
    memcpy(zmqData.data(), buf, file_size);
    s_send(*socketReq, zmqData);
    string strData = (const char*)zmqData.data();
    printf("send: %s (in GpsSenderThread::run)\n", strData.c_str());

    int sendBytes;
    while((sendBytes==fread(buf, sizeof(char), sizeof(buf), infile))>0){
        s_send(*socketReq, zmqData);
        //while((sendBytes==fread(buf, sizeof(char), sizeof(buf), file))>0) s_send(*socketReq, zmqData);
        printf("send: %s (in GpsSenderThread::run)\n", strData.c_str());
    }
    */
    

}