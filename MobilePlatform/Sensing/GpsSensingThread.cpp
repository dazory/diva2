#pragma once
#include "GpsSensingThread.h"
#include <unistd.h>
#include <sys/time.h>

int initialize(string devicename);
void readGPS(int iDev, char *cBuff);

GpsSensingThread::GpsSensingThread()
{
}

void GpsSensingThread::run(zmq::socket_t *pubSock, mutex &m)
{
    Timestamp ts;
    printf("[MobilePlatform/Sensing/GpsSensingThread] run\n");

    int iDev = 0;
    int speed = 0;
    Can_serial cs;
    Linux_keyboard lk;

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
    string path = "/home/diva2/DIVA2_DATA/"+timestamp+"_0/GPS/i30_GPS_" + ts.getMilliTime() + ".csv";
    fstream dataFile;
    dataFile.open(path, ios::out);

    if (USE_GPS == 1) // real
    {
        // [connect GPS device]
        iDev = initialize("/dev/ttyACM0");
        speed = B9600;
        cs.init_serial(iDev, speed);
        lk.init_keyboard();
        printf("[MobilePlatform/Sensing/GpsSensingThread] connect GPS device\n");
    }

    clock_t clk_bef = clock();
    time_t clk_now = clock();

    while (1)
    {
        // [Read 255bytes from GPS]
        int nRet = 0;
        char cBuff[526];
        sensors::Gps gps;
        if (USE_GPS == 1)
        {
            nRet = read(iDev, cBuff, 526);
            cBuff[nRet] = 0;
            //cout<<cBuff<<endl;
            // < timestamp >
            struct timeval tv;
            gettimeofday(&tv, NULL);
            gps.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));

            // printf("(%d) [MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", cnt,nRet); cnt++;
            printf("%s\n", cBuff);
        }

        if (USE_GPS == 2)
        {
            strcpy(cBuff, "$GNGGA,015442.01,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,,*61");
            printf("[MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", sizeof(cBuff) / sizeof(cBuff[0]));
            printf("%s\n", cBuff);
            struct timeval tv;
            gettimeofday(&tv, NULL);
            gps.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));
        }

        // [Parsing to Proto]
        char *pSep;
        char *pText;
        string strBuff[1000];
        int cnt = 0;

        pText = cBuff;
        pSep = strsep(&pText, ",");
        strBuff[cnt] = string(pSep);
        cnt++;
        if (pSep != NULL && (strcmp(pSep, "$GNGGA") == 0 | strcmp(pSep, "$GPGGA") == 0))
        {
            while ((pSep = strsep(&pText, ",")) != NULL)
            {
                strBuff[cnt++] = string(pSep);
            }
            // latitude
            if (strlen(strBuff[2].c_str()) != 0)
                gps.set_latitude(stod(strBuff[2].c_str()));

            // longitude
            if (strlen(strBuff[4].c_str()) != 0)
                gps.set_longitude(stod(strBuff[4].c_str()));

            // HorizontalDilutionOfPrecision
            if (strlen(strBuff[8].c_str()) != 0)
                gps.set_horizontaldilutionofprecision(stod(strBuff[8].c_str()));

            // [Send to PUB socket]
            // <Serialization>
            int data_len = gps.ByteSize();
            unsigned char data[data_len] = "\0";
            gps.SerializeToArray(data, data_len);

            // <Send Message>
            zmq::message_t zmqData(data_len);
            memcpy((void *)zmqData.data(), data, data_len);
            m.lock();
            s_send_idx(*pubSock, SENSOR_GPS);
            s_send(*pubSock, zmqData);
            m.unlock();

            char cSn[50];

            //timestamp
            auto time = chrono::system_clock::now();
            auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
            long long currentTimeMillis = mill.count();
            int msc = currentTimeMillis % 1000;
            long nowTime = currentTimeMillis / 1000;
            tm *ts = localtime(&nowTime);

            sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
                    ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
            // <save csv file>
            cout << cSn << endl;
            dataFile << cSn << "," << strBuff[2] << "," << strBuff[4] << "," << strBuff[8] << std::endl;

        } // end "Parsing to Proto"

    } // end: while(1)
    // <close csv file>
    dataFile.close();

    if (USE_GPS)
    {
        lk.close_keyboard();
        cs.close_serial(iDev);
        printf("[MobilePlatform/Sensing/GpsSensingThread] Terminate\n");
    }
}

int initialize(string devname)
{
    printf("start! (in GpsSensing::initialize)\n");

    const char *devicename = devname.c_str();
    int iDev = open(devicename, O_RDWR | O_NOCTTY);
    if (0 > iDev)
    {
        printf("(ERROR) can't open the gps device with devicename(%s) (in GpsSensing::initialize)\n", devicename);
        perror(devicename);
        exit(-100);
    }

    printf("finish! (in GpsSensing::initialize)\n");
    return iDev;
}

