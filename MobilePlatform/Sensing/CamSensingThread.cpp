#pragma once
#include "CamSensingThread.h"

sensors::ChannelOrder imTypeToProto(const int& cv_type);


CamSensingThread::CamSensingThread()
{
}

void CamSensingThread::run(zmq::socket_t *publisher) // const int devicename, zmq::context_t *context,
{
    // [Connect CAM device]
    int open;
    VideoCapture cap;
    if (USE_CAM == 1)
    {
        open = cap.open(0);
        printf("[MobilePlatform/Sensing/CamSensingThread] Connect the CAM device\n");
    }

    while (open)
    {
        if (USE_CAM == 1)
        {
            // [Send Topic]
            s_send_idx(*publisher, SENSOR_CAM);
        
            // [SENSING FROM CAMERA]
            sensors::Cam cam;
            Mat frame;
            cap.read(frame);
            // resize(frame, frame, Size(320, 240));
            printf("[MobilePlatform/Sensing/CamSensingThread] read a frame (size:%dx%d, %d)\n",frame.cols, frame.rows, frame.type());
            

            if (!frame.empty())
            {
                // [Parsing to Proto]
                sensors::ChannelOrder co = imTypeToProto(frame.type());
                cam.set_channel_order(co);
                cam.set_cols(frame.cols);
                cam.set_rows(frame.rows);

                // 참고: https://github.com/linklab-uva/deepracing/blob/adca1d1a724c4d930e3a5b905a039da5a143a561/data-logger/src/image_logging/utils/opencv_utils.cpp
                size_t totalsize = frame.step[0]*frame.rows;
                cam.mutable_image_data()->resize(totalsize);
                memcpy((void*)cam.mutable_image_data()->data(), (void*)frame.data, totalsize);
                printf("[MobilePlatform/Sensing/CamSensingThread] set the CAM message (size:%dx%d, %d)\n",cam.cols(), cam.rows(), cam.channel_order());

                // [Send to PUB socket]
                // <Serialization>        
                int data_len = cam.ByteSize();
                unsigned char data[data_len] = "\0";
                cam.SerializeToArray(data, data_len);
                printf("[MobilePlatform/Sensing/CamSensingThread] complete to serialize (size=%d)\n",data_len);
                
                // <Send>
                zmq::message_t zmqData(data_len);
                memcpy((void *)zmqData.data(), data, data_len);
                s_send(*publisher, zmqData);
                printf("[MobilePlatform/Sensing/CamSensingThread] complete to send (size=%d)\n",zmqData.size());
            }

            // [Options]
            sleep(1);
        } // end : if(USE_CAM)
    }// end : while(open)
}// end : CamSensingThread::run


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