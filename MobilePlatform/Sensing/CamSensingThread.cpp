#pragma once
#include "CamSensingThread.h"
#include <sys/time.h>

#define MILL 1000000

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
    //Resolution & frame rate
    open = cap->open(2);
    cap->set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    cap->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
    cap->set(CV_CAP_PROP_FPS, 15);
  }

  clock_t clk_bef = clock();
  clock_t clk_now = clock();
  
  while (open)
  {
    if (USE_CAM == 1)
    {
      // SENSING FROM CAMERA
      sensors::Cam cam;
      Mat frame, frame_org;
      cap->read(frame_org);

      // Downsize  
      resize(frame_org, frame, Size(640, 360), 0, 0, CV_INTER_LINEAR);

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

        // <Serialization>
        int data_len = cam.ByteSize();
        unsigned char data[data_len] = "\0";
        cam.SerializeToArray(data, data_len);

        // <Send Message>
        zmq::message_t zmqData(data_len);
        memcpy((void *)zmqData.data(), data, data_len);
        m.lock();
        s_send_idx(*pubSock, SENSOR_CAM);
        s_send(*pubSock, zmqData);
        m.unlock();
      } 

      char cFn[50];
      char cSn[50];

      auto time = chrono::system_clock::now();
      auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
      long long currentTimeMillis = mill.count();
      int msc = currentTimeMillis % 1000;
      long nowTime = currentTimeMillis / 1000;
      tm *ts = localtime(&nowTime);

      // save jpg & csv
      char cPath[50];
      sprintf(cPath, "/home/diva2/DIVA2_DATA/%s_0/CAM/JPG/CAM_%04d%02d%02d", timestamp.c_str(), ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday);
      sprintf(cFn, "%s%02d%02d%02d%03d.jpg", cPath,
              ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
      cv::imwrite(cFn, frame_org);
      sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
              ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
      dataFile << cSn << std::endl;

    }
  } 
  dataFile.close();
} 
