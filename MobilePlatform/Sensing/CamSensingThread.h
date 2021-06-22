#pragma once
// OpenCV
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

#include <chrono>
#include <iostream>
#include <sstream>
#include <time.h>
#include "unistd.h"
#include <sys/timeb.h>
#include <cstddef>
#include <sys/stat.h> // mkdir
#include <sys/types.h>
#include <errno.h>		//errno
#include <mutex>

#include "../../protobuf/sensors.pb.h"
#include "../../service/zmq_helper.h"
#include "../../service/Timestamp.h"

// JSON
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

// #include "boost/"

using namespace cv;
using namespace std;

extern int USE_CAM;

class CamSensingThread
{

public:
    CamSensingThread();
    static void run(zmq::socket_t *publisher, mutex &m, string dir); //const int devicename, zmq::context_t *context,
};

// class CamSensingThread
// {
// public:
//     CamSensingThread();
//     static void run(void *context, mutex &m, string dir); //const int devicename, zmq::context_t *context,
// };