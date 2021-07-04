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

using namespace std;
using namespace pqxx;

class ImuStoringThread{
    public:
        ImuStoringThread();
        void run();
        void stop();
    private:
        bool stop_flag=false;
};