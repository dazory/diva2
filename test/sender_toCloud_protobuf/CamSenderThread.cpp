#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

#include "CamSenderThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include "../protobuf/sensors.pb.h"
#include <fstream>
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

using namespace cv;
using namespace std;

CamSenderThread::CamSenderThread() {}

int protoTypeToCV(const sensors::ChannelOrder& proto_type);

void CamSenderThread::run(void *contextSub, zmq::socket_t *socketReq)
{
    printf("start (in CamSenderThread::run)\n");

    // Connect with socket SUB with Sensing Process
    zmq::socket_t socketSub(*(zmq::context_t *)contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3);
    printf("socket connected (in CamSenderThread::run)\n");

    int cnt = 0;
    while (1)
    { //!stop_flag){

        sensors::Cam cam;

        /* RECIEVE FROM SENSING PROCESS */
        zmq::message_t msgTopic = s_recv(socketSub);
        string topic = (const char *)msgTopic.data();
        printf("Recevied \"%s\"(in CamSenderThread::run)\n", topic.c_str());

        zmq::message_t msgData;
        socketSub.recv(&msgData);
        printf("Recevied (in CamSenderThread::run)\n");
        printf("~~~~~~~~~~~~~~~~ SIZE = %d ~~~~~~~~~~~~~~~~ \n", msgData.size());

        unsigned char data[msgData.size()] = "\0";
        cam.ParseFromArray(msgData.data(), msgData.size());

        /*
        // CHECK THE IMAGE - 참고: https://github.com/linklab-uva/deepracing/blob/adca1d1a724c4d930e3a5b905a039da5a143a561/data-logger/src/image_logging/utils/opencv_utils.cpp
        cv::Mat frame;
        frame.create(cam.rows(), cam.cols(), protoTypeToCV(cam.channel_order()));
        memcpy((void *) frame.data, (void *)(&(cam.image_data()[0])), frame.step[0] * (size_t)frame.rows );
        
        imshow("test", frame);
        waitKey(0);
        */

        // /* SEND TO CLOUD SERVER */
        // size_t data_len = cam.ByteSize();
        // unsigned char data[data_len] = "\0";
        // cam.SerializeToArray(data, data_len);
        // // for (auto i = 0; i < data_len; i++)
        // //     printf("%02X ", data[i]);
        // // printf("\n");

        // size_t size = data_len;
        // zmq::message_t zmqDatas(size);
        // // memcpy((void*)zmqDatas.data(), strMsg.c_str(), size);
        // memcpy((void *)zmqDatas.data(), data, size);
        // printf("Sending Cam data ...\n");
        // s_send(*socketReq, zmqDatas);
        // printf("send complete!\n");

        // /* OPTIONAL: DELETE ALL GLOBAL OBJECTS ALLOCATED BY LIBPROTOBUF */
        // google::protobuf::ShutdownProtobufLibrary();

        // /* RECEIVE FROM CLOUD SERVER PROCESS */
        // zmq::message_t msgRecv = s_recv(*socketReq);
        // printf("Reply:%s\n", msgRecv.data());
        // printf("size=%d (Cam:%d)\n", zmqDatas.size(), size);

        // /* OPTIONS */
        // cnt++;
    }

}

int protoTypeToCV(const sensors::ChannelOrder& proto_type)
{
  switch(proto_type)
  {
  case sensors::ChannelOrder::BGR:
  {
    return CV_8UC3;
  }
  case sensors::ChannelOrder::BGRA:
  {
    return CV_8UC4;
  }
  case sensors::ChannelOrder::GRAYSCALE:
  {
    return CV_8U;
  }
  default:
  {
    std::string err = "Unsupported image type: " + google::protobuf::GetEnumDescriptor< sensors::ChannelOrder >()->value(proto_type)->name();
    std::cerr << err << std::endl;
    throw std::runtime_error(err);
  }

  }
}