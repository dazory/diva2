// 참고: https://github.com/kka-na/DIVA_Qt

#include "makejsonThread.h"

using namespace std;

MakeJsonThread::MakeJsonThread(){}

void MakeJsonThread::run(){

    //timestamp
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
    
    //make log, frame, scene, lidar, cam, gps, imu, can json
    MakeJson* j = new MakeJson("/home/cvlab2/DIVA2/diva2/Server/DIVA2_DATA/"+timestamp+"_0");
    j->Sensor(5);
    
    j->Log(0);
    cout<<"make Log json"<<endl;
    j->Frame();
    cout<<"make Frame json"<<endl;
    j->Scene();
    cout<<"make Scene json"<<endl;
    j->Lidar_Data();
    cout<<"make Lidar json"<<endl;
    j->Cam_Data();
    cout<<"make Cam json"<<endl;
    j->Gps_Data();
    cout<<"make Gps json"<<endl;
    j->Imu_Data();
    cout<<"make Imu json"<<endl;
    j->Can_Data();
    cout<<"make Can json"<<endl;

    delete j;
}

void MakeJsonThread::stop(){
    stop_flag = true;
}