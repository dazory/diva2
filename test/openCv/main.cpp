#include "opencv2/opencv.hpp"
#include <iostream>  
#include "unistd.h"
  
using namespace cv;  
using namespace std;  
  
  
  
int main(int, char**)  
{  
    printf("main start!\n");

    VideoCapture cap(0);  
    if (!cap.isOpened())  
    {  
        printf("카메라를 열수 없습니다. \n");  
    }  
  
  
    Mat frame;  
    namedWindow("camera1", 1);  
    printf("frame generate\n");
  
    for (;;)  
    {  
  
        cap >> frame;  
        printf("cap>>frame\n");

        imshow("camera1", frame);  
        printf("imshow()!\n");
  
        // cv::Mat img;
        // img = cv::imread("/home/diva2/diva2/test/openCv/helloworld.png",CV_LOAD_IMAGE_UNCHANGED);
        // if (img.empty())
        // {
        //     cout << "can't find da file\n\n" ;
        // }
        // cv::namedWindow("test");
        // printf("namedWindow\n");
        // cv::imshow("test",img);
        // printf("imshow()2\n");
        waitKey(0);

        
        if (waitKey(20) >= 0) break;  

    }  
  
  
    return 0;  
}  