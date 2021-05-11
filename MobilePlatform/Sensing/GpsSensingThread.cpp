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

    clock_t clk_bef = clock(); 
    time_t clk_now = clock();
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
            /* GPGGA
            [1] time
            [2] latitude
            [3] Unknown=0 North=1 South=2
            [4] longitude
            [5] Unknown=0 East=1 West=2
            [6] GPS Quality
            [7] NumberOfSatellitesInUse
            [8] HorizontalDilutionOfPrecision
            [9] AntennaAltitudeMeters
            [11] GeoidalSeparationMeters
            [13] AgeOfDifferentialGPSDataSeconds
            [14] DifferentialReferenceStationID
            [15] checksum
            */
            
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
            printf("[MobilePlatform/Sensing/GpsSensingThread] Serialize\n");
            for (auto i = 0; i < data_len; i++)
                printf("%02X ", data[i]);
            printf("\n");

            // <Send Message
            clk_now = clock();
            if((float)(clk_now - clk_bef)/CLOCKS_PER_SEC >= 0.1)
            {
                zmq::message_t zmqData(data_len);
                memcpy((void *)zmqData.data(), data, data_len);
                s_send_idx(*pubSock, SENSOR_GPS);
                s_send(*pubSock, zmqData);
                printf("(%dms)[MobilePlatform/Sensing/GpsSensingThread] Complete to send to PUB Socket\n", ((float)(clk_now-clk_bef)/CLOCKS_PER_SEC)*1000);
                clk_bef = clk_now;
            }
        } // end "Parsing to Proto"

        // [Store the GPS data]
        // <Make json object>
        Json::Value json_dataset;
        
        string path = "gps.json"; // TO-DO: the rule of file name
        ifstream in(path.c_str());
        if(in.is_open()) in >> json_dataset;
        printf("[MobilePlatform/Sensing/GpsSensingThread] Make Json Object (path:%s)\n",path.c_str()); 

        Json::Value json_data; 
        // json_data["gpgga"] = string(cBuff); // TO-DO: gpgga?
        json_data["latitude"] = strBuff[2]; 
        json_data["isNorth"] = strBuff[3]; 
        json_data["longitude"] = strBuff[4]; 
        json_data["isEast"] = strBuff[5]; 
        json_data["gpsQuality"] = strBuff[6]; 
        json_data["NumberOfSatellitesInUse"] = strBuff[7]; 
        json_data["HorizontalDilutionOfPrecision"] = strBuff[8];
        json_data["AntennaAltitudeMeters"] = strBuff[9];
        json_data["GeoidalSeparationMeters"] = strBuff[11];
        json_data["AgeOfDifferentialGPSDataSeconds"] = strBuff[13];
        json_data["DifferentialReferenceStationID"] = strBuff[14];
        json_data["checksum"] = strBuff[15];
        json_dataset.append(json_data);
        printf("[MobilePlatform/Sensing/GpsSensingThread] Append a json data\n");

        Json::StyledWriter jsonWriter;
        ofstream out(path.c_str());
        out<<jsonWriter.write(json_dataset);
        out.close();
        printf("[MobilePlatform/Sensing/GpsSensingThread] complete to make json file at \"%s\"\n",path.c_str());
        
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