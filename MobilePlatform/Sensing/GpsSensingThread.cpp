#pragma once
#include "GpsSensingThread.h"
#include <unistd.h>

int initialize(string devicename);
void readGPS(int iDev, char *cBuff);

GpsSensingThread::GpsSensingThread()
{
}

void GpsSensingThread::run(zmq::socket_t *pubSock)
{
    printf("[MobilePlatform/Sensing/GpsSensingThread] run\n");

    int iDev = 0;
    int speed = 0;
    Can_serial cs;
    Linux_keyboard lk;
    
    if (USE_GPS == 1) // real
    {
        // [connect GPS device]
        iDev = initialize("/dev/ttyACM0");
        speed = B1200;
        cs.init_serial(iDev, speed);
        lk.init_keyboard();
        printf("[MobilePlatform/Sensing/GpsSensingThread] connect GPS device\n");
    }

    int count=0;
    while (1)
    {
        
        // [Read 255bytes from GPS]
        int nRet = 0;
        char cBuff[255];
        if (USE_GPS == 1)
        {
            nRet = read(iDev, cBuff, 255);
            cBuff[nRet] = 0;
            // printf("(%d) [MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", cnt,nRet); cnt++;
            // printf("%s\n", cBuff);
        }

        if (USE_GPS == 2)
        {
            strcpy(cBuff, "$GNGGA,015442.01,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,,*61");
            printf("[MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", sizeof(cBuff)/sizeof(cBuff[0]));
            printf("%s\n", cBuff);
        }

        // [Parsing to Proto]
        sensors::Gps gps;
        char *pSep; char *pText; string strBuff[1000];
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
                // gps.set_numberofsatellitesinuse(stoi(strBuff[7].c_str()));

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
                // gps.set_differentialreferencestationid(stoi(strBuff[14].c_str()));
            }

            // checksum [15]
            string checksum = strBuff[15];

            // [Send to PUB socket]
            // [Send Topic]
            s_send_idx(*pubSock, SENSOR_GPS);
            // <Serialization>
            int data_len = gps.ByteSize();
            unsigned char data[data_len] = "\0";
            gps.SerializeToArray(data, data_len);
            for (auto i = 0; i < data_len; i++)
                printf("%02X ", data[i]);
            printf("\n");
            printf("[MobilePlatform/Sensing/GpsSensingThread] Serialize\n");

            // <Send>
            zmq::message_t zmqData(data_len);
            memcpy((void *)zmqData.data(), data, data_len);
            s_send(*pubSock, zmqData);
            printf("[MobilePlatform/Sensing/GpsSensingThread] Complete to send to PUB Socket\n");


            printf("(%d) [MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", count,nRet); count++;
            printf("latitude=%f, longitude=%f\n", gps.latitude(), gps.longitude());

        } // end "Parsing to Proto"


        


        // [Store the GPS data]
        // <Make .json File>

        // <Store json file to local storage>
        

        // [OPTION]
        usleep(100);
        // sleep(1);
    } // end: while(1)

    if (USE_GPS)
    {
        lk.close_keyboard();
        cs.close_serial(iDev);
        printf("[MobilePlatform/Sensing/GpsSensingThread] Terminate\n");
    }
}


int initialize(string devname){
	printf("start! (in GpsSensing::initialize)\n");

	const char *devicename = devname.c_str();
	int iDev = open(devicename, O_RDWR | O_NOCTTY);
	if(0>iDev){
		printf("(ERROR) can't open the gps device with devicename(%s) (in GpsSensing::initialize)\n", devicename);
		perror(devicename);
		exit(-100);
	}

	printf("finish! (in GpsSensing::initialize)\n");
    return iDev;
}

void readGPS(int iDev, char *cBuff){
    int nRet = 0;
    if (USE_GPS == 1){
        nRet = read(iDev, cBuff, 255);
        cBuff[nRet] = 0;
        printf("[MobilePlatform/Sensing/GpsSensingThread] read %dbytes from GPS device\n", nRet);
    }else if (USE_GPS == 2){
        strcpy(cBuff, "$GNGGA,015442.01,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,,*61");
        printf("[MobilePlatform/Sensing/GpsSensingThread] read %bytes from GPS device\n",sizeof(cBuff)/sizeof(cBuff[0]));
    }
}