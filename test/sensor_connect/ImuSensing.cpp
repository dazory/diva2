#pragma once
#include "ImuSensing.h"

ImuSensing::ImuSensing(){
      mImuPacket = ImuPacket();
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

void ImuSensing::read_imuPacket(int enumIMU, mscl::MipDataPoint dataPoint){
      switch(enumIMU){
            case IMU_ACCELX:
                  {mImuPacket.scaledAccelX = dataPoint.as_float(); printf("IMU_ACCELX\n"); break;}
            case IMU_ACCELY:
                  {mImuPacket.scaledAccelY = dataPoint.as_float(); printf("IMU_ACCELY\n"); break;}
            case IMU_ACCELZ:
                  {mImuPacket.scaledAccelZ = dataPoint.as_float(); printf("IMU_ACCELZ\n"); break;}
            case IMU_GYROX:
                  {mImuPacket.scaledGyroX = dataPoint.as_float(); printf("IMU_GYROX\n"); break;}
            case IMU_GYROY:
                  {mImuPacket.scaledGyroY = dataPoint.as_float(); printf("IMU_GYROY\n"); break;}
            case IMU_GYROZ:
                  {mImuPacket.scaledGyroZ = dataPoint.as_float(); printf("IMU_GYROZ\n"); break;}
            case IMU_MAGX:
                  {mImuPacket.scaledMagX = dataPoint.as_float(); printf("IMU_MAGX\n"); break;}
            case IMU_MAGY:
                  {mImuPacket.scaledMagY = dataPoint.as_float(); printf("IMU_MAGY\n"); break;}
            case IMU_MAGZ:
                  {mImuPacket.scaledMagZ = dataPoint.as_float(); break;} 

            case IMU_ESTROLL:
                  {mImuPacket.estRoll = dataPoint.as_float(); printf("IMU_ESTROLL\n"); break;}
            case IMU_ESTPITCH:
                  {mImuPacket.estPitch = dataPoint.as_float(); printf("IMU_ESTPITCH\n"); break;}
            case IMU_ESTYAW:
                  {mImuPacket.estYaw = dataPoint.as_float(); printf("IMU_ESTYAW\n"); break;}
                    
            case IMU_ESTROLL_UNCERT:
                  {mImuPacket.estRollUncert = dataPoint.as_float(); printf("IMU_ESTROLL_UNCERT\n"); break;}
            case IMU_ESTPITCH_UNCERT:
                  {mImuPacket.estPitchUncert = dataPoint.as_float(); printf("IMU_ESTPITCH_UNCERT\n"); break;}
            case IMU_ESTYAW_UNCERT:
                  {mImuPacket.estYawUncert = dataPoint.as_float(); printf("IMU_ESTYAW_UNCERT\n"); break;}

            default:{
                  printf("\n");
                  break;
            }
      }
      mImuPackets.push_back(mImuPacket);
}

void ImuSensing::displayImuPacket(){
      printf("Accel (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledAccelX,mImuPacket.scaledAccelY,mImuPacket.scaledAccelZ );
      printf("Gyro (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledGyroX,mImuPacket.scaledGyroY,mImuPacket.scaledGyroZ );
      printf("Mag (X,Y,Z) = (%.2f, %.2f, %.2f)\n",mImuPacket.scaledMagX,mImuPacket.scaledMagY,mImuPacket.scaledMagZ );
      printf("est (Roll,Pitch,Yaw) = (%.2f, %.2f, %.2f)\n",mImuPacket.estRoll,mImuPacket.estPitch,mImuPacket.estYaw );
      printf("estUncert (Roll,Pitch,Yaw) = (%.2f, %.2f, %.2f)\n",mImuPacket.estRollUncert,mImuPacket.estPitchUncert,mImuPacket.estYawUncert );
}

size_t ImuSensing::getImuPacketSize(){
      return sizeof(mImuPacket);
}
size_t ImuSensing::getImuPacketsSize(){
      return sizeof(mImuPackets);
}

ImuPacket ImuSensing::getImuPacket(){
      return mImuPacket;
}
