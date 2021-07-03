#pragma once
#include <iostream>
#include <zmq.hpp>

#include "Module_Input.h"
#include "Module_Function.h"
#include "global.h"
#include "../../protobuf/sensors.pb.h"

using namespace std;

static map<int, string> mLidar;
static map<int, string> mCam;
static map<int, string> mCan;
static map<int, string> mImu;
static map<int, string> mGps;
static vector<map<int,string>> mAlgorithms;

void setMSettings();

int main(int argc, char *argv[])
{
    // [Sensing Process]
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    socket.bind("tcp://*:9898");
    printf("[AlgorithmTesting/main] binding\n");
	/*
        argv[1] : sensorIdx
        argv[2] : algorithmIdx
        argv[3] : model_path
        argv[3] : weight_path
        argv[3] : fileDir 
    */

    printf("[AlgorithmTesting/main] start\n");
    // int sensorIdx = atoi(argv[1]);
    // int algorithmIdx = atoi(argv[2]);
    // string model_path = argv[3];
    // string weight_path = argv[4];
    // string fileDir = argv[5];

    // printf("   sensor: %d\n", sensorIdx);
    // printf("   algorithm: %d\n", algorithmIdx);
    // printf("   model_path: %s\n", model_path.c_str());
    // printf("   weight_path: %s\n", weight_path.c_str());
    // printf("   fileDir: %s\n", fileDir.c_str());

    // ==================================

    while(1)
    {
        // [ Load a Image ]
    Mat frame = imread("/home/diva2/diva2/GroundStation/AlgorithmTesting/test1.jpg", 1);
    resize(frame, frame, Size(640, 480));
    // [Parsing to Proto]
    sensors::algorithm_img algoImg;
    // <Set image data > - 참고: https://github.com/linklab-uva/deepracing/blob/adca1d1a724c4d930e3a5b905a039da5a143a561/data-logger/src/image_logging/utils/opencv_utils.cpp
    size_t totalsize = frame.step[0]*frame.rows;
    algoImg.mutable_image_original()->resize(totalsize);
    memcpy((void*)algoImg.mutable_image_original()->data(), (void*)frame.data, totalsize);
    printf("[GroundStation/AlgorithmTesting/main] set the algorithm Image message (size:%dx%d)\n",frame.cols, frame.rows); 

    Mat frame_result;
    frame.copyTo(frame_result);
    totalsize = frame_result.step[0]*frame_result.rows;
    algoImg.mutable_image_result()->resize(totalsize);
    memcpy((void*)algoImg.mutable_image_result()->data(), (void*)frame_result.data, totalsize);
    printf("[GroundStation/AlgorithmTesting/main] set the algorithm Image message (size:%dx%d)\n",frame_result.cols, frame_result.rows); 
    
    
    // [Send to PUB socket]
    // <Serialization>        
    int data_len = algoImg.ByteSize();
    unsigned char data[data_len] = "\0";
    algoImg.SerializeToArray(data, data_len);
    printf("[GroundStation/AlgorithmTesting/main] complete to serialize (size=%d)\n",data_len);
                
    // <Send>
    // <Send Message>
    zmq::message_t zmqData(data_len);
    memcpy((void *)zmqData.data(), data, data_len);

    // string topic = "ALGO";
    // size_t size_topic = topic.size() + 1;
    // zmq::message_t zmqIdx(size_topic);
    // memcpy(zmqIdx.data(), topic.c_str(), size_topic);
    // int rc = socket.send(zmqIdx, ZMQ_SNDMORE);

    socket.send(zmqData, 0);
    printf("[GroundStation/AlgorithmTesting/main] complete to send (size=%d)\n",zmqData.size());

    // usleep(100000);
    sleep(1);
    }
    
    // ==================================

    /*
    // int sensorIdx = SensorIdx::cam;
    // int algorithmIdx = 1;
    // string fileDir = "";
    
	
    Module_Input moduleInput(sensorIdx);
    // moduleInput.setFileNamesWithDir(fileDir.c_str(), ".jpg");
    // moduleInput.sortFileNames();
    // moduleInput.displayFileName();

    // ***  /home/diva2/diva2/build/MobilePlatform/Sensing/2021-05-22/CAM/
    // string outputFileName = moduleInput.getDateNameFromDir() + ".mp4";
    // moduleInput.setFiles();
    // moduleInput.image2video(outputFileName.c_str()); // /home/diva2/diva2/build/GroundStation/AlgorithmTesting/CAM/hello.mp4");
    // string fileName = "/home/diva2/diva2/build/GroundStation/AlgorithmTesting/"+outputFileName;
    // moduleInput.displayVideos(fileName);

    setMSettings();
    Module_Function moduleFunction(sensorIdx, algorithmIdx);
    // fileName = "/home/diva2/diva2/build/GroundStation/AlgorithmTesting/testvideo2.mp4";
    // moduleFunction.setFileName(fileName);
    moduleFunction.run();
    
    // string model_path = "./checkpoints/fcn_big_01.json";
    // string weight_path = "./checkpoints/fcn_big_01.h5";
    moduleFunction.model_run(model_path, weight_path, fileDir);
    
    // moduleFunction.laneDetection(0, "/home/diva2/diva2/test/lane_detection/project_video.mp4");
    // moduleFunction.laneDetection(0, fileDir.c_str());
    // moduleFunction.laneDetection(1, "/home/diva2/diva2/build/GroundStation/AlgorithmTesting/testvideo2.mp4");
    // moduleFunction.laneDetection("/home/diva2/diva2/test/lane_detection/project_video.mp4");
    return 0;
    */
}

void setMSettings(){
    // cam
    mCam.insert(make_pair(0, "Lane Detection"));
    mCam.insert(make_pair(1, "Object Detection"));

    mAlgorithms.push_back(mLidar);
    mAlgorithms.push_back(mCam);
    mAlgorithms.push_back(mCan);
    mAlgorithms.push_back(mImu);
    mAlgorithms.push_back(mGps);
}