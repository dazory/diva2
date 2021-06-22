#pragma once
#include "CamSensingThread.h"
#include <sys/time.h>

#define MILL 1000000

sensors::ChannelOrder imTypeToProto(const int &cv_type);

CamSensingThread::CamSensingThread()
{
}

void CamSensingThread::run(zmq::socket_t *pubSock, mutex &m, string dir) // const int devicename, zmq::context_t *context,
{
  Timestamp ts;

  time_t system_time;
  struct tm* systime;
  system_time = time(NULL);
  systime = localtime(&system_time);

  string tm_year = to_string(systime->tm_year + 1900);
  string tm_month = to_string(systime->tm_mon+1);
  string tm_date = to_string(systime->tm_mday);
  if(tm_date.size() == 1){
      tm_date = "0"+tm_date;
  }

  string timestamp;
  timestamp = tm_year + tm_month + tm_date;

  // <make csv file>
  string path = "/home/diva2/DIVA2_DATA/"+timestamp+"_0/CAM/i30_CAM_" + ts.getMilliTime() + ".csv";
  fstream dataFile;
  dataFile.open(path, ios::out);

  // [Connect CAM device]
  int open;
  VideoCapture *cap = new VideoCapture(CAP_DSHOW);

  if (USE_CAM == 1)
  {
    open = cap->open(2);
    cap->set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    cap->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
    cap->set(CV_CAP_PROP_FPS, 15);
    //printf("[MobilePlatform/Sensing/CamSensingThread] Connect the CAM device\n");
  }

  clock_t clk_bef = clock();
  clock_t clk_now = clock();
  
  while (open)
  {
    if (USE_CAM == 1)
    {
      // [SENSING FROM CAMERA]
      sensors::Cam cam;
      Mat frame, frame_org;
      cap->read(frame_org);

      resize(frame_org, frame, Size(640, 360), 0, 0, CV_INTER_LINEAR);

      // resize(frame, frame, Size(320, 240));
      //printf("[MobilePlatform/Sensing/CamSensingThread] read a frame (size:%dx%d, %d)\n", frame.cols, frame.rows, frame.type());

      if (!frame.empty())
      {
        // < timestamp >
        struct timeval tv;
        gettimeofday(&tv, NULL);
        cam.set_timestamp((tv.tv_sec * MILL) + (tv.tv_usec));

        cam.set_cols(frame.cols);
        cam.set_rows(frame.rows);

        vector<uchar> buffer;
        imencode(".jpg", frame, buffer);
        size_t totalsize = buffer.size();
        cam.mutable_image_data()->resize(totalsize);
        memcpy((void *)cam.mutable_image_data()->data(), (void *)buffer.data(), totalsize);
        //printf("[MobilePlatform/Sensing/CamSensingThread] set the CAM message (size:%dx%d)\n", cam.cols(), cam.rows()); //, cam.channel_order());

        // [Send to PUB socket]
        // <Serialization>
        int data_len = cam.ByteSize();
        unsigned char data[data_len] = "\0";
        cam.SerializeToArray(data, data_len);
        //printf("[MobilePlatform/Sensing/CamSensingThread] complete to serialize (size=%d)\n", data_len);

        // <Send>
        // <Send Message>
        clk_now = clock();
        zmq::message_t zmqData(data_len);
        memcpy((void *)zmqData.data(), data, data_len);
        m.lock();
        s_send_idx(*pubSock, SENSOR_CAM);
        s_send(*pubSock, zmqData);
        m.unlock();
        //printf("(%dms)[MobilePlatform/Sensing/CamSensingThread] complete to send (size=%d)\n", (float)(clk_now - clk_bef) / CLOCKS_PER_SEC * 1000, zmqData.size());
        clk_bef = clk_now;

      } // end : if (!frame.empty())

      char cFn[50];
      char cSn[50];

      auto time = chrono::system_clock::now();
      auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
      long long currentTimeMillis = mill.count();
      int msc = currentTimeMillis % 1000;
      long nowTime = currentTimeMillis / 1000;
      tm *ts = localtime(&nowTime);

      char cPath[15];
      sprintf(cPath, "/home/diva2/DIVA2_DATA/%s_0/CAM/JPG/CAM_%04d%02d%02d", timestamp.c_str(), ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday);
      // string cPath = "/home/diva2/DIVA2data/"+timestamp+"_0/CAM/JPG/CAM_%04d%02d%02d", ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday);

      // int nResult = mkdir(cPath, 0776);
      // if (nResult == 0)
      // {
      //   printf("[MobilePlatform/Sensing/CamSensingThread] make directory (%s)\n", cPath);
      // } // if(nResult == -1 ) : already exists

      sprintf(cFn, "%s%02d%02d%02d%03d.jpg", cPath,
              ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
      cv::imwrite(cFn, frame_org);
      printf("[MobilePlatform/Sensing/CamSensingThread] complete to save jpg file at \"%s\"\n", cFn);

      sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
              ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
      // <save txt file>
      dataFile << cSn << std::endl;

      usleep(10);
      // sleep(1);

    } // end : if(USE_CAM)
  }   // end : while(open)
  // <close txt file>
  dataFile.close();
} // end : CamSensingThread::run

sensors::ChannelOrder imTypeToProto(const int &cv_type)
{
  switch (cv_type)
  {
  case CV_8U:
  {
    return sensors::ChannelOrder::GRAYSCALE;
  }
  case CV_8UC4:
  {
    return sensors::ChannelOrder::BGRA;
  }
  case CV_8UC3:
  {
    return sensors::ChannelOrder::BGR;
  }
  default:
  {
    std::string err = "Unsupported image type: " + std::to_string(cv_type);
    std::cerr << err << std::endl;
    throw std::runtime_error(err);
  }
  }
}



// void CamSensingThread::run(void *context, mutex &m, string dir) // const int devicename, zmq::context_t *context,
// {
//   zmq::socket_t socketCam(*(zmq::context_t*)context, ZMQ_PUB);
//   socketCam.bind(protocol::SENSING_PUB);
//   socketCam.connect("tcp://165.246.39.124:5560");
    
//   Timestamp ts;
//   // <make csv file>
//   string path = "/home/diva2/DIVAdata/"+dir+"/CAM/i30_CAM_ts_" + ts.getMilliTime() + ".csv";
//   fstream dataFile;
//   dataFile.open("cam.csv", ios::out);

//   // [Connect CAM device]
//   int open;
//   VideoCapture *cap = new VideoCapture(CAP_DSHOW);

//   if (USE_CAM == 1)
//   {
//     open = cap->open(0);
//     cap->set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
//     cap->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
//     cap->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
//     cap->set(CV_CAP_PROP_FPS, 30);
//     printf("[MobilePlatform/Sensing/CamSensingThread] Connect the CAM device\n");
//   }

//   clock_t clk_bef = clock();
//   clock_t clk_now = clock();
  
//   while (open)
//   {
//     if (USE_CAM == 1)
//     {
//       // [SENSING FROM CAMERA]
//       sensors::Cam cam;
//       Mat frame, frame_org;
//       cap->read(frame_org);

//       resize(frame_org, frame, Size(640, 360), 0, 0, CV_INTER_LINEAR);

//       // resize(frame, frame, Size(320, 240));
//       printf("[MobilePlatform/Sensing/CamSensingThread] read a frame (size:%dx%d, %d)\n", frame.cols, frame.rows, frame.type());

//       if (!frame.empty())
//       {
//         // < timestamp >
//         struct timeval tv;
//         gettimeofday(&tv, NULL);
//         cam.set_timestamp((tv.tv_sec * MILL) + (tv.tv_usec));

//         cam.set_cols(frame.cols);
//         cam.set_rows(frame.rows);

//         vector<uchar> buffer;
//         imencode(".jpg", frame, buffer);
//         size_t totalsize = buffer.size();
//         cam.mutable_image_data()->resize(totalsize);
//         memcpy((void *)cam.mutable_image_data()->data(), (void *)buffer.data(), totalsize);
//         printf("[MobilePlatform/Sensing/CamSensingThread] set the CAM message (size:%dx%d)\n", cam.cols(), cam.rows()); //, cam.channel_order());

//         // [Send to PUB socket]
//         // <Serialization>
//         int data_len = cam.ByteSize();
//         unsigned char data[data_len] = "\0";
//         cam.SerializeToArray(data, data_len);
//         printf("[MobilePlatform/Sensing/CamSensingThread] complete to serialize (size=%d)\n", data_len);

//         // <Send>
//         // <Send Message>
//         clk_now = clock();
//         zmq::message_t zmqData(data_len);
//         memcpy((void *)zmqData.data(), data, data_len);
//         m.lock();
//         s_send_idx(socketCam, SENSOR_CAM);
//         s_send(socketCam, zmqData);
//         m.unlock();
//         printf("(%dms)[MobilePlatform/Sensing/CamSensingThread] complete to send (size=%d)\n", (float)(clk_now - clk_bef) / CLOCKS_PER_SEC * 1000, zmqData.size());
//         clk_bef = clk_now;

//       } // end : if (!frame.empty())

//       char cFn[50];
//       char cSn[50];

//       auto time = chrono::system_clock::now();
//       auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
//       long long currentTimeMillis = mill.count();
//       int msc = currentTimeMillis % 1000;
//       long nowTime = currentTimeMillis / 1000;
//       tm *ts = localtime(&nowTime);

//       char cPath[15]; // sprintf(cPath, "cam");
//       sprintf(cPath, "CAM_%04d%02d%02d", ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday);

//       int nResult = mkdir(cPath, 0776);
//       if (nResult == 0)
//       {
//         printf("[MobilePlatform/Sensing/CamSensingThread] make directory (%s)\n", cPath);
//       } // if(nResult == -1 ) : already exists

//       sprintf(cFn, "%s%02d%02d%02d%03d.jpg", cPath,
//               ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
//       cv::imwrite(cFn, frame_org);
//       printf("[MobilePlatform/Sensing/CamSensingThread] complete to save jpg file at \"%s\"\n", cFn);

//       sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
//               ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
//       // <save txt file>
//       dataFile << cSn << std::endl;

//       usleep(10);
//       // sleep(1);

//     } // end : if(USE_CAM)
//   }   // end : while(open)
//   // <close txt file>
//   dataFile.close();
// } // end : CamSensingThread::run