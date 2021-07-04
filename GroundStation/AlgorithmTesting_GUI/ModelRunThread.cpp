#pragma once
#include "ModelRunThread.h"

enum Sensor { lidar, cam, can, imu, gps};

ModelRunThread::ModelRunThread(QObject *parent) : QThread(parent)
{

}

void ModelRunThread::run(){
    printf("[ModelRunThread::run] start\n");
    printf("   sensorIdx:%d\n", this->sensorIdx);
    printf("   algorithmIdx:%d\n", this->algorithmIdx);
    printf("   data file:%s\n", this->str_datafile.c_str());
    printf("   config file:%s\n", this->str_configfile.c_str());
    printf("   weight file:%s\n", this->str_weightfile.c_str());
    printf("   input file:%s\n", this->str_inputfile.c_str());
    printf("\n");

    string command;
    if(sensorIdx == Sensor::cam){
        if(algorithmIdx==0) // lane detection
        {
            command += "cd /home/diva2/diva2/GroundStation/AlgorithmTesting/lane_detection_algorithm/ ";
            command += "&& python3 model.py ";
            command += " ";
            command += this->str_datafile;
            command += " ";
            command += this->str_weightfile;
            command += " ";
            command += this->str_inputfile;
        }else if(algorithmIdx==1) // object detection
        {
            command += "cd /home/diva2/diva2/GroundStation/AlgorithmTesting/obj_detection/darknet/ ";
            command += "&& ./darknet detector test ";
            command += this->str_datafile;
            command +=" ";
            command += this->str_configfile;
            command +=" ";
            command += this->str_weightfile;
        }
    }
    
    int ret = system(command.c_str());

}

void ModelRunThread::stop(){
}

void ModelRunThread::set_algorithmIdx(int algoIdx){
    this->algorithmIdx = algoIdx;
}
void ModelRunThread::set_sensorIdx(int sensorIdx){
    this->sensorIdx = sensorIdx;
}

void ModelRunThread::set_datafile(string datafile){
    this->str_datafile = datafile;
}
void ModelRunThread::set_configfile(string configfile){
    this->str_configfile = configfile;
}
void ModelRunThread::set_weightfile(string weightfile){
    this->str_weightfile = weightfile;
}
void ModelRunThread::set_inputfile(string inputfile){
    this->str_inputfile = inputfile;
}
