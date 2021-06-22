#pragma once
#include "ImuSensingThread.h"
#include <sys/time.h>

enum IMU
{
    IMU_EXCEPTION = 0,
    IMU_ACCELX,
    IMU_ACCELY,
    IMU_ACCELZ,
    IMU_GYROX,
    IMU_GYROY,
    IMU_GYROZ,
    IMU_MAGX,
    IMU_MAGY,
    IMU_MAGZ,
    IMU_ESTROLL,
    IMU_ESTPITCH,
    IMU_ESTYAW,
    IMU_ESTROLL_UNCERT,
    IMU_ESTPITCH_UNCERT,
    IMU_ESTYAW_UNCERT
};

static map<string, IMU> ImuMap;

void ImuMap_init();

ImuSensingThread::ImuSensingThread()
{
}

void ImuSensingThread::run(zmq::socket_t *pubSock, const char *devicename, mscl::uint32 baudrate, mutex &m)
{
    Timestamp ts;

    printf("[MobilePlatform/Sensing/ImuSensingThread] run (MSCL VER.%s)\n", mscl::MSCL_VERSION.str());
    ImuMap_init();

    time_t system_time;
    struct tm* systime;
    system_time = time(NULL);
    systime = localtime(&system_time);

    string tm_year = to_string(systime->tm_year + 1900);
    string tm_month = to_string(systime->tm_mon+1);
    string tm_date = to_string(systime->tm_mday);
    if(tm_date.size() == 1){
        tm_date = "0"+tm_date;
    }

    string timestamp;
    timestamp = tm_year + tm_month + tm_date;

    // <make csv file>
    string path = "/home/diva2/DIVA2_DATA/"+timestamp+"_0/IMU/i30_IMU_" + ts.getMilliTime() + ".csv";
    fstream dataFile;
    dataFile.open(path, ios::out);

    float scaledaccelx = 0;
    float scaledaccely = 0;
    float scaledaccelz = 0;

    int count = 0;
    if (USE_IMU == 1)
    {
        // [Connect the IMU device]
        // <create the connection object with port and baud rate>
        mscl::Connection connection = mscl::Connection::Serial(devicename, baudrate);

        // <create the InertialNode, passing in the connection>
        mscl::InertialNode msclNode = mscl::InertialNode(connection);
        printf("[MobilePlatform/Sensing/ImuSensingThread] connect to IMU device\n");

        while (1)
        {
            sensors::Imu imu;

            // <Get MipDataPackets>
            mscl::MipDataPackets msclPackets = msclNode.getDataPackets(500);

            for (mscl::MipDataPacket packet : msclPackets)
            {
                packet.descriptorSet();
                mscl::MipDataPoints points = packet.data();

                printf("=========== 읽은 데이터 ===========\n");
                printf("     Channel     |     Value     \n");
                int count = 0;
                for (mscl::MipDataPoint dataPoint : points)
                {
                    // [Parsing to Proto]
                    const char *cName = dataPoint.channelName().c_str();
                    printf("%15s  | %5d : ", cName, ImuMap[cName]);

                    switch (ImuMap[cName])
                    {
                    case IMU_ACCELX:
                    {
                        scaledaccelx = dataPoint.as_float();
                        imu.set_scaledaccelx(scaledaccelx);
                        break;
                    }
                    case IMU_ACCELY:
                    {
                        scaledaccely = dataPoint.as_float();
                        imu.set_scaledaccely(scaledaccely);
                        break;
                    }
                    case IMU_ACCELZ:
                    {
                        scaledaccelz = dataPoint.as_float();
                        imu.set_scaledaccelz(scaledaccelz);
                        break;
                    }
                    default:
                    {
                    }
                    }
                }

                char cSn[50];
                auto time = chrono::system_clock::now();
                auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
                long long currentTimeMillis = mill.count();
                int msc = currentTimeMillis % 1000;
                long nowTime = currentTimeMillis / 1000;
                tm *ts = localtime(&nowTime);

                sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
                        ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
                dataFile << cSn << "," << scaledaccelx << "," << scaledaccely << "," << scaledaccelz << std::endl;
                //if(count==3){
                cout << "---------send-------------\n";
                struct timeval tv;
                gettimeofday(&tv, NULL);
                cout << tv.tv_sec << endl;
                cout << tv.tv_usec << endl;
                imu.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));
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
    }     // End : if(USE_IMU==1)
    if (USE_IMU == 2)
    {
        while (1)
        {
            sensors::Imu imu;

            // [write fake IMU data]
            float scaledAccelX = rand() % 20;
            float scaledAccelY = rand() % 20;
            float scaledAccelZ = rand() % 10;
            printf("%f %f\n", scaledAccelX, scaledAccelY);
            imu.set_scaledaccelx(scaledAccelX);
            imu.set_scaledaccely(scaledAccelY);
            imu.set_scaledaccelz(scaledAccelZ);
            struct timeval tv;
            gettimeofday(&tv, NULL);
            cout << tv.tv_sec << endl;
            cout << tv.tv_usec << endl;
            imu.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));
            int data_len = imu.ByteSize();
            unsigned char data[data_len] = "\0";
            imu.SerializeToArray(data, data_len);

            zmq::message_t zmqData(data_len);
            memcpy((void *)zmqData.data(), data, data_len);
            m.lock();
            s_send_idx(*pubSock, SENSOR_IMU);
            s_send(*pubSock, zmqData);
            m.unlock();

        } // End : while(1)

    } // End : if(USE_IMU==2)
    dataFile.close();
}

