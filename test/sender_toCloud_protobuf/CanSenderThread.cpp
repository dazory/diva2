#pragma once

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "CanSenderThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include "../protobuf/sensors.pb.h"
#include <fstream>
#include "jsoncpp/json/json.h"

#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

using namespace std;

CanSenderThread::CanSenderThread() {}
void displayCanFrame(struct can_frame &frame);

void CanSenderThread::run(void *contextSub, zmq::socket_t *socketReq)
{
    printf("start (in CanSenderThread::run)\n");

    // Connect with socket SUB with Sensing Process
    zmq::socket_t socketSub(*(zmq::context_t *)contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    printf("socket connected (in CanSenderThread::run)\n");

    int cnt = 0;
    while (1)
    { //!stop_flag){

        sensors::Can can;

        /* RECIEVE FROM SENSING PROCESS */
        zmq::message_t msgTopic = s_recv(socketSub);
        string topic = (const char *)msgTopic.data();
        printf("Recevied \"%s\"(in CanSenderThread::run)\n", topic.c_str());

        zmq::message_t msgData;
        socketSub.recv(&msgData);
        printf("Recevied (in CanSenderThread::run)\n");
        printf("~~~~~~~~~~~~~~~~ SIZE = %d ~~~~~~~~~~~~~~~~ \n", msgData.size());

        unsigned char data[msgData.size()] = "\0";
        can.ParseFromArray(msgData.data(), msgData.size());

        // CHECK THE CAN DATA
        std::printf("0x%03X [%d] ", can.can_id(), can.can_dlc());
        for(int i=0; i<can.can_dlc(); i++)
            std::printf("%02X ", can.data()[i]);
        std::printf("\r\n");
        
        /* DATA SERIALIZATION */

        /* SEND TO CLOUD SERVER */
        int data_len = can.ByteSize();
        unsigned char s_data[data_len] = "\0";
        can.SerializeToArray(s_data, data_len);
        // for (auto i = 0; i < data_len; i++)
        //     printf("%02X ", data[i]);
        // printf("\n");

        size_t size = data_len;
        zmq::message_t zmqDatas(size);
        // memcpy((void*)zmqDatas.data(), strMsg.c_str(), size);
        memcpy((void *)zmqDatas.data(), s_data, size);
        printf("Sending Can data ...\n");
        s_send(*socketReq, zmqDatas);
        printf("send complete!\n");

        /* OPTIONAL: DELETE ALL GLOBAL OBJECTS ALLOCATED BY LIBPROTOBUF */
        google::protobuf::ShutdownProtobufLibrary();

        /* RECEIVE FROM CLOUD SERVER PROCESS */
        zmq::message_t msgRecv = s_recv(*socketReq);
        printf("Reply:%s\n", msgRecv.data());
        printf("size=%d (Can:%d)\n", zmqDatas.size(), size);

        /* OPTIONS */
        cnt++;

    }

}