#pragma once
#include <string>
#include <iostream>
#include "LiDAR_Sensing.h"
#include "../../service/Timestamp.h"
#include <pcl/PCLPointCloud2.h>

extern int USE_LiDAR;

class LiDAR_SensingThread{
    public:
    LiDAR_SensingThread(){};
    static void run(zmq::socket_t *socket, mutex &m, float leaf_size);
};

// class LiDAR_SensingThread{
//     public:
//     LiDAR_SensingThread(){};
//     static void run(void *context, mutex &m, float leaf_size);
// };