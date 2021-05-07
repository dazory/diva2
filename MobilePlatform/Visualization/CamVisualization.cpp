#pragma once
#include "CamVisualization.h"

#include <fstream>

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

#include "../../service/Timestamp.h"
#include "../../service/global_name.hpp"
#include "../../protobuf/sensors.pb.h"

using namespace cv;
using namespace std;

CamVisualization::CamVisualization() {}

int protoTypeToCV(const sensors::ChannelOrder& proto_type);

void CamVisualization::run(void *contextSub)
{
    printf("[MobilePlatform/Sensing/CamVisualization] run\n");

    // [Connect with SUB socket]
    zmq::socket_t socketSub(*(zmq::context_t *)contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3);
    printf("[MobilePlatform/Sensing/CamVisualization] connect with SUB socket\n");

    // int cnt = 0;
    while (1)
    { 
        sensors::Cam cam;

        // [receive the topic from SUB socket]
        zmq::message_t msgTopic = s_recv(socketSub);
        string topic = (const char *)msgTopic.data();
        printf("[MobilePlatform/Sensing/CamVisualization] topic = %s\n", topic.c_str());

        // [receive the message_t from SUB socket]
        zmq::message_t msgData;
        socketSub.recv(&msgData);
        printf("[MobilePlatform/Sensing/CamVisualization] receive %dbytes\n",msgData.size());

        // [Parsing to proto]
        unsigned char data[msgData.size()] = "\0";
        cam.ParseFromArray(msgData.data(), msgData.size());

        // [CHECK THE IMAGE]
        // 참고: https://github.com/linklab-uva/deepracing/blob/adca1d1a724c4d930e3a5b905a039da5a143a561/data-logger/src/image_logging/utils/opencv_utils.cpp
        // cv::Mat frame;
        // frame.create(cam.rows(), cam.cols(), protoTypeToCV(cam.channel_order()));
        // memcpy((void *) frame.data, (void *)(&(cam.image_data()[0])), frame.step[0] * (size_t)frame.rows );
        // imshow("test", frame);
        // waitKey(0);
        
        // [OPTIONS]
        // <DELETE ALL GLOBAL OBJECTS ALLOCATED BY LIBPROTOBUF>
        google::protobuf::ShutdownProtobufLibrary();

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