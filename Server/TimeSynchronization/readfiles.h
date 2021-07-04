// 참고: https://github.com/kka-na/DIVA_Qt

#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define is_GPS 1
#define is_CAM  2
#define is_LiDAR 3
#define is_IMU 4
#define is_CAN 5
#define  number_of_sensors 5
class ReadFiles
{
public:
    string dir;

    ReadFiles(string fpath);
    string get_path(int i);
    vector<vector<string>> read_csv(string csv_file);
    vector<string> read_txt(string txt_file);
};