void readGPS(int iDev, char *cBuff)
{
    int nRet = 0;
    if (USE_GPS == 1)
    {
        nRet = read(iDev, cBuff, 255);
        cBuff[nRet] = 0;
        printf("[MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", nRet);
    }
    else if (USE_GPS == 2)
    {
        strcpy(cBuff, "$GNGGA,015442.01,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,,*61");
        printf("[MobilePlatform/Sensing/GpsSensingThread] read %bytes from GPS device\n", sizeof(cBuff) / sizeof(cBuff[0]));
    }
}


// void GpsSensingThread::run( mutex &m)
// {
//     zmq::context_t context(1);
//     zmq::socket_t socketGps(context, ZMQ_PUB);
//     socketGps.bind(protocol::SENSING_PUB);
//     socketGps.connect("tcp://165.246.39.124:5562");
//     Timestamp ts;
//     printf("[MobilePlatform/Sensing/GpsSensingThread] run\n");

//     int iDev = 0;
//     int speed = 0;
//     Can_serial cs;
//     Linux_keyboard lk;

//     // <make csv file>
//     string path = "/GPS/i30_GPS_" + ts.getMilliTime() + ".csv";
//     fstream dataFile;
//     dataFile.open("gps.csv", ios::out);

//     if (USE_GPS == 1) // real
//     {
//         // [connect GPS device]
//         iDev = initialize("/dev/ttyACM1");
//         speed = B9600;
//         cs.init_serial(iDev, speed);
//         lk.init_keyboard();
//         printf("[MobilePlatform/Sensing/GpsSensingThread] connect GPS device\n");
//     }

//     clock_t clk_bef = clock();
//     time_t clk_now = clock();

//     while (1)
//     {
//         // [Read 255bytes from GPS]
//         int nRet = 0;
//         char cBuff[526];
//         sensors::Gps gps;
//         if (USE_GPS == 1)
//         {
//             nRet = read(iDev, cBuff, 526);
//             cBuff[nRet] = 0;
//             //cout<<cBuff<<endl;
//             // < timestamp >
//             struct timeval tv;
//             gettimeofday(&tv, NULL);
//             gps.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));

//             // printf("(%d) [MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", cnt,nRet); cnt++;
//             printf("%s\n", cBuff);
//         }

//         if (USE_GPS == 2)
//         {
//             strcpy(cBuff, "$GNGGA,015442.01,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,,*61");
//             printf("[MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", sizeof(cBuff) / sizeof(cBuff[0]));
//             printf("%s\n", cBuff);
//             struct timeval tv;
//             gettimeofday(&tv, NULL);
//             gps.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));
//         }

//         // [Parsing to Proto]
//         char *pSep;
//         char *pText;
//         string strBuff[1000];
//         int cnt = 0;

//         pText = cBuff;
//         pSep = strsep(&pText, ",");
//         strBuff[cnt] = string(pSep);
//         cnt++;
//         if (pSep != NULL && (strcmp(pSep, "$GNGGA") == 0 | strcmp(pSep, "$GPGGA") == 0))
//         {
//             while ((pSep = strsep(&pText, ",")) != NULL)
//             {
//                 strBuff[cnt++] = string(pSep);
//             }
//             // latitude
//             if (strlen(strBuff[2].c_str()) != 0)
//                 gps.set_latitude(stod(strBuff[2].c_str()));

//             // longitude
//             if (strlen(strBuff[4].c_str()) != 0)
//                 gps.set_longitude(stod(strBuff[4].c_str()));

//             // HorizontalDilutionOfPrecision
//             if (strlen(strBuff[8].c_str()) != 0)
//                 gps.set_horizontaldilutionofprecision(stod(strBuff[8].c_str()));

//             // [Send to PUB socket]
//             // <Serialization>
//             int data_len = gps.ByteSize();
//             unsigned char data[data_len] = "\0";
//             gps.SerializeToArray(data, data_len);

//             // <Send Message>
//             zmq::message_t zmqData(data_len);
//             memcpy((void *)zmqData.data(), data, data_len);
//             m.lock();
//             s_send_idx(socketGps, SENSOR_GPS);
//             s_send(socketGps, zmqData);
//             m.unlock();

//             char cSn[50];

//             //timestamp
//             auto time = chrono::system_clock::now();
//             auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
//             long long currentTimeMillis = mill.count();
//             int msc = currentTimeMillis % 1000;
//             long nowTime = currentTimeMillis / 1000;
//             tm *ts = localtime(&nowTime);

//             sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
//                     ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);
//             // <save csv file>
//             cout << cSn << endl;
//             dataFile << cSn << "," << strBuff[2] << "," << strBuff[4] << "," << strBuff[8] << std::endl;

//         } // end "Parsing to Proto"

//     } // end: while(1)
//     // <close csv file>
//     dataFile.close();

//     if (USE_GPS)
//     {
//         lk.close_keyboard();
//         cs.close_serial(iDev);
//         printf("[MobilePlatform/Sensing/GpsSensingThread] Terminate\n");
//     }
// }
