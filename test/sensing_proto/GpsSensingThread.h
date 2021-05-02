#pragma once
#include <iostream>
#include <sstream>
#include <time.h>
#include <sys/timeb.h>

#include "GpsSensing.h"
#include "../service/zmq_helper.h"
#include "../service/Can_serial.h"
#include "../service/Linux_keyboard.h"
#include "../protobuf/sensors.pb.h"
// #include "../protobuf/proto_helper.h"

using namespace std;

extern int USE_GPS;
extern map<string, tuple<string, int>> SensorInfoMap;

class GpsSensingThread
{
public:
    GpsSensingThread();
    static void run(zmq::socket_t *socket);
};

GpsSensingThread::GpsSensingThread()
{
}

void GpsSensingThread::run(zmq::socket_t *socket)
{
    printf("start (in GpsSensingThread::run)\n");

    int iDev = 0;
    int speed = 0;
    Can_serial cs;
    Linux_keyboard lk;
    GpsSensing mGpsSensing;

    if (USE_GPS == 1)
    {
        //iDev = mGpsSensing.initialize(get<0>(SensorInfoMap["GPS"]));
        iDev = mGpsSensing.initialize("/dev/ttyACM0");
        printf("gps.initialize (in GpsSensingThread::run)\n");

        //speed = get<1>(SensorInfoMap["GPS"]);
        speed = B1200;
        printf("baudrate setting (in GpsSensingThread::run)\n");

        cs.init_serial(iDev, speed);
        printf("GPS device connect setting complete! (in GpsSensingThread::run)\n");

        lk.init_keyboard();
        printf("keyboard initialize (in GpsSensingThread::run)\n");
    }

    while (1)
    {
        printf("while(1) start! (in GpsSensingThread::run/while(1))\n");

        // s_send_idx(*socket, SENSOR_GPS);
        printf("send index (in GpsSensingThread::run/while(1))\n");

        /* Read 255bytes from GPS */
        int nRet = 0;
        char cBuff[255];
        if (USE_GPS == 1)
        {
            nRet = read(iDev, cBuff, 255);
            cBuff[nRet] = 0;
            printf("read from device (in GpsSensingThread::run/while(1))");
        }

        if (USE_GPS == 2)
        {
            strcpy(cBuff, "$GNGGA,015442.01,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,,*61");
            printf("read from fake value (in GpsSensingThread::run/while(1))");
        }

        /* Parsing to Proto */
        sensors::Gps gps;
        char *pSep; char *pText; string strBuff[1000];
        int cnt = 0;
        
        // time and raw data
        time_t curTime = time(NULL);
        gps.set_gpgga("$GNGGA,015442.01,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,,*61");
        // gps.set_allocated_timestamp(TimeUtil::TimeTToTimestamp(curTime));

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
            // time [1]
            struct tm tm;
            if (strlen(strBuff[1].c_str()) != 0)
                strptime(strBuff[1].c_str(), "%H%M%S", &tm);
            time_t t = mktime(&tm);
            // gps.set_allocated_timestamp(TimeUtil::TimeTToTimestamp(t)));

            // latitude [2]
            if (strlen(strBuff[2].c_str()) != 0)
                gps.set_latitude(stod(strBuff[2].c_str()));

            // Unknown=0 North=1 South=2 [3]
            string strTmp = strBuff[3];
            if (strcmp(strTmp.c_str(), "N") == 0)
                gps.set_isnorth(true);
            else if (strcmp(strTmp.c_str(), "S") == 0)
                gps.set_isnorth(false);

            // longitude [4]
            if (strlen(strBuff[4].c_str()) != 0)
                gps.set_longitude(stod(strBuff[4].c_str()));

            // Unknown=0 East=1 West=2 [5]
            strTmp = strBuff[5];
            if (strcmp(strTmp.c_str(), "E") == 0)
                gps.set_iseast(true);
            else if (strcmp(strTmp.c_str(), "W") == 0)
                gps.set_iseast(false);

            // GPS Quality [6]
            if (strlen(strBuff[6].c_str()) != 0)
                gps.set_gpsquality(stoi(strBuff[6].c_str()));

            // NumberOfSatellitesInUse [7]
            if (strlen(strBuff[7].c_str()) != 0)
                gps.set_numberofsatellitesinuse(stoi(strBuff[7].c_str()));

            // HorizontalDilutionOfPrecision [8]
            if (strlen(strBuff[8].c_str()) != 0)
                gps.set_horizontaldilutionofprecision(stod(strBuff[8].c_str()));

            // AntennaAltitudeMeters [9]
            string isMeter = strBuff[10];
            if (strlen(strBuff[9].c_str()) != 0)
                gps.set_antennaaltitudemeters(stod(strBuff[9].c_str()));

            // GeoidalSeparationMeters [11]
            string isMeter2 = strBuff[12];
            if (strlen(strBuff[11].c_str()) != 0)
                gps.set_geoidalseparationmeters(stod(strBuff[11].c_str()));

            // AgeOfDifferentialGPSDataSeconds [13]
            if (strlen(strBuff[13].c_str()) != 0)
            {
                gps.set_ageofdifferentialgpsdataseconds(stod(strBuff[13].c_str()));
            }

            // DifferentialReferenceStationID [14]
            if (strlen(strBuff[14].c_str()) != 0)
            {
                gps.set_differentialreferencestationid(stoi(strBuff[14].c_str()));
            }

            // checksum [15]
            string checksum = strBuff[15];
        } // end "Parsing to Proto"


        /* Sender to Cloud with data serialization */
        int data_len = gps.ByteSize();
        unsigned char data[1024] = "\0";
        gps.SerializeToArray(data, data_len);
        for (auto i = 0; i < data_len; i++)
            printf("%02X ", data[i]);
        printf("\n");

        zmq::message_t zmqData(data_len);
        memcpy((void *)zmqData.data(), data, data_len);
        s_send(*socket, zmqData);
        printf("send complete! (in GpsSensingThread::run/while(1))\n");

        /* OPTION */
        sleep(1);
    }

    if (USE_GPS)
    {
        lk.close_keyboard();
        cs.close_serial(iDev);
    }
    printf("terminate complete! (in GpsSensingThread::run/while(1))\n");
}