#include "GpsSenderThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include <fstream>

#define PACKET_SIZE 1024
// 참고(txt file): https://github.com/BehaviorTree/BehaviorTree.CPP/blob/725eba7e0abbc704284dec393706e5404f1472e3/tools/bt_recorder.cpp
using namespace std;

// http://zguide.zeromq.org/cpp:interrupt

GpsSenderThread::GpsSenderThread(){}

void GpsSenderThread::run(void *contextSub, zmq::socket_t *socketPub){
    printf("start (in GpsSenderThread::run)\n");
    
    zmq::socket_t socketSub(*(zmq::context_t*)contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "GPS", 3);
    printf("socket connected (in GpsSenderThread::run)\n");

    Timestamp mTimestamp;
    string fname = "/home/diva2/GPS_log/";
    // string now = mTimestamp.getMilliTime();
    string now = "1234";
    fname.append(now); fname.append(".txt");
    // ofstream file;
    // file.open(fname.c_str(), ios::out | ios::app | ios::binary);
    FILE *file = fopen(fname.c_str(), "a+"); // 읽기/쓰기 모드로 열기
    fseek(file, 0, SEEK_END); // 끝으로 가기
    printf("file open = %s (in GpsSenderThread::run)\n", fname.c_str());

    int cnt=0;
    while(cnt < 1){//!stop_flag){

        // Receive from Sensing Process
        zmq::message_t msgTopic = s_recv(socketSub);
        string strTopic = (const char*)msgTopic.data();
        printf("topic = %s (in GpsSenderThread::run)\n", strTopic.c_str());

        zmq::message_t msgData = s_recv(socketSub);
        string strData = (const char*)msgData.data();
        printf("data = %s (in GpsSenderThread::run)\n", strData.c_str());

        // Write data to file
        long strSize = sizeof(strData);
        //file << strData << endl;
        fwrite(strData.c_str(), strSize, 1, file);
        printf("file.write = %s [size=%d] (in GpsSenderThread::run)\n", strData.c_str(),strSize);

        cnt++;
    }

    // Send to Cloud
    //file.close();
    fclose(file);
    printf("file.close (in GpsSenderThread::run)\n");

    s_send_idx(*socketPub, SENSOR_GPS);
    printf("send_idx complete (in GpsSenderThread::run)\n");

    FILE *infile;
    infile = fopen(fname.c_str(), "r"); // binary파일 읽기 형식으로 열기
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
    s_send(*socketPub, zmqData);
    string strData = (const char*)zmqData.data();
    printf("send: %s (in GpsSenderThread::run)\n", strData.c_str());

    int sendBytes;
    while((sendBytes==fread(buf, sizeof(char), sizeof(buf), infile))>0){
        s_send(*socketPub, zmqData);
        //while((sendBytes==fread(buf, sizeof(char), sizeof(buf), file))>0) s_send(*socketPub, zmqData);
        printf("send: %s (in GpsSenderThread::run)\n", strData.c_str());
    }

    

}