#pragma once
#include "CamSensingThread.h"

sensors::ChannelOrder imTypeToProto(const int& cv_type);


CamSensingThread::CamSensingThread()
{
}

void CamSensingThread::run(zmq::socket_t *pubSock) // const int devicename, zmq::context_t *context,
{
  // [Connect CAM device]
  int open;
  VideoCapture cap;
  if (USE_CAM == 1)
  {
    open = cap.open(0);
    printf("[MobilePlatform/Sensing/CamSensingThread] Connect the CAM device\n");
  }

  time_t time_bef = time(NULL); 
  time_t time_now = time(NULL);
  while (open)
  {
    time_now = time(NULL);
    if (USE_CAM == 1)
    {
      // [SENSING FROM CAMERA]
      sensors::Cam cam;
      Mat frame;
      cap.read(frame);
      // resize(frame, frame, Size(320, 240));
      printf("[MobilePlatform/Sensing/CamSensingThread] read a frame (size:%dx%d, %d)\n",frame.cols, frame.rows, frame.type());
  
      if (!frame.empty())
      {
        // [Parsing to Proto]
        // sensors::ChannelOrder co = imTypeToProto(frame.type());
        // cam.set_channel_order(co);
        // <Set cols and rows>
        cam.set_cols(frame.cols);
        cam.set_rows(frame.rows);
        
        // <Set image data>
        // 참고: https://github.com/linklab-uva/deepracing/blob/adca1d1a724c4d930e3a5b905a039da5a143a561/data-logger/src/image_logging/utils/opencv_utils.cpp
        size_t totalsize = frame.step[0]*frame.rows;
        cam.mutable_image_data()->resize(totalsize);
        memcpy((void*)cam.mutable_image_data()->data(), (void*)frame.data, totalsize);
        printf("[MobilePlatform/Sensing/CamSensingThread] set the CAM message (size:%dx%d)\n",cam.cols(), cam.rows()); //, cam.channel_order());


        // [Send to PUB socket]
        // <Serialization>        
        int data_len = cam.ByteSize();
        unsigned char data[data_len] = "\0";
        cam.SerializeToArray(data, data_len);
        printf("[MobilePlatform/Sensing/CamSensingThread] complete to serialize (size=%d)\n",data_len);
                
        // <Send>
        // <Send Message>
        if(time_now - time_bef >= 1)
        {
          zmq::message_t zmqData(data_len);
          memcpy((void *)zmqData.data(), data, data_len);
          s_send_idx(*pubSock, SENSOR_CAM);
          s_send(*pubSock, zmqData);
          printf("[MobilePlatform/Sensing/CamSensingThread] complete to send (size=%d)\n",zmqData.size());
                
          time_bef = time_now;
        }
        
      }// end : if (!frame.empty())

      // [Store the CAM data]
      // <Make json object>
      Json::Value json_dataset;
      string path = "cam.json"; // TO-DO: the rule of file name
      ifstream in(path.c_str());
      if(in.is_open()) in >> json_dataset;
      printf("[MobilePlatform/Sensing/CamSensingThread] Make Json Object (path:%s)\n",path.c_str()); 

      Json::Value json_data; 
      // json_data["latitude"] = strBuff[2]; 
      json_dataset.append(json_data);
      printf("[MobilePlatform/Sensing/CamSensingThread] Append a json data\n");

      Json::StyledWriter jsonWriter;
      ofstream out(path.c_str());
      out<<jsonWriter.write(json_dataset);
      out.close();
      printf("[MobilePlatform/Sensing/CamSensingThread] complete to make json file at \"%s\"\n",path.c_str());
      

      // <Make JPG file> 
      time_t curTime = time(NULL); 
      struct tm *pLocal = localtime(&curTime); 
      char cPath[10]; sprintf(cPath, "cam");  
      int nResult = mkdir(cPath, 0776); 
      if( nResult == 0 ){
        printf("[MobilePlatform/Sensing/CamSensingThread] make directory (%s)\n", cPath);
      }// if(nResult == -1 ) : already exists

      char cFn[50];
      sprintf(cFn, "%s/%04d-%02d-%02dT%02d-%02d-%02d.jpg", cPath,
      pLocal->tm_year + 1900, pLocal->tm_mon + 1, pLocal->tm_mday,  
      pLocal->tm_hour, pLocal->tm_min, pLocal->tm_sec);
      cv::imwrite(cFn, frame);
      printf("[MobilePlatform/Sensing/CamSensingThread] complete to save jpg file at \"%s\"\n", cFn);

      // [Options]
      usleep(100);
      // sleep(1);

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