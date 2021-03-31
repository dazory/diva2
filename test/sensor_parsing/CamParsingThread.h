#pragma once
#include <zmq.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <fstream>
#include <thread>
#include <chrono>

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

using namespace std;

class CamParsingThread {
public:
CamParsingThread();
void run(void*);
void stop();
private:
cv::Mat mat;
bool stop_flag = false;

};
