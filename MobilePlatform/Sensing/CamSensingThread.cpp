#pragma once
#include "CamSensingThread.h"

sensors::ChannelOrder imTypeToProto(const int& cv_type);

CamSensingThread::CamSensingThread()
{
}

void CamSensingThread::run(zmq::socket_t *pubSock, mutex& m) // const int devicename, zmq::context_t *context,
{
  // <make txt file>
  fstream dataFile;
  dataFile.open("cam.txt", ios::out);

  // [Connect CAM device]
  int open;
  VideoCapture cap;
  if (USE_CAM == 1)
  {
    open = cap.open(2);
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
    cap.set(CV_CAP_PROP_FPS, 30);
    printf("[MobilePlatform/Sensing/CamSensingThread] Connect the CAM device\n");
  }

  clock_t clk_bef = clock(); 
  clock_t clk_now = clock();
  while (open)
  {
    if (USE_CAM == 1)
    {
      // [SENSING FROM CAMERA]
      sensors::Cam cam;
      Mat frame_org, frame;
      cap.read(frame_org);
      // resize(frame, frame, Size(320, 240));
      printf("[MobilePlatform/Sensing/CamSensingThread] read a frame (size:%dx%d, %d)\n",frame.cols, frame.rows, frame.type());
      
  
      if (!frame.empty())
      {
        // [Parsing to Proto]
        // sensors::ChannelOrder co = imTypeToProto(frame.type());
        // cam.set_channel_order(co);
        // <Set cols and rows>
        resize(frame_org, frame, Size(640, 360),0,0,CV_INTER_LINEAR);
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
        clk_now = clock();
        if((float)(clk_now - clk_bef)/CLOCKS_PER_SEC >= 0.1)
        {
          zmq::message_t zmqData(data_len);
          memcpy((void *)zmqData.data(), data, data_len);
          m.lock();
          s_send_idx(*pubSock, SENSOR_CAM);
          s_send(*pubSock, zmqData);
          m.unlock();
          printf("(%dms)[MobilePlatform/Sensing/CamSensingThread] complete to send (size=%d)\n",(float)(clk_now-clk_bef)/CLOCKS_PER_SEC*1000,zmqData.size());
          clk_bef = clk_now;
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
      // time_t curTime = time(NULL); 
      // struct tm *pLocal = localtime(&curTime);
      
      char cFn[50];
      char cSn[50];
      
      auto time = chrono::system_clock::now();
      auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
      long long currentTimeMillis = mill.count();
      int msc = currentTimeMillis % 1000;
      long nowTime = currentTimeMillis/1000;
      tm *ts = localtime(&nowTime);

      char cPath[15]; // sprintf(cPath, "cam");  
      sprintf(cPath, "CAM_%04d%02d%02d", ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday);
      
      int nResult = mkdir(cPath, 0776); 
      if( nResult == 0 ){
        printf("[MobilePlatform/Sensing/CamSensingThread] make directory (%s)\n", cPath);
      }// if(nResult == -1 ) : already exists

      sprintf(cFn, "%s%02d%02d%02d%03d.jpg", cPath,
      ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
      cv::imwrite(cFn, frame_org);
      printf("[MobilePlatform/Sensing/CamSensingThread] complete to save jpg file at \"%s\"\n", cFn);

      sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
      ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
      // <save txt file>
      dataFile<<cSn<<std::endl;

      // [Options]
      usleep(100);
      // sleep(1);

    } // end : if(USE_CAM)
  }// end : while(open)
  // <close txt file>
  dataFile.close();
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