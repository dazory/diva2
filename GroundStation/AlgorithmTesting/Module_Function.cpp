#include "Module_Function.h"
#include "global.h"

extern map<int, string> mLidar;
extern map<int, string> mCam;
extern map<int, string> mCan;
extern map<int, string> mImu;
extern map<int, string> mGps;
extern vector<map<int,string>> mAlgorithms;

Module_Function::Module_Function(int sensorIdx, int algorithmIdx){
    this->sensorIdx = sensorIdx;
    this->algorithmIdx = algorithmIdx;
    printf("[Module_Function::Module_Function] sensor %d, algorithm %d\n", this->sensorIdx, this->algorithmIdx);
}

void Module_Function::run(){
    switch (sensorIdx)
    {
    case SensorIdx::lidar:
    { break; }
    case SensorIdx::cam:
    { 
        switch (algorithmIdx)
        {
        case 0:
        {
            funcPath = "/home/diva2/diva2/build/test/lane_detection/LaneDetector";
            funcName = "./lanes";
            break;
        }
        default:
            break;
        }
        break;
    }
    case SensorIdx::can:
    { break; }
    case SensorIdx::imu:
    { break; }
    case SensorIdx::gps:
    { break; }
    default:
    { break; }
    }

    // clock_t clk_bef = clock();
    string command = "cd "+funcPath+" && pwd && "+funcName+" "+fileName;
    // int ret = system(command.c_str());
    // clock_t clk_aft = clock();
    // clk_term = (float)(clk_aft - clk_bef)/CLOCKS_PER_SEC;
    // printf("[Module_Function::run] term = %f (or %f)\n", clk_term, (float)(clk_aft - clk_bef)/CLOCKS_PER_SEC);
}

void Module_Function::setFileName(string fileName){
    this->fileName = fileName;
}



void Module_Function::model_run(string model_path, string weight_path, string dir){
    // './checkpoints/fcn_big_01.json'
    // './checkpoints/fcn_big_01.h5'
    string command = "";
    command += "cd /home/diva2/diva2/GroundStation/AlgorithmTesting/Algorithm/";
    command += " && ";
    command += "python3 model.py ";
    command += model_path;
    command += " ";
    command += weight_path;
    command += " ";
    command += dir;
    printf("[Module_Function::model_run] command: %s\n", command.c_str());
    system(command.c_str());
}
        