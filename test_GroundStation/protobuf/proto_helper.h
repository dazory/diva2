#pragma once
#include <string>
#include <time.h>
#include <google/protobuf/util/time_util.h>

#include "../protobuf/sensors.pb.h"
#include <google/protobuf/text_format.h>

using namespace google::protobuf::util;
using namespace std;

static void proto_gpsReader(sensors::Gps gps, char *cBuff)
{

    char *pSep;
    char *pText;
    int cnt = 0;
    string strBuff[1000];
    gps.set_gpgga(cBuff);

    time_t curTime = time(NULL);
    // gps.set_allocated_timestamp(TimeUtil::TimeTToTimestamp(curTime));

    pText = cBuff;
    pSep = strsep(&pText, ",");
    strBuff[cnt] = string(pSep);
    cnt++;
    if (pSep != NULL && (strcmp(pSep, "$GNGGA") == 0 | strcmp(pSep, "$GPGGA") == 0))
    {
        while ((pSep = strsep(&pText, ",")) != NULL)
        {
            //printf("[%d] pSep=[%s]\n", cnt ,pSep);
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
    }
}

static void proto_gpsDisplay(sensors::Gps gps){
    
	printf("Time = %s\n", "");
    string str;
    gps.SerializeToString(&str);
    google::protobuf::TextFormat::PrintToString(gps, &str);
}