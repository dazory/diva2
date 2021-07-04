#pragma once
#include "LogStoringThread.h"
#include "FrameStoringThread.h"
#include "SceneStoringThread.h"
#include "LidarStoringThread.h"
#include "CamStoringThread.h"
#include "GpsStoringThread.h"
#include "ImuStoringThread.h"
#include "CanStoringThread.h"

#include <thread> 
#include <string>
using namespace std;

int main(int argc, char *argv[]){

    // LOG
    LogStoringThread mLogStoringThread;
    thread logThread(&LogStoringThread::run, &mLogStoringThread);
    logThread.join();

    // FRAME
    FrameStoringThread mFrameRawStoringThread;
    thread frameThread(&FrameStoringThread::run, &mFrameRawStoringThread);
    frameThread.join();

    // SCENE
    SceneStoringThread mSceneStoringThread;
    thread SceneThread(&SceneStoringThread::run, &mSceneStoringThread);
    SceneThread.join();

    // Lidar
    LidarStoringThread mLidarStoringThread;
    thread lidarThread(&LidarStoringThread::run, &mLidarStoringThread);
    lidarThread.join();

    // CAM
    CamStoringThread mCamStoringThread;
    thread camThread(&CamStoringThread::run, &mCamStoringThread);
    camThread.join();

    // GPS
    GpsStoringThread mGpsStoringThread;
    thread gpsThread(&GpsStoringThread::run, &mGpsStoringThread);
    gpsThread.join();

    // IMU
    ImuStoringThread mImuStoringThread;
    thread imuThread(&ImuStoringThread::run, &mImuStoringThread);
    imuThread.join();

    // CAN
    CanStoringThread mCanStoringThread;
    thread canThread(&CanStoringThread::run, &mCanStoringThread);
    canThread.join();
        
}