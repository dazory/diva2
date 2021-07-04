#pragma once
// OpenCV
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

// #include <chrono>
#include <iostream> //I/O스트림 헤더
#include <string>//스트링 객체 사용 헤더
#include <list>//리스트 자료형 헤더
#include <vector>
#include <string>
#include <dirent.h>
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>

#include <algorithm>

#include <sys/time.h>


using namespace cv;
using namespace std;

class Module_Function
{
public:
    Module_Function(int sensorIdx, int algorithmIdx);
    // void laneDetection(int i, string videoFullName);
    void run();
    void model_run(string model_path, string weight_path, string dir);

    void setFileName(string fileName);
private:
    int sensorIdx;
    int algorithmIdx;

    string funcPath;
    string funcName;
    string fileName;

    clock_t clk_term;
    

    // string strDirPath;
    // vector<string> fileNames;
    // string strFileType;
    // string strExtension;
    // vector<Mat> images;

};