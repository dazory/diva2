#include "GpsVisualization.h"
#include "../../service/Timestamp.h"
#include "../../service/global_name.hpp"
#include "../../protobuf/sensors.pb.h"
#include <fstream>
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

using namespace std;

GpsVisualization::GpsVisualization() {}

void GpsVisualization::run(void *contextSub)
{
    printf("[MobilePlatform/Visualization/GpsVisualization] run\n");

    // [Connect with socket SUB with Sensing Process]
    zmq::socket_t SubSock(*(zmq::context_t *)contextSub, ZMQ_SUB);
    SubSock.connect(protocol::SENSING_SUB);
    SubSock.setsockopt(ZMQ_SUBSCRIBE, "GPS", 3);
    // SubSock.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    printf("[MobilePlatform/Visualization/GpsVisualization] Connet with SUB socket\n");

    while (1)
    {
        int USE_PROTO = 1;

        // [Receive the topic From SUB Socket]
        zmq::message_t msgtopic = s_recv(SubSock);
        string topic = (const char *)msgtopic.data();
        printf("[MobilePlatform/Visualization/GpsVisualization] Toic=%s\n",topic.c_str());

        // [Receive the message from SUB Socket]
        sensors::Gps gps;
        zmq::message_t msgData;
        SubSock.recv(&msgData);
        printf("[MobilePlatform/Visualization/GpsVisualization] Receive %dbytes\n",msgData.size());
        int data_len = msgData.size();
        unsigned char cBytes[data_len];
        memcpy(cBytes, msgData.data(), msgData.size());
        for (auto i = 0; i < data_len; i++)
            printf("%02X ", cBytes[i]);
        printf("\n");

        printf("\n");
        gps.ParseFromArray(msgData.data(), msgData.size());
        
        printf("latitude=%f, longitude=%f\n",gps.latitude(), gps.longitude());

        // [OPTIONAL: DELETE ALL GLOBAL OBJECTS ALLOCATED BY LIBPROTOBUF]
        google::protobuf::ShutdownProtobufLibrary();

        
        // [OPTIONS]
        // sleep(1);
    }
}