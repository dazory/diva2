#pragma once

#include "CamSensing.h"

CamSensing::CamSensing()
{
    Compression_params.push_back(cv::IMWRITE_JPEG_QUALITY); //Select jpeg
    Compression_params.push_back(30);
}

bool CamSensing::initialize(const int devicename)
{
    int open = cap.open(devicename);
    return open;
}
