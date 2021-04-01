//#pragma once
#ifndef CAMSENSING_H_
#define CAMSENSING_H_

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <stdint.h>
#include <iostream>
#include "../service/Timestamp.h"
using namespace cv;
using namespace std;
class CamSensing
{
    public:

    CamSensing();
    VideoCapture cap;
    Mat frame;
    vector<int> Compression_params;
    bool initialize(const int devicename); //0
    //bool initialize(const char *devicename); // /dev/tty/ACM0
    string dir;
    string path;
    Timestamp ts;
    private:
};

#endif //CAMSENSING_H_