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
// #include "../service/zmq_helper.h"

// //#include <vtkRenderWindow.h>
// #include <pcl/point_cloud.h>
// #include <pcl/io/pcd_io.h>
// #include <pcl/point_types.h>
// //#include <pcl/visualization/pcl_visualizer.h>
// #include <pcl/common/transforms.h>
// #include <pcl/console/parse.h>
// #include <pcl/filters/voxel_grid.h>

// #include "jsoncpp/json/json.h"

// // #include "../service/ouster/os1.h" //old
// #include "../service/ouster/os1_packet.h"
// #include "../service/ouster/os1_util.h"
// #include "../service/ouster/client.h"

// //google protobuf
// #include <google/protobuf/text_format.h>
// #include <google/protobuf/util/json_util.h>
// #include "../protobuf/sensors.pb.h"

// #define os1_host "10.5.5.1"
// #define os1_udp_dest "10.5.5.2"

// namespace LiDAR = ouster::sensor;
// namespace OS1 = ouster::OS1;
// //namespace viz = ouster::viz;

// using namespace std;
// using namespace google;
// using namespace protobuf;

// class LiDAR_Sensing
// {
// public:
//     LiDAR_Sensing();

//     pcl::PointCloud<pcl::PointXYZ>::Ptr cloud; //생성할 PointCloud structure구조체(x,y,z) 정의
//     pcl::PointCloud<pcl::PointXYZ> cloud2;

//     bool stop_flag = false;
//     bool do_config = true;
//     int lidar_port = 0;
//     int imu_port = 0;
//     int count = 0;
//     int W = 1024;
//     int H = OS1::pixels_per_column;

//     string metadata{};

//     ofstream writeFile;

//     struct PointField
//     {
//         int offset;
//         int datatype;
//         int count;
//     };

//     struct PointCloudHeader
//     {
//         int width;
//         int height;
//         bool is_dense;
//         bool is_bigendian;
//         int point_step;
//         int row_step;
//         int num_fields;
//     };
//     void resetCount();
//     void addCount();
//     int getCount();

//     void WritePCD_proto(std::vector<double> xyz_lut, uint8_t *buf, sensors::Lidar &pLiDAR);

//     void stop();

// private:
//     void send_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr);
//     void connectedOK();
// };

// #endif //LIDAR_SENSING_H
