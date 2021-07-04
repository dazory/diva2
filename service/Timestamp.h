#ifndef Timestamp_h
#define Timestamp_h

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <chrono>
#include <fstream>
#include <sstream>
#include <istream>
#include <string.h>
#include <string>
#include <cstring>

using namespace std;

class Timestamp{
public:

    string getMilliTime(){
        auto time = chrono::system_clock::now();
        auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
        long long currentTimeMillis = mill.count();
        int msc = currentTimeMillis % 1000;
        long nowTime = currentTimeMillis/1000;

        tm *ts = localtime(&nowTime);
        char buffer[80];
        strftime(buffer, 80, "%Y%m%d%H%M%S", ts);
        string s(buffer);

        string str;
        if(stoi(to_string(msc)) < 10){
          str = s+"00"+to_string(msc);
      }
      else if(stoi(to_string(msc)) < 100){
          str = s+"0"+to_string(msc);
      }else{
          str = s+to_string(msc);
      }
      return str;
  }

  const char *p_time(){
    string get_time = getMilliTime();

    char * mtime = new char[get_time.size()];
    strcpy(mtime, get_time.c_str());
    return mtime;
}
const char *utc_to_kst(char*s){
    char *buf = new char[256];
    float utc = atof(s);
    float kst = utc + 90000;
    int result = kst*100;
    sprintf(buf, "%d", result);
    return buf;
}


};

#endif