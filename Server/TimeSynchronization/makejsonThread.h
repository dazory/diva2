#pragma once
#include <iostream>
#include <pqxx/pqxx> 
#include "jsoncpp/json/json.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "makejson.h"
#include "readfiles.h"
#include "indexandtimes.h"

using namespace std;
using namespace pqxx;

class MakeJsonThread{
    public:
        MakeJsonThread();
        void run();
        void stop();
    private:
        bool stop_flag=false;
};