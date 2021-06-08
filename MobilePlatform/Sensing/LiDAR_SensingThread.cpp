#include "LiDAR_SensingThread.h"

void LiDAR_SensingThread::run(zmq::socket_t *socket, mutex &m, float leaf_size)
{
    LiDAR_Sensing mLiDAR_Sensing;

    Timestamp ts;
    time_t time_bef = time(NULL);
    time_t time_now = time(NULL);

    bool stop_flag = false;
    bool do_config = true;

    int lidar_port = 0;
    int imu_port = 0;

    int W = 1024;
    int H = OS1::pixels_per_column;

    LiDAR::lidar_mode mode = LiDAR::MODE_1024x10;

    string path = "/home/dahye/LiDAR/i30_LiDAR_ts_" + ts.getMilliTime() + ".txt"; // 데이터(x,y,z)
    mLiDAR_Sensing.writeFile.open(path.c_str());

    std::shared_ptr<LiDAR::client> cli;
    if (USE_LiDAR == 1)
    {
        cout << "Configuring sensor: " << os1_host
             << " UDP Destination:" << os1_udp_dest << std::endl;
        cli = ouster::sensor::init_client(os1_host, os1_udp_dest, mode,
                                          ouster::sensor::TIME_FROM_INTERNAL_OSC, lidar_port, imu_port);
        cout << "init_client" << endl;
    }
    uint8_t lidar_buf[ouster::sensor::lidar_packet_bytes + 1];
    if (do_config)
        mLiDAR_Sensing.metadata = LiDAR::get_metadata(*cli);
    ouster::sensor::sensor_info info = LiDAR::parse_metadata(mLiDAR_Sensing.metadata);
    vector<double> xyz_lut = OS1::make_xyz_lut(W, H, info.beam_azimuth_angles, info.beam_altitude_angles);
    int cnt_ok = 0;

    while (!stop_flag)
    {
        sensors::Lidar pLiDAR;
        LiDAR::client_state st = LiDAR::poll_client(*cli);
        if (st & LiDAR::client_state::LIDAR_DATA)
        {
            if (LiDAR::read_lidar_packet(*cli, lidar_buf))
            {
                mLiDAR_Sensing.WritePCD(xyz_lut, lidar_buf);
            }

            if (mLiDAR_Sensing.getCount() == W * H)
            {
                string ch_ts = ts.getMilliTime();
                string name = "/home/dahye/LiDAR/PCD/i30_LiDAR_" + ch_ts + ".pcd"; //pcd 포맷은 헤더정보(전체 포인트 수, 데이터 타입, 크기 등의 정보) + 데이터(x,y,z)
                string name2 = "/home/dahye/LiDAR/PCD_filtered/i30_LiDAR_" + ch_ts + ".pcd";

                pcl::io::savePCDFile(name, *mLiDAR_Sensing.cloud, true);

                // downsampling
                pcl::VoxelGrid<pcl::PointXYZ> sor;
                sor.setInputCloud(mLiDAR_Sensing.cloud);    //입력
                sor.setLeafSize(leaf_size, leaf_size, leaf_size);          //leaf size 조절
                sor.filter(*mLiDAR_Sensing.cloud_filtered); //출력

                //pcd파일 저장
                pcl::io::savePCDFile(name2, *mLiDAR_Sensing.cloud_filtered, true);
                // cout << "pcd saved" << endl;
                // cout << "point size: " << mLiDAR_Sensing.cloud_filtered->size() << endl;
                pLiDAR.set_size(mLiDAR_Sensing.cloud_filtered->size());
                // cout << "point size in protobuf: " << pLiDAR.size() << endl;

                // [Parsing to Proto]
                for (const auto &point : *mLiDAR_Sensing.cloud_filtered)
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
                printf("[MobilePlatform/Sensing/LiDARSensingThread] Serialize\n");

                // <Send>
                if (time_now - time_bef >= 0.1)
                {
                    zmq::message_t zmqData(data_len);
                    memcpy((void *)zmqData.data(), data, data_len);
                    m.lock();
                    s_send_idx(*socket, SENSOR_LIDAR);
                    s_send(*socket, zmqData);
                    m.unlock();
                    printf("[MobilePlatform/Sensing/LiDARSensingThread] Complete to send to PUB Socket\n");
                }

                ////~~~~~~ json 형식으로 출력 "Key" : Value ~~~~~~
                string json_string;
                google::protobuf::util::JsonPrintOptions options;
                options.add_whitespace = true;
                options.always_print_primitive_fields = true;
                options.preserve_proto_field_names = true;
                google::protobuf::util::MessageToJsonString(pLiDAR, &json_string, options);
                //cout << json_string << endl;

                // [Store the LiDAR data]
                // // <Make .json File>
                // std::ofstream ost;
                // int cnt = 1;
                // ost.open("LiDAR.json", std::ios_base::out | std::ios_base::app);
                // ost << json_string;
                // // ost << "PCD count : " << cnt;
                // // cout << "saved" << endl
                // //  << endl;
                // cnt++;

                if (mLiDAR_Sensing.writeFile.is_open())
                {
                    mLiDAR_Sensing.writeFile << ch_ts << "\n"; //취득 시점의 timestamp저장(txt).
                }
                mLiDAR_Sensing.cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
                mLiDAR_Sensing.cloud_filtered.reset(new pcl::PointCloud<pcl::PointXYZ>);
                mLiDAR_Sensing.resetCount();

                // [Options]
                usleep(100);
            }
        }
    }
}
