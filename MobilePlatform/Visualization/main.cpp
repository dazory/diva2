#pragma once
#include "GpsVisualization.h"
#include "CamVisualization.h"
#include "ImuVisualization.h"
#include "CanVisualization.h"

#include <thread> 
#include <string>

#include "../../service/global_name.hpp"

using namespace std;

int USE_GPS =0; int USE_IMU =0; int USE_CAM =0; int USE_LIDAR =0; int USE_CAN =0;

int main(int argc, char *argv[]){
    
    // SUB
    zmq::context_t contextSub(1);
    printf("sub context generated (in main)\n");

    // GPS
    GpsVisualization mGpsVisualization;
    thread gpsVisualizationThread(&GpsVisualization::run, &mGpsVisualization, &contextSub);
    
    // CAM
    CamVisualization mCamVisualization;
    thread camVisualizationThread(&CamVisualization::run, &mCamVisualization, &contextSub);
    
    // IMU
    ImuVisualization mImuVisualization;
    thread imuVisualizationThread(&ImuVisualization::run, &mImuVisualization, &contextSub);

    // CAM
    CanVisualization mCanVisualization;
    thread canVisualizationThread(&CanVisualization::run, &mCanVisualization, &contextSub);
    
    gpsVisualizationThread.join();
    camVisualizationThread.join();
    imuVisualizationThread.join();
    canVisualizationThread.join();
    
}