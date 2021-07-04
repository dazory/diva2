#include <iostream>
#include <sys/time.h>
#include "../service/Timestamp.h"
using namespace std;

int main(){
    printf("hello\n");

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

    auto time = chrono::system_clock::now();
    auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
    long long currentTimeMillis = mill.count();
    int msc = currentTimeMillis % 1000;
    long nowTime = currentTimeMillis / 1000;
    tm *t = localtime(&nowTime);

    char cPath[15];
    sprintf(cPath, "/home/diva2/DIVA2_DATA/%s_0/CAM/JPG/CAM_%04d%02d%02d", timestamp.c_str(), t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    // string cPath = "/home/diva2/DIVA2data/"+timestamp+"_0/CAM/JPG/CAM_%04d%02d%02d" + t->tm_year + 1900 + t->tm_mon + 1 + t->tm_mday;
    printf("path: %s\n", cPath);
}