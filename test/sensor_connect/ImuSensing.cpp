#pragma once
#include "ImuSensing.h"

ImuSensing::ImuSensing(){
      // gyrox, gyroy, gyroz, magx, magy, magz, accelx, accely, accelz;

}
mscl::InertialNode ImuSensing::getMsclNode(const char *devicename, mscl::uint32 baudrate){
      /*
      : Make sure to replace ${devicename} and ${baudrate} with your own port settings.
      */

      //create the connection object with port and baud rate
      mscl::Connection connection = mscl::Connection::Serial(devicename, baudrate);

      //create the InertialNode, passing in the connection
      mscl::InertialNode node =  mscl::InertialNode(connection);
      return node;
}
