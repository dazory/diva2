// 참고: https://github.com/kka-na/DIVA_Qt

#pragma once

#include <iostream>

#include "indexandtimes.h"
#include "readfiles.h"
#include "jsoncpp/json/json.h"

class MakeJson
{
public:
    MakeJson(string fpath);
    

    string dir;

    IndexAndTimes *iat;

    int gps_idx;

    int gps_start;
    int gps_last;
    int cam_start;
    int lidar_start;
    int imu_start;
    int can_start;

    int gps_csv_size;
    int imu_csv_size;
    int cam_csv_size;
    int lidar_csv_size;
    int can_csv_size;

    int scene_count;
    int cam_sensors;
    int this_frame_start;
    int this_log_start;
    int this_frame_data_start;

    string generate_token();
    string generate_token_2();
    string generate_timestamp();
    bool Log(int car_id);
    bool Sensor(int sensors_num);
    bool Scene();
    bool Frame();
    bool Frame_Data();
    bool Cam_Data();
    bool Lidar_Data();
    bool Gps_Data();
    bool Imu_Data();
    bool Can_Data();

    bool Check_Directory();

    void Get_LLA(int gps_idx);
    long double Convert_to_dd(long double raw);
    void Get_GAM(int imu_idx);
    void Get_HSGT(int can_idx);

    //~GPS Datum~
    string latitude;
    string isNorth;
    string longitude;
    string isEast;
    string gpsQuality;
    string NumberOfSatellitesInUse;
    string HorizontalDilutionOfPrecision;
    string AntennaAltitudeMeters;
    string GeoidalSeparationMeters;
    //~IMU Datum~
    string scaledaccelx;
    string scaledaccely; 
    string scaledaccelz;
    //~CAN Datum~
    string handleAngle;
    string turnLight;
    string vehicleSpeed;
    string gear;

    int num_of_scene = 0;

};