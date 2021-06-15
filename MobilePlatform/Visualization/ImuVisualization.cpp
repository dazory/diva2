#include "ImuVisualization.h"
#include <sys/time.h>

#include <fstream>

#include "../../service/Timestamp.h"
#include "../../service/global_name.hpp"
#include "../../protobuf/sensors.pb.h"

#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

using namespace std;

ImuVisualization::ImuVisualization() {}

void ImuVisualization::run(void *contextSub)
{
    printf("[MobilePlatform/Visualization/ImuVisualization] run\n");

    // [Connect with socket SUB with Sensing Process]
    zmq::socket_t SubSock(*(zmq::context_t *)contextSub, ZMQ_SUB);
    SubSock.connect(protocol::SENSING_SUB);
    SubSock.setsockopt(ZMQ_SUBSCRIBE, "IMU", 3);
    printf("[MobilePlatform/Visualization/ImuVisualization] Connet with SUB socket\n");

    int cnt = 0;
    clock_t clk_bef = clock();
    clock_t clk_now = clock();

    fstream dataFile;
    dataFile.open("IMU_DELAY.csv", ios::out);
    while (1)
    {
        int USE_PROTO = 1;

        // [Receive the topic From SUB Socket]
        zmq::message_t msgtopic = s_recv(SubSock);
        string topic = (const char *)msgtopic.data();
        printf("[MobilePlatform/Visualization/ImuVisualization] Toic=%s\n",topic.c_str());

        // [Receive the message from SUB Socket]
        sensors::Imu imu;
        zmq::message_t msgData;
        SubSock.recv(&msgData);


        // < timestamp >
        // struct timeval tv;
        // auto *end_ts = new google::protobuf::Timestamp();
        // gettimeofday(&tv, NULL);
        // end_ts->set_seconds(tv.tv_sec);
        // end_ts->set_nanos(tv.tv_usec*1000);

        clk_now = clock();
        printf("(%dms)[MobilePlatform/Visualization/ImuVisualization] Receive %dbytes\n",(float)(clk_now-clk_bef)/CLOCKS_PER_SEC*1000, msgData.size()); cnt++;
        clk_bef = clk_now;
        int data_len = msgData.size();
        unsigned char cBytes[data_len];
        memcpy(cBytes, msgData.data(), msgData.size());
        for (auto i = 0; i < data_len; i++)
            printf("%02X ", cBytes[i]);
        printf("\n");

        printf("\n");
        imu.ParseFromArray(msgData.data(), msgData.size());

        // <TIME>
        // auto *dur_ts = new google::protobuf::Timestamp();
        // dur_ts->set_seconds(end_ts->seconds()-imu.timestamp().seconds());
        // dur_ts->set_nanos(end_ts->nanos()-imu.timestamp().nanos());
        // printf("dur:%f,  %f\n", dur_ts->seconds(), dur_ts->nanos());
        // dataFile<<dur_ts->seconds()<<","<<dur_ts->nanos()<<","<<dur_ts->seconds()*1000+dur_ts->nanos()<<endl;
        
        printf("ScaleAccelX=%f, ScaleAccelY=%f, ScaleAccelZ=%f\n",imu.scaledaccelx(), imu.scaledaccely(), imu.scaledaccelz());

        // [OPTIONAL: DELETE ALL GLOBAL OBJECTS ALLOCATED BY LIBPROTOBUF]
        google::protobuf::ShutdownProtobufLibrary();

        
        // [OPTIONS]
        // sleep(1);
    }

    dataFile.close();
}