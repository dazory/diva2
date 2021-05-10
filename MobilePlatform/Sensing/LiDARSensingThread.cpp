#include "LiDARSensingThread.h"

// int count = 0;

// void WritePCD(std::vector<double> xyz_lut, uint8_t *buf, int W, int H)
// {
//     float leaf_size = 0.001f;

//     for (int icol = 0; icol < OS1::columns_per_buffer; icol++)
//     {
//         std::cout << "for" << std::endl;
//         const uint8_t *col_buf = OS1::nth_col(icol, buf);
//         const uint16_t m_id = OS1::col_measurement_id(col_buf);
//         const int idx = H * m_id;

//         for (uint8_t ipx = 0; ipx < H; ipx++)
//         {
//             std::cout << "second for" << std::endl;
//             const uint8_t *px_buf = OS1::nth_px(ipx, col_buf);
//             uint32_t r = OS1::px_range(px_buf);
//             int ind = 3 * (idx + ipx);
//             pcl::PointXYZ points;
//             points.x = r * leaf_size * xyz_lut[ind + 0]; //leaf size 설정 -> downsampling 0.001f(787kB) 5****
//             points.y = r * leaf_size * xyz_lut[ind + 1]; //0.01f -> 1cm (787kB) tkdlwmsms 27***
//             points.z = r * leaf_size * xyz_lut[ind + 2];
//             if (count > W * H)
//             {
//                 break;
//             }

//             cloud->push_back(points); //point들을 cloud에 담음
//             count++;
//         }
//     }
// }

