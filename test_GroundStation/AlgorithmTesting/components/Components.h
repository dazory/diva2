#pragma once

// #include <opencv2/opencv.hpp>
// #include "opencv2/imgproc/imgproc.hpp"
// #include "opencv2/highgui/highgui.hpp"
// #include <opencv2/imgcodecs.hpp>
// #include <stdint.h>
#include <iostream>
#include <zmq.hpp>

#include <google/protobuf/util/time_util.h>
#include <google/protobuf/text_format.h>
#include "../../protobuf/sensors.pb.h"

//using namespace cv;
using namespace google::protobuf::util;
using namespace std;

class Components
{
public:

    Components();
    
    /* DATA */
    INPUTS *inputs;
    SETTINGS settings;
    OUTPUTS *outputs;

    /* FUNCTIONS */
    
    
};

class INPUTS{
    
};

class SETTINGS{
public:
    /* DATA */
    vector<int> inputs_discriptions;
    string function_name;
    
};

class OUTPUTS{

};