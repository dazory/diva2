// 참고: https://github.com/kka-na/DIVA_Qt
#pragma once
#include "makejsonThread.h"
#include <thread> 
#include <string>
using namespace std;

int main(int argc, char *argv[]){

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

    // make JSON folder
    string command = "mkdir -p /home/cvlab2/DIVA2/diva2/Server/DIVA2_DATA/"+timestamp+"_0/JSON";
    
    const char *c = command.c_str();
    system(c);
    cout<<"makefile"<<endl;

    // makejsonThread
    MakeJsonThread mMakeJsonThread;
    thread makejsonThread(&MakeJsonThread::run, &mMakeJsonThread);
    makejsonThread.join();
}