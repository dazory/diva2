#pragma once
#include "Module_Input_CAM.h"

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
#include "global.h"

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
    // string getVideoFullName(){ printf("[Module_Input::getVideoFullName] start\n"); return cam.getVideoFullName();}
    // Module_Input_CAM *getCAM(){return &cam;}
    // void setVideoFullName(string strFullName) {this->cam.setVideoFullName(strFullName);}
    void setFiles();
        void setImages();

    // void setFps(int fps){this->fps = fps;}
    string getDateNameFromDir();
    
    void displayImages();
    // vector<Mat> getImages();
    void image2video(string strFileName);
    void displayVideos(string strFileName);

private:
    int sensorType;
    string strDirPath;
    vector<string> fileNames;
    string strFileType;
    string strExtension;

    // Module_Input_CAM cam;
    int fps;
    vector<Mat> images;
    
};