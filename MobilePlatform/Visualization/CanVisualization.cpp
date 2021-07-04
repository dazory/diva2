#include "CanVisualization.h"
#include <sys/time.h>
#include "../../service/Timestamp.h"
#include "../../service/global_name.hpp"
#include "../../protobuf/sensors.pb.h"
#include <fstream>
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

using namespace std;

CanVisualization::CanVisualization() {}

void CanVisualization::run(void *contextSub)
{
    printf("[MobilePlatform/Visualization/CanVisualization] run\n");

    // [Connect with socket SUB with Sensing Process]
    zmq::socket_t SubSock(*(zmq::context_t *)contextSub, ZMQ_SUB);
    SubSock.connect(protocol::SENSING_SUB);
    SubSock.setsockopt(ZMQ_SUBSCRIBE, "CAN", 3);
    // SubSock.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    printf("[MobilePlatform/Visualization/CanVisualization] Connet with SUB socket\n");

    clock_t time_bef = clock();
    clock_t time_now = clock();

    fstream dataFile;
    dataFile.open("CAN_DELAY.csv", ios::out);
    while (1)
    {
        // [Receive the topic From SUB Socket]
        zmq::message_t msgtopic = s_recv(SubSock);
        string topic = (const char *)msgtopic.data();
        printf("[MobilePlatform/Visualization/CanVisualization] Topic=%s\n",topic.c_str());

        // [Receive the message from SUB Socket]
        sensors::Can can;
        zmq::message_t msgData;
        SubSock.recv(&msgData);

        // < timestamp >
        struct timeval tv;
        auto *end_ts = new google::protobuf::Timestamp();
        gettimeofday(&tv, NULL);
        end_ts->set_seconds(tv.tv_sec);
        end_ts->set_nanos(tv.tv_usec*1000);

        time_now = clock();
        printf("(%dms)[MobilePlatform/Visualization/CanVisualization] Receive %dbytes\n",(float)(time_now-time_bef)/CLOCKS_PER_SEC*1000,msgData.size());
        time_bef = time_now;
        int data_len = msgData.size();
        unsigned char cBytes[data_len];
        memcpy(cBytes, msgData.data(), msgData.size());
        for (auto i = 0; i < data_len; i++)
            printf("%02X ", cBytes[i]);
        printf("\n");

        printf("\n");
        can.ParseFromArray(msgData.data(), msgData.size());

        // <TIME>
      

        
        printf("type=%f, data=%f\n", can.type(), can.data());
        

        // [OPTIONAL: DELETE ALL GLOBAL OBJECTS ALLOCATED BY LIBPROTOBUF]
        google::protobuf::ShutdownProtobufLibrary();

        
        // [OPTIONS]
        // sleep(1);
    }


    dataFile.close();
}