// data_format/gps_packet.h
#pragma once
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

class CamPacket {
public:
    CamPacket();
    
    /* DATA */ 
    time_t time;
    Mat image;
    // vector<uchar> img_buff;
    int rows, cols, type;


	/* FUNCTION */
    void display();
    void read(VideoCapture cap);
    int getSizeofImage();
    CamPacket getCamPacket(zmq::message_t zmqData);
private:

};

CamPacket::CamPacket(){
    image = Mat();
    time = 0;
    rows=0; cols=0; type=0;
}

CamPacket CamPacket::getCamPacket(zmq::message_t zmqData){

}

void CamPacket::display(){
    struct tm *tm = localtime(&time);
    char buffer[32];
	std::strftime(buffer, 32, "%H:%M:%S", tm);  
	printf("time = %s\n", buffer);
    
    // cols=640; rows=480;
    printf("DISPLAY) cols=%d, rows=%d\n",cols, rows);
    if(!image.empty()){
        // image = imdecode(Mat(img_buff),CV_LOAD_IMAGE_COLOR);
        printf("Decoding complete!\n");
        imshow("display",image);
        waitKey(0);
    }else {printf("EMPTY IMAGE\n");}
}

void CamPacket::read(VideoCapture cap){    
    Mat frame;
    cap.read(frame);
    printf("read cap (in CamPacket::read())\n");

    // cols = frame.cols;
    // rows = frame.rows;
    // type = frame.type();

    //jpg로 인코딩해서 버퍼에 담은 다음 전송
    vector<int> param = vector<int>(2);
    param[0] = CV_IMWRITE_JPEG_QUALITY;
    param[1] = 95;
    // frame.copyTo(image);
    //imencode(".jpg", frame);
    // imshow("display",frame);
    // waitKey(0);

    vector<uchar> img_buff;
    if (!frame.empty()) {
        cols = frame.cols; rows=frame.rows; type=frame.type();
        printf("READ) cols=%d, rows=%d\n",cols, rows);
        vector<int> param(2);
        param[0] = CV_IMWRITE_JPEG_QUALITY;
        param[1] = 95;
        imencode(".jpg", frame, img_buff, param);
        image = imdecode(Mat(img_buff),CV_LOAD_IMAGE_COLOR);
        printf("Encoding complete!\n");
    }
}

int CamPacket::getSizeofImage(){
    return image.total()*image.elemSize();
}