#pragma once
#include "ImuSensingThread.h"
#include <sys/time.h>


enum IMU{IMU_EXCEPTION=0, IMU_ACCELX, IMU_ACCELY, IMU_ACCELZ, IMU_GYROX, IMU_GYROY, IMU_GYROZ, IMU_MAGX, IMU_MAGY, IMU_MAGZ,
        IMU_ESTROLL, IMU_ESTPITCH, IMU_ESTYAW, IMU_ESTROLL_UNCERT, IMU_ESTPITCH_UNCERT, IMU_ESTYAW_UNCERT};

static map<string, IMU> ImuMap;

void ImuMap_init();

ImuSensingThread::ImuSensingThread(){

}

void ImuSensingThread::run(zmq::socket_t *pubSock, const char *devicename, mscl::uint32 baudrate, mutex &m)
{
    
    printf("[MobilePlatform/Sensing/ImuSensingThread] run (MSCL VER.%s)\n", mscl::MSCL_VERSION.str());
    ImuMap_init();

    fstream dataFile;
    dataFile.open("imu.csv", ios::out);

    float scaledaccelx=0;
    float scaledaccely=0;
    float scaledaccelz=0;

    int count=0;
    if(USE_IMU==1)
    {
        // [Connect the IMU device]
        // <create the connection object with port and baud rate>
        mscl::Connection connection = mscl::Connection::Serial(devicename, baudrate);

        // <create the InertialNode, passing in the connection>
        mscl::InertialNode msclNode = mscl::InertialNode(connection);
        printf("[MobilePlatform/Sensing/ImuSensingThread] connect to IMU device\n");

        while(1)
        {
            sensors::Imu imu;

            // <Get MipDataPackets>
            mscl::MipDataPackets msclPackets = msclNode.getDataPackets(500);
            
                
            for(mscl::MipDataPacket packet : msclPackets)
            {
                packet.descriptorSet();
                mscl::MipDataPoints points = packet.data();
                    

                printf("=========== 읽은 데이터 ===========\n");
                printf("     Channel     |     Value     \n");
                int count =0;
                for(mscl::MipDataPoint dataPoint : points)
                {    
                    // [Parsing to Proto]
                    const char *cName = dataPoint.channelName().c_str();
                    printf("%15s  | %5d : ",cName, ImuMap[cName]);

                    switch(ImuMap[cName]){
                    case IMU_ACCELX:
                        {scaledaccelx=dataPoint.as_float();
                        imu.set_scaledaccelx(scaledaccelx); break;}
                    case IMU_ACCELY:
                        {scaledaccely=dataPoint.as_float();
                         imu.set_scaledaccely(scaledaccely); break;}
                    case IMU_ACCELZ:
                        {scaledaccelz=dataPoint.as_float();
                        imu.set_scaledaccelz(scaledaccelz); break;}
                    default:
                        {}
                    }

                    
                }

                char cSn[50];
                 auto time = chrono::system_clock::now();
            auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
            long long currentTimeMillis = mill.count();
            int msc = currentTimeMillis % 1000;
            long nowTime = currentTimeMillis/1000;
            tm *ts = localtime(&nowTime);
            
            sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
            ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
                dataFile<<cSn<<","<<scaledaccelx<<","<<scaledaccely<<","<<scaledaccelz<<std::endl;
                //if(count==3){      
                    cout<<"---------send-------------\n";
                    struct timeval tv;
                    gettimeofday(&tv, NULL);
                    cout<<tv.tv_sec<<endl;
                    cout<<tv.tv_usec<<endl;
                    imu.set_timestamp((tv.tv_sec*1000000) + (tv.tv_usec));
                    int data_len = imu.ByteSize();
                    unsigned char data[data_len] = "\0";
                    imu.SerializeToArray(data, data_len);

                    zmq::message_t zmqData(data_len);
                    memcpy((void *)zmqData.data(), data, data_len);
                    m.lock();
                    s_send_idx(*pubSock, SENSOR_IMU);
                    s_send(*pubSock, zmqData);
                    m.unlock();
                    //sleep(5);
                //}
            } // End : read all packet lines
        
            // [Options]
            //usleep (100);
            //sleep(5);
        } // End : while(1)
    } // End : if(USE_IMU==1)
    if(USE_IMU==2){
        while(1){
            sensors::Imu imu;

            // [write fake IMU data]
            float scaledAccelX = rand()%20;
            float scaledAccelY = rand()%20;
            float scaledAccelZ = rand()%10;
            printf("%f %f\n", scaledAccelX, scaledAccelY);
            imu.set_scaledaccelx(scaledAccelX);
            imu.set_scaledaccely(scaledAccelY);
            imu.set_scaledaccelz(scaledAccelZ);
           struct timeval tv;
                    gettimeofday(&tv, NULL);
                    cout<<tv.tv_sec<<endl;
                    cout<<tv.tv_usec<<endl;
                    imu.set_timestamp((tv.tv_sec*1000000) + (tv.tv_usec));
                    int data_len = imu.ByteSize();
                    unsigned char data[data_len] = "\0";
                    imu.SerializeToArray(data, data_len);

                    zmq::message_t zmqData(data_len);
                    memcpy((void *)zmqData.data(), data, data_len);
                    m.lock();
                    s_send_idx(*pubSock, SENSOR_IMU);
                    s_send(*pubSock, zmqData);
                    m.unlock();
                    
            //}
            
            // [Store the GPS data]
            // // <Make json object>
            // Json::Value json_dataset;
            // string path = "imu.json"; // TO-DO: the rule of file name
            // ifstream in(path.c_str());
            // if(in.is_open()) in >> json_dataset;
            // printf("[MobilePlatform/Sensing/ImuSensingThread] Make Json Object (path:%s)\n",path.c_str()); 

            // // <make a json object>
            // Json::Value json_data; 
            // json_data["scaledAccelX"] = to_string(scaledAccelX);
            // json_data["scaledAccelY"] = to_string(scaledAccelY);
            // json_data["scaledAccelZ"] = to_string(scaledAccelZ);
            
            // // <add a json to json_dataset>
            // json_dataset.append(json_data);
            // printf("[MobilePlatform/Sensing/ImuSensingThread] Append a json data\n");
            
            // // <save the json file>
            // Json::StyledWriter jsonWriter;
            // ofstream out(path.c_str());
            // out<<jsonWriter.write(json_dataset);
            // out.close();
            // printf("[MobilePlatform/Sensing/ImuSensingThread] complete to make json file at \"%s\"\n",path.c_str());

            // [Options]
            
            // sleep(1);
        } // End : while(1)
        
        
    } // End : if(USE_IMU==2)
    dataFile.close();
}


void ImuMap_init(){
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