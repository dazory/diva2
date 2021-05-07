#pragma once
// OpenCV
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

#include "../../protobuf/sensors.pb.h"
#include "../../service/zmq_helper.h"

using namespace cv;
using namespace std;

extern int USE_CAM;

class CamSensingThread
{

public:
    CamSensingThread();
    static void run(zmq::socket_t *publisher); //const int devicename, zmq::context_t *context,
};

