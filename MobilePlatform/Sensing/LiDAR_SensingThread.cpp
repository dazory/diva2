#pragma once
#include "LiDAR_SensingThread.h"

void LiDAR_SensingThread::run(zmq::socket_t *socket, mutex &m, float leaf_size)
{
    Timestamp ts;

    time_t system_time;
    struct tm* systime;
    system_time = time(NULL);
    systime = localtime(&system_time);

    string tm_year = to_string(systime->tm_year + 1900);
    string tm_month = to_string(systime->tm_mon+1);
    string tm_date = to_string(systime->tm_mday);
    if(tm_date.size() == 1){
        tm_date = "0"+tm_date;
    }

    string timestamp;
    timestamp = tm_year + tm_month + tm_date;

    // <make csv file>
    string path = "/home/diva2/DIVA2data/"+timestamp+"_0/LiDAR/i30_LiDAR_" + ts.getMilliTime() + ".csv";
    fstream dataFile;
    dataFile.open(path, ios::out);

    LiDAR_Sensing mLiDAR_Sensing;

    bool stop_flag = false;
    bool do_config = true;

    int lidar_port = 0;
    int imu_port = 0;

    int W = 1024;
    int H = OS1::pixels_per_column;

    LiDAR::lidar_mode mode = LiDAR::MODE_1024x10;

    char cSn[50];

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

                //timestamp
                auto time = chrono::system_clock::now();
                auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
                long long currentTimeMillis = mill.count();
                int msc = currentTimeMillis % 1000;
                long nowTime = currentTimeMillis / 1000;
                tm *ts = localtime(&nowTime);

                //[ save PCD ] ;pcd 포맷은 헤더정보(전체 포인트 수, 데이터 타입, 크기 등의 정보) + 데이터(x,y,z)
                sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
                        ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
                string ttt(cSn);
                string name = "/home/diva2/DIVA2data/"+timestamp+"_0/LiDAR/PCD/LiDAR_" + ttt + ".pcd";
                pcl::io::savePCDFile(name, *mLiDAR_Sensing.cloud, true);

                // [ downsampling ]
                pcl::VoxelGrid<pcl::PointXYZ> sor;
                sor.setInputCloud(mLiDAR_Sensing.cloud);          //입력
                sor.setLeafSize(leaf_size, leaf_size, leaf_size); //leaf size 조절
                sor.filter(*mLiDAR_Sensing.cloud_filtered);       //출력

                // [Parsing to Proto]
                pLiDAR.set_size(mLiDAR_Sensing.cloud_filtered->size());
                // cout << "point size in protobuf: " << pLiDAR.size() << endl;

                for (const auto &point : *mLiDAR_Sensing.cloud_filtered)
                {
                    sensors::Lidar::xyz *xyz = pLiDAR.add_data();
                    xyz->set_x(point.x);
                    xyz->set_y(point.y);
                    xyz->set_z(point.z);
                }
                struct timeval tv;
                gettimeofday(&tv, NULL);
                pLiDAR.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));

                // [Sender to PUB socket]
                // <Serialization>
                int data_len = pLiDAR.ByteSize();
                unsigned char data[data_len] = "\0";
                pLiDAR.SerializeToArray(data, data_len);
                // for (auto i = 0; i < data_len; i++)
                //     printf("%02X ", data[i]);
                printf("\n");
                printf("[MobilePlatform/Sensing/LiDARSensingThread] Serialize\n");

                dataFile << cSn << endl;
                // <Send>
                zmq::message_t zmqData(data_len);
                memcpy((void *)zmqData.data(), data, data_len);
                m.lock();
                s_send_idx(*socket, SENSOR_LIDAR);
                s_send(*socket, zmqData);
                m.unlock();
                printf("[MobilePlatform/Sensing/LiDARSensingThread] Complete to send to PUB Socket\n");

                ////~~~~~~ json 형식으로 출력 "Key" : Value ~~~~~~
                // string json_string;
                // google::protobuf::util::JsonPrintOptions options;
                // options.add_whitespace = true;
                // options.always_print_primitive_fields = true;
                // options.preserve_proto_field_names = true;
                // google::protobuf::util::MessageToJsonString(pLiDAR, &json_string, options);
                //cout << json_string << endl;

                mLiDAR_Sensing.cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
                mLiDAR_Sensing.cloud_filtered.reset(new pcl::PointCloud<pcl::PointXYZ>);
                mLiDAR_Sensing.resetCount();

                // [Options]
                usleep(100);
            }
        }
    }
    dataFile.close();
}

