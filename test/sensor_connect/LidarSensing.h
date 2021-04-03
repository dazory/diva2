//#pragma once
#ifndef LIDARSENSING_H_
#define LIDARSENSING_H_

#include <stdint.h>
#include <iostream>
#include "../service/Timestamp.h"
using namespace std;
class LidarSensing
{
    public:
    LidarSensing();
    bool initialize(const int devicename); //0

    private:
};
#endif //LIDARSENSING_H_