#pragma once
#include <zmq.hpp>

#include <thread> 
#include <string>

#include "../../service/global_name.hpp"

using namespace std;

int USE_GPS =0; int USE_IMU =0; int USE_CAM =0; int USE_LIDAR =0; int USE_CAN =0;

int main(int argc, char *argv[]){
    
    // SUB
    zmq::context_t contextSub(1);
    printf("sub context generated (in main)\n");

    // [press the playback button in Qt]

    // [Get log from DB]

    // [Select a scene]

    // [Get zip file from Cloud Server]

    // [Playback]
    
}