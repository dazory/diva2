#pragma once
#include "ImuSensing.h"

ImuSensing::ImuSensing(){
      // gyrox, gyroy, gyroz, magx, magy, magz, accelx, accely, accelz;

}
mscl::InertialNode ImuSensing::initialize(const char *devicename){
      mscl::Connection connection = mscl::Connection::Serial(devicename, 115200);
      mscl::InertialNode node =  mscl::InertialNode(connection);
      return node;
}
int ImuSensing::getBaudrate(const char *baudrate){

}
