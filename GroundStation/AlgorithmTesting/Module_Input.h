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
// #include "global.h"

#include <algorithm>


using namespace cv;
using namespace std;

class Module_Input
{
public:
    Module_Input(int sensorType);
    void setSensorType(int sensorType);
    void setFileNamesWithDir(string strDirPath, string strExtension);
    void sortFileNames();
    
    void displayFileName();
    
    // CAM
    void setFiles();
    void setImages();

    string getDateNameFromDir();
    
    void displayImages();
    void image2video(string strFileName);
    void displayVideos(string strFileName);

private:
    int sensorType;
    string strDirPath;
    vector<string> fileNames;
    string strFileType;
    string strExtension;

    int fps;
    vector<Mat> images;
    
};