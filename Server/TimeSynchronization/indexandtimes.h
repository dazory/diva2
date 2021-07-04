// 참고: https://github.com/kka-na/DIVA_Qt

#pragma once
#include "readfiles.h"
#define is_GPS 1
#define is_CAM  2
#define is_LiDAR 3
#define is_IMU 4
#define is_CAN 5
#define number_of_sensors 5

class IndexAndTimes{
public:
    string dir = "";
    ReadFiles *rf;

    int latest_sensor;
    int earliest_sensor;
    int gps_last;
    int s_ts = 0;

    IndexAndTimes(string fpath);

    int get_hhmmsssss(string str);


    //Get Files!!
    vector<vector<string>> gps_csv;
    vector<vector<string>> cam_csv;
    vector<vector<string>> lidar_csv;
    vector<vector<string>> imu_csv;
    vector<vector<string>> can_csv;

    int find_cam_idx_by_ts(int now, string comp_timestamp);
    int find_lidar_idx_by_ts(int now, string comp_timestamp);
    int find_gps_idx_by_ts(int now, string comp_timestamp);
    int find_imu_idx_by_ts(int now, string comp_timestamp);
    int find_can_idx_by_ts(int now, string comp_timestamp);
    int find_cam_start_idx();

    int find_lidar_start_idx();
    int find_gps_start_idx();
    int find_imu_start_idx();
    int find_can_start_idx();

    string find_latest_started();

    string find_earliest_ended();

    int number_of_frames();

    int* get_start_indexes();

    bool txt_sensor_is_key_frame(int isSensor, int target_idx, int gps_idx);
    bool csv_sensor_is_key_frame(int isSensor, int target_idx, int gps_idx);
    string get_gps_timestamp(int gps_idx);
    string get_cam_timestamp(int cam_idx);
    string get_lidar_timestamp(int lidar_idx);
    string get_imu_timestamp(int imu_idx);
    string get_can_timestamp(int can_idx);
};