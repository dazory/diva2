class ImuPacket {
public:
    ImuPacket();
    float scaledAccelX, scaledAccelY, scaledAccelZ;
    float scaledGyroX, scaledGyroY, scaledGyroZ;
    float scaledMagX, scaledMagY, scaledMagZ;
    float estRoll, estPitch, estYaw;
    float estRollUncert, estPitchUncert, estYawUncert;

};

ImuPacket::ImuPacket(){
    scaledAccelX=0;  scaledAccelY=0; scaledAccelZ=0;
    scaledGyroX=0; scaledGyroY=0; scaledGyroZ=0;
    scaledMagX=0; scaledMagY=0; scaledMagZ=0;
    estRoll=0; estPitch=0; estYaw=0;
    estRollUncert=NULL; estPitchUncert=NULL; estYawUncert=NULL;
}

enum IMU{IMU_EXCEPTION=0, IMU_ACCELX, IMU_ACCELY, IMU_ACCELZ, IMU_GYROX, IMU_GYROY, IMU_GYROZ, IMU_MAGX, IMU_MAGY, IMU_MAGZ,
        IMU_ESTROLL, IMU_ESTPITCH, IMU_ESTYAW, IMU_ESTROLL_UNCERT, IMU_ESTPITCH_UNCERT, IMU_ESTYAW_UNCERT};

static map<string, IMU> ImuMap;
void Init(){
    ImuMap["scaledAccelX"] = IMU_ACCELX;
    ImuMap["scaledAccelY"] = IMU_ACCELY;
    ImuMap["scaledAccelZ"] = IMU_ACCELZ;
    ImuMap["scaledGyroX"] = IMU_GYROX;
    ImuMap["scaledGyroY"] = IMU_GYROY;
    ImuMap["scaledGyroZ"] = IMU_GYROZ;
    ImuMap["scaledMagX"] = IMU_MAGX;
    ImuMap["scaledMagY"] = IMU_MAGY;
    ImuMap["scaledMagZ"] = IMU_MAGZ;

    ImuMap["estRoll"] = IMU_ESTROLL;
    ImuMap["estPitch"] = IMU_ESTPITCH;
    ImuMap["estYaw"] = IMU_ESTYAW;

    ImuMap["estRollUncert"] = IMU_ESTROLL_UNCERT;
    ImuMap["estPitchUncert"] = IMU_ESTPITCH_UNCERT;
    ImuMap["estYawUncert"] = IMU_ESTYAW_UNCERT;

    ImuMap[""] = IMU_EXCEPTION;
}