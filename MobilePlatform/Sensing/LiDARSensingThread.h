#ifndef LIDARSENSINGTHREAD_H_
#define LIDARSENSINGTHREAD_H_

#include <unistd.h>
#include <atomic>
#include <cmath>
#include <csignal>
#include <cstdlib>
#include <chrono>

#include <Eigen/Eigen>
#include <fstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <zmq.hpp>
#include "../../service/zmq_helper.h"

#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>
#include <pcl/filters/voxel_grid.h>

#include "jsoncpp/json/json.h"

// #include "../service/ouster/os1.h" //old ouster exmaple
#include "../../service/ouster/os1_packet.h"
#include "../../service/ouster/os1_util.h"
#include "../../service/ouster/client.h"

#include "../../service/Timestamp.h"

//google protobuf
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>
#include "../../protobuf/sensors.pb.h"

#define os1_host "10.5.5.1"
#define os1_udp_dest "10.5.5.2"

namespace LiDAR = ouster::sensor;
namespace OS1 = ouster::OS1;

using namespace std;

extern int USE_LiDAR;

class LiDAR_SensingThread
{
public:
int lidar_port = 0;
    int imu_port = 0;
    int W = 1024;
    int H = OS1::pixels_per_column;
    LiDAR_SensingThread(){};
    static void run(zmq::socket_t *socket);
};

#endif //LIDARSENSINGTHREAD_H_