#include "GpsSenderThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include "../service/gps_packet.h"
#include "../protobuf/sensors.pb.h"
#include <fstream>
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

#define PACKET_SIZE 1024

// 참고(txt file): https://github.com/BehaviorTree/BehaviorTree.CPP/blob/725eba7e0abbc704284dec393706e5404f1472e3/tools/bt_recorder.cpp
using namespace std;

// http://zguide.zeromq.org/cpp:interrupt

GpsSenderThread::GpsSenderThread() {}

void GpsSenderThread::run(void *contextSub, zmq::socket_t *socketReq)
{
    printf("start (in GpsSenderThread::run)\n");

    // Connect with socket SUB with Sensing Process
    zmq::socket_t socketSub(*(zmq::context_t *)contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    printf("socket connected (in GpsSenderThread::run)\n");

    vector<GpsPacket> mGpsPackets;

    int cnt = 0;
    while (1)
    { //!stop_flag){

        int USE_PROTO = 1;

        sensors::Gps gps;
        /* RECIEVE FROM SENSING PROCESS */
        if (USE_PROTO == 1) // REAL CONDITION
        {
            zmq::message_t msgData;
            socketSub.recv(&msgData);
            printf("Recevied(in GpsSenderThread::run)\n");
            printf("~~~~~~~~~~~~~~~~ SIZE = %d ~~~~~~~~~~~~~~~~ \n", msgData.size());

            unsigned char data[1024] = "\0";
            gps.ParseFromArray(msgData.data(), msgData.size());
        }
        else // TEST CONDITION
        {
            zmq::message_t msg = s_recv(socketSub);
            GpsPacket *mGpsPacket = new GpsPacket();
            memcpy(mGpsPacket, msg.data(), msg.size());

            gps.set_gpgga("temp");

            gps.set_latitude(mGpsPacket->Latitude);
            if (mGpsPacket->NorthSouth == 1)
                gps.set_isnorth(1);
            else if (mGpsPacket->NorthSouth = 0)
                gps.set_isnorth(0);
            gps.set_longitude(mGpsPacket->Longitude);
            if (mGpsPacket->NorthSouth == 1)
                gps.set_iseast(1);
            else if (mGpsPacket->NorthSouth = 0)
                gps.set_iseast(0);
            gps.set_gpsquality(mGpsPacket->GPSQuality);
            gps.set_numberofsatellitesinuse(mGpsPacket->NumberOfSatellitesInUse);
            gps.set_horizontaldilutionofprecision(mGpsPacket->HorizontalDilutionOfPrecision);
            gps.set_antennaaltitudemeters(mGpsPacket->AntennaAltitudeMeters);
            gps.set_geoidalseparationmeters(mGpsPacket->GeoidalSeparationMeters);
            gps.set_ageofdifferentialgpsdataseconds(mGpsPacket->AgeOfDifferentialGPSDataSeconds);
            gps.set_differentialreferencestationid(mGpsPacket->DifferentialReferenceStationID);
        }

        /* DATA SERIALIZATION */

        /* SEND TO CLOUD SERVER */
        int data_len = gps.ByteSize();
        unsigned char data[1024] = "\0";
        gps.SerializeToArray(data, data_len);
        for (auto i = 0; i < data_len; i++)
            printf("%02X ", data[i]);
        printf("\n");

        size_t size = data_len;
        zmq::message_t zmqDatas(size);
        // memcpy((void*)zmqDatas.data(), strMsg.c_str(), size);
        memcpy((void *)zmqDatas.data(), data, size);
        printf("Sending GPS data ...\n");
        s_send(*socketReq, zmqDatas);
        printf("send complete!\n");

        /* OPTIONAL: DELETE ALL GLOBAL OBJECTS ALLOCATED BY LIBPROTOBUF */
        google::protobuf::ShutdownProtobufLibrary();

        /* RECEIVE FROM CLOUD SERVER PROCESS */
        zmq::message_t msgRecv = s_recv(*socketReq);
        printf("Reply:%s\n", msgRecv.data());
        printf("size=%d (Gps:%d)\n", zmqDatas.size(), size);

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