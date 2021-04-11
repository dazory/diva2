#include "GpsReceiverThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include "../service/gps_packet.h"
#include "sensors.pb.h"
#include <fstream>
#include <google/protobuf/text_format.h>


#define PACKET_SIZE 1024
using namespace std;

GpsReceiverThread::GpsReceiverThread(){}

void GpsReceiverThread::run(void *contextRep){
    printf("start (in GpsReceiverThread::run)\n");
    
    // Connect with socket REP with SenderTocloud
    zmq::socket_t socketRep(*(zmq::context_t*)contextRep, ZMQ_REP);
    printf("socketRep\n");
    socketRep.bind(protocol::RECEIVER_FROMMOBILE_REP_TEST); 
    printf("connect\n");
    printf("socket connected (in GpsReceiverThread::run)\n");

    while(1){//!stop_flag){
        printf("while(1) start! (in GpsReceiverThread::run/while(1))\n");
		
        /* RECIEVE FROM MOBILE */
        zmq::message_t msgData;
        socketRep.recv(&msgData);
        printf("Recevied\n");

        sensors::Gps gps;
        // string strMsg(static_cast<char*>(msgData.data()), msgData.size());
        // gps.ParseFromString(strMsg);
        unsigned char data[1024] = "\0";
        gps.ParseFromArray(msgData.data(), msgData.size());

        string strTxt;
        google::protobuf::TextFormat::PrintToString(gps, &strTxt);
        cout<<strTxt<<endl;
        
        // zmq::message_t msgRecv = s_recv(*socketReq);
        // printf("Data:%s\n", msgRecv.data());
        string strOK = "THANK YOU";
        zmq::message_t zmqData(sizeof(strOK));
        memcpy(zmqData.data(), strOK.c_str(), sizeof(strOK));
        s_send(socketRep, zmqData);
        /* OPTIONS */
        // cnt++;
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

void GpsReceiverThread::stop(){
    stop_flag = true;
}