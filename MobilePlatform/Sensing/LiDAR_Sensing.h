
// #ifndef LIDAR_SENSING_H
// #define LIDAR_SENSING_H

// #include <unistd.h>
// #include <atomic>
// #include <cmath>
// #include <csignal>
// #include <cstdlib>
// #include <chrono>

// #include <Eigen/Eigen>
// #include <fstream>
// #include <istream>
// #include <iostream>
// #include <iterator>
// #include <memory>
// #include <sstream>
// #include <string>
// #include <thread>
// #include <vector>
// #include <zmq.hpp>
// #include "../../service/zmq_helper.h"

// #include <pcl/point_cloud.h>
// #include <pcl/io/pcd_io.h>
// #include <pcl/point_types.h>
// #include <pcl/common/transforms.h>
// #include <pcl/console/parse.h>
// #include <pcl/filters/voxel_grid.h>

// #include "jsoncpp/json/json.h"

// // #include "../service/ouster/os1.h" //old
// #include "../../service/ouster/os1_packet.h"
// #include "../../service/ouster/os1_util.h"
// #include "../../service/ouster/client.h"

// //google protobuf
// #include <google/protobuf/text_format.h>
// #include <google/protobuf/util/json_util.h>
// #include "../../protobuf/sensors.pb.h"

// // #define os1_host "os1-991904000944"
// #define os1_host "10.5.5.1"
// #define os1_udp_dest "10.5.5.2"

// namespace LiDAR = ouster::sensor;
// namespace OS1 = ouster::OS1;

// using namespace std;

// class LiDAR_Sensing
// {
// public:
//     LiDAR_Sensing();

//     pcl::PointCloud<pcl::PointXYZ>::Ptr cloud; //생성할 PointCloud structure구조체(x,y,z) 정의
//     pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered; //for downsampling
    
//     bool stop_flag = false;
//     bool do_config = true;
    
//     int count = 0;
//     int W = 1024;
//     int H = OS1::pixels_per_column;

//     string metadata{};

//     ofstream writeFile;


//     void resetCount();
//     void addCount();
//     int getCount();

//     void WritePCD(std::vector<double> xyz_lut, uint8_t *buf);

//     void stop();

// private:
// };

// #endif //LIDAR_SENSING_H