void LiDAR_SensingThread::run(zmq::socket_t *socket)
{
    // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); //PointCloud structure구조체(x,y,z)생성
    // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);

    sensors::Lidar pLiDAR; //protobuf

    Timestamp ts;
    ofstream writeFile;

    int lidar_port = 0;
    int imu_port = 0;
    int W = 1024;
    int H = OS1::pixels_per_column;

    //The first value is horizontal resolution and the second is scan rate.
    LiDAR::lidar_mode mode = LiDAR::MODE_1024x10; //512x10, 1024x10, 2048x10, 512x20, 1024x20.

    std::shared_ptr<LiDAR::client> LiDAR_points;
    //LiDAR initialize
    if (USE_LiDAR == 1)
    {
        cout << "Configuring sensor: " << os1_host
             << " UDP Destination:" << os1_udp_dest << std::endl;
        LiDAR_points = ouster::sensor::init_client(os1_host, os1_udp_dest, mode,
                                                   ouster::sensor::TIME_FROM_INTERNAL_OSC, lidar_port, imu_port);
        cout << "init_client" << endl;
        LiDAR::client_state st = LiDAR::poll_client(*LiDAR_points); //LiDAR Data 잘 들어오고 있는지 체크
        cout << "st : " << st << endl;
    }

    int c = 0;
    uint8_t lidar_buf[ouster::sensor::lidar_packet_bytes + 1]; //연결된 Lidar로부터 Data를 읽어 저장할 buffer
    string metadata{};

    if (USE_LiDAR == 1)
        metadata = LiDAR::get_metadata(*LiDAR_points);

    ouster::sensor::sensor_info info = LiDAR::parse_metadata(metadata);

    vector<double> xyz_lut = OS1::make_xyz_lut(W, H, info.beam_azimuth_angles, info.beam_altitude_angles);

    int count = 0;
    while (1)
    {

         pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); //PointCloud structure구조체(x,y,z)생성
        //  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
         LiDAR::client_state st = LiDAR::poll_client(*LiDAR_points); //LiDAR Data 잘 들어오고 있는지 체크
         if (st & LiDAR::client_state::LIDAR_DATA)
         {

             if (LiDAR::read_lidar_packet(*LiDAR_points, lidar_buf))
             {

                //  float leaf_size = 0.001f;

                 for (int icol = 0; icol < OS1::columns_per_buffer; icol++)
                 {

                     // std::cout << "for" << std::endl;
                     const uint8_t *col_buf = OS1::nth_col(icol, lidar_buf);
                     const uint16_t m_id = OS1::col_measurement_id(col_buf);
                     const int idx = H * m_id;

                     for (uint8_t ipx = 0; ipx < H; ipx++)
                     {

                         // std::cout << "second for" << std::endl;
                         const uint8_t *px_buf = OS1::nth_px(ipx, col_buf);
                         uint32_t r = OS1::px_range(px_buf);
                         int ind = 3 * (idx + ipx);
                         pcl::PointXYZ points;
                         points.x = r  * 0.001f * xyz_lut[ind + 0]; //leaf size 설정 -> downsampling 0.001f(787kB) 5**** * leaf_size
                         points.y = r  * 0.001f * xyz_lut[ind + 1]; //0.01f -> 1cm (787kB) tkdlwmsms 27***
                         points.z = r  * 0.001f * xyz_lut[ind + 2];
                         if (count > W * H) //break가 안걸림. 그래서 PCD저장이 안됨. run만 따로 분리하면 되는데 이렇게 하면 왜 안되는지 모르겠음ㅜㅜ
                         {
                             break;
                         }

                         cloud->push_back(points); //point들을 cloud에 담음
                         count++;
                     }
                 }
             }

             if (count == W * H)
             {
                //  cout << "count == W * H" << endl;
                 string ch_ts = ts.getMilliTime();
                 string name = "/home/dahye/diva2/MobilePlatform/Sensing/2021-05-10/LiDAR/i30_LiDAR_" + ch_ts + ".pcd"; //pcd 포맷은 헤더정보(전체 포인트 수, 데이터 타입, 크기 등의 정보) + 데이터(x,y,z)

                //  //보통 이렇게 downsapling 한다는데 cloud에 라이다에서 받은 데이터를 어떻게 담아야할지 모르겠다.
                //  pcl::VoxelGrid<pcl::PointXYZ> sor;
                //  sor.setInputCloud(cloud);                          //입력
                //  sor.setLeafSize(0.1f, 0.1f, 0.1f);              //leaf size  1cm
                //  sor.filter(*cloud_filtered);                       //출력
                 pcl::io::savePCDFile(name, *cloud, true); //pcd파일 저장(binary mode = true)
                 cout << "pcd saved" << endl;

                 // [Parsing to Proto]
                 for (const auto &point : *cloud)
                 {
                     sensors::Lidar::xyz *xyz = pLiDAR.add_data();
                     xyz->set_x(point.x);
                     xyz->set_y(point.y);
                     xyz->set_z(point.z);
                 }

                 // [Sender to PUB socket]
                 // <Serialization>
                 int data_len = pLiDAR.ByteSize();
                 unsigned char data[data_len] = "\0";
                 pLiDAR.SerializeToArray(data, data_len);
                 // for (auto i = 0; i < data_len; i++)
                 //     printf("%02X ", data[i]);
                 printf("\n");
                 printf("[MobilePlatform/Sensing/LiDARSensingThread] Serialize. size : %d\n", data_len);

                 // <Send>
                 zmq::message_t zmqData(data_len);
                 memcpy((void *)zmqData.data(), data, data_len);
                 s_send(*socket, zmqData);
                 printf("[MobilePlatform/Sensing/LiDARSensingThread] Complete to send to PUB Socket\n");

                 // ////~~~~~~ json 형식으로 출력 "Key" : Value ~~~~~~
                 string json_string;
                 google::protobuf::util::JsonPrintOptions options;
                 options.add_whitespace = true;
                 options.always_print_primitive_fields = true;
                 options.preserve_proto_field_names = true;
                 google::protobuf::util::MessageToJsonString(pLiDAR, &json_string, options);
                 // cout << json_string << endl;

                 // [Store the LiDAR data]
                 // <Make .json File>
                 std::ofstream ost;
                 ost.open("LiDAR_only_voxel_0.01f.json", std::ios_base::out | std::ios_base::app);
                 ost << json_string;
                 cout << "saved" << endl
                      << endl;

                 // if (writeFile.is_open())
                 // {
                 //     writetxtFile << ch_ts << "\n"; //취득 시점의 timestamp저장(txt).
                 // }
                 cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
                //  cloud_filtered.reset(new pcl::PointCloud<pcl::PointXYZ>);

                 count = 0;
             }
        }
    }
}