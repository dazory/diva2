#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <sstream>
#include <time.h>
#include "unistd.h"
#include <sys/timeb.h>
#include <cstddef>

#include "CamSensing.cpp"
#include "../protobuf/sensors.pb.h"
#include "../service/zmq_helper.h"

using namespace cv;
using namespace std;

extern int USE_CAM;

sensors::ChannelOrder imTypeToProto(const int& cv_type);

class CamSensingThread
{

public:
    CamSensingThread();
    static void run(zmq::socket_t *publisher); //const int devicename, zmq::context_t *context,
};

CamSensingThread::CamSensingThread()
{
}

void CamSensingThread::run(zmq::socket_t *publisher) // const int devicename, zmq::context_t *context,
{

    // CamSensing camThread;
    int open;
    VideoCapture cap;
    if (USE_CAM == 1)
    {
        open = cap.open(0); //camThread.initialize(0);
        printf("cam open[%d] (in CamSensingThread::run())\n");
    }

    vector<uchar> buffer;
    while (open)
    {
        s_send_idx(*publisher, SENSOR_CAM);
        printf("sendmore: CAM (in CamSensingThread::run())\n");

        sensors::Cam cam;
        if (USE_CAM == 1)
        {

            /* SENSING FROM CAMERA */
            Mat frame;
            cap.read(frame);
            printf("read cap (in CamPacket::read())\n");
            // resize(frame, frame, Size(320, 240));
            // imshow("hello",frame);
            // waitKey(0);

            //jpg로 인코딩해서 버퍼에 담은 다음 전송
            // vector<int> param = vector<int>(2);
            // param[0] = CV_IMWRITE_JPEG_QUALITY;
            // param[1] = 95;

            if (!frame.empty())
            {
                sensors::ChannelOrder co = imTypeToProto(frame.type());
                cam.set_channel_order(co);
                cam.set_cols(frame.cols);
                cam.set_rows(frame.rows);
                printf("READ) width=%d, height=%d, type=%d\n", cam.cols(), cam.rows(), cam.channel_order());

                int size = frame.total() * frame.elemSize();
                size = frame.step[0] * frame.rows;
               
                // 참고: https://github.com/linklab-uva/deepracing/blob/adca1d1a724c4d930e3a5b905a039da5a143a561/data-logger/src/image_logging/utils/opencv_utils.cpp
                size_t totalsize = frame.step[0]*frame.rows;
                printf("totalsize= %d\n", totalsize);
                cam.mutable_image_data()->resize(totalsize);
                memcpy((void*)cam.mutable_image_data()->data(), (void*)frame.data, totalsize);
                
                /* SEND TO CLOUD WITH DATA SERIALIZATION */
                printf("start SerializeToArray\n");
                int data_len = cam.ByteSize();
                unsigned char data[data_len] = "\0";
                cam.SerializeToArray(data, data_len);
                printf("end SerializeToArray\n");
                // for (auto i = 0; i < data_len; i++)
                //     printf("%02X ", data[i]);
                // printf("\n");

                zmq::message_t zmqData(data_len);
                memcpy((void *)zmqData.data(), data, data_len);
                s_send(*publisher, zmqData);
                printf("send complete! [size=%d] (in CamSensingThread::run/while(1))\n", data_len);
            }

            sleep(1);
        }
    }
}


sensors::ChannelOrder imTypeToProto(const int& cv_type)
{
  switch (cv_type){
  case CV_8U:{
    return sensors::ChannelOrder::GRAYSCALE;
  }
  case CV_8UC4:{
    return sensors::ChannelOrder::BGRA;
  }
  case CV_8UC3:{
    return sensors::ChannelOrder::BGR;
  }
  default:{
    std::string err = "Unsupported image type: " + std::to_string(cv_type);
    std::cerr << err << std::endl;
    throw std::runtime_error(err);
  }
  }
}