void ImuMap_init()
{
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


// void ImuSensingThread::run(const char *devicename, mscl::uint32 baudrate, mutex &m)
// {
//     zmq::context_t context(1);
//     zmq::socket_t socketImu(context, ZMQ_PUB);
//     socketImu.bind(protocol::SENSING_PUB);
//     socketImu.connect("tcp://165.246.39.124:5563");
    
//     Timestamp ts;

//     printf("[MobilePlatform/Sensing/ImuSensingThread] run (MSCL VER.%s)\n", mscl::MSCL_VERSION.str());
//     ImuMap_init();

//     // <make csv file>
//     string path = "/IMU/i30_CAM_ts_" + ts.getMilliTime() + ".csv";
//     fstream dataFile;
//     dataFile.open("imu.csv", ios::out);

//     float scaledaccelx = 0;
//     float scaledaccely = 0;
//     float scaledaccelz = 0;

//     int count = 0;
//     if (USE_IMU == 1)
//     {
//         // [Connect the IMU device]
//         // <create the connection object with port and baud rate>
//         mscl::Connection connection = mscl::Connection::Serial(devicename, baudrate);

//         // <create the InertialNode, passing in the connection>
//         mscl::InertialNode msclNode = mscl::InertialNode(connection);
//         printf("[MobilePlatform/Sensing/ImuSensingThread] connect to IMU device\n");

//         while (1)
//         {
//             sensors::Imu imu;

//             // <Get MipDataPackets>
//             mscl::MipDataPackets msclPackets = msclNode.getDataPackets(500);

//             for (mscl::MipDataPacket packet : msclPackets)
//             {
//                 packet.descriptorSet();
//                 mscl::MipDataPoints points = packet.data();

//                 printf("=========== 읽은 데이터 ===========\n");
//                 printf("     Channel     |     Value     \n");
//                 int count = 0;
//                 for (mscl::MipDataPoint dataPoint : points)
//                 {
//                     // [Parsing to Proto]
//                     const char *cName = dataPoint.channelName().c_str();
//                     printf("%15s  | %5d : ", cName, ImuMap[cName]);

//                     switch (ImuMap[cName])
//                     {
//                     case IMU_ACCELX:
//                     {
//                         scaledaccelx = dataPoint.as_float();
//                         imu.set_scaledaccelx(scaledaccelx);
//                         break;
//                     }
//                     case IMU_ACCELY:
//                     {
//                         scaledaccely = dataPoint.as_float();
//                         imu.set_scaledaccely(scaledaccely);
//                         break;
//                     }
//                     case IMU_ACCELZ:
//                     {
//                         scaledaccelz = dataPoint.as_float();
//                         imu.set_scaledaccelz(scaledaccelz);
//                         break;
//                     }
//                     default:
//                     {
//                     }
//                     }
//                 }

//                 char cSn[50];
//                 auto time = chrono::system_clock::now();
//                 auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
//                 long long currentTimeMillis = mill.count();
//                 int msc = currentTimeMillis % 1000;
//                 long nowTime = currentTimeMillis / 1000;
//                 tm *ts = localtime(&nowTime);

//                 sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
//                         ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
//                 dataFile << cSn << "," << scaledaccelx << "," << scaledaccely << "," << scaledaccelz << std::endl;
//                 //if(count==3){
//                 cout << "---------send-------------\n";
//                 struct timeval tv;
//                 gettimeofday(&tv, NULL);
//                 cout << tv.tv_sec << endl;
//                 cout << tv.tv_usec << endl;
//                 imu.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));
//                 int data_len = imu.ByteSize();
//                 unsigned char data[data_len] = "\0";
//                 imu.SerializeToArray(data, data_len);

//                 zmq::message_t zmqData(data_len);
//                 memcpy((void *)zmqData.data(), data, data_len);
//                 m.lock();
//                 s_send_idx(socketImu, SENSOR_IMU);
//                 s_send(socketImu, zmqData);
//                 m.unlock();
//                 //sleep(5);
//                 //}
//             } // End : read all packet lines

//             // [Options]
//             //usleep (100);
//             //sleep(5);
//         } // End : while(1)
//     }     // End : if(USE_IMU==1)
//     if (USE_IMU == 2)
//     {
//         while (1)
//         {
//             sensors::Imu imu;

//             // [write fake IMU data]
//             float scaledAccelX = rand() % 20;
//             float scaledAccelY = rand() % 20;
//             float scaledAccelZ = rand() % 10;
//             printf("%f %f\n", scaledAccelX, scaledAccelY);
//             imu.set_scaledaccelx(scaledAccelX);
//             imu.set_scaledaccely(scaledAccelY);
//             imu.set_scaledaccelz(scaledAccelZ);
//             struct timeval tv;
//             gettimeofday(&tv, NULL);
//             cout << tv.tv_sec << endl;
//             cout << tv.tv_usec << endl;
//             imu.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));
//             int data_len = imu.ByteSize();
//             unsigned char data[data_len] = "\0";
//             imu.SerializeToArray(data, data_len);

//             zmq::message_t zmqData(data_len);
//             memcpy((void *)zmqData.data(), data, data_len);
//             m.lock();
//             s_send_idx(socketImu, SENSOR_IMU);
//             s_send(socketImu, zmqData);
//             m.unlock();

//         } // End : while(1)

//     } // End : if(USE_IMU==2)
//     dataFile.close();
// }