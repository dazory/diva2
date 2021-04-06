// data_format/gps_packet.h
#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
using namespace std;

class GpsPacket {
public:
    GpsPacket();
    //int initialize(const char *devicename);

    /* DATA */ // 참고: https://github.com/SammyB428/NMEA0183/blob/master/GGA.HPP
    time_t Time;
    double Latitude;
    int NorthSouth;
    double Longitude;
    int EastWest;
    int GPSQuality;
    int NumberOfSatellitesInUse;
    double HorizontalDilutionOfPrecision;
    double AntennaAltitudeMeters;
    double GeoidalSeparationMeters;
    double AgeOfDifferentialGPSDataSeconds;
    int DifferentialReferenceStationID;

	/* FUNCTION */
    void displayGpsPacket();
    void readGpsPacket(char *cBuff);
private:

};

GpsPacket::GpsPacket(){
    Time = 0;
    Latitude = 0.0;
    NorthSouth = 0;
    Longitude = 0.0;
    EastWest = 0;
    GPSQuality = 0;
    NumberOfSatellitesInUse = 0;
    HorizontalDilutionOfPrecision = 0.0;
    AntennaAltitudeMeters = 0.0 ;
    GeoidalSeparationMeters = 0.0;
    AgeOfDifferentialGPSDataSeconds = 0.0 ;
    DifferentialReferenceStationID= 0;
}

void GpsPacket::displayGpsPacket(){
    
    struct tm *tm = localtime(&Time);
    char buffer[32];
	std::strftime(buffer, 32, "%H:%M:%S", tm);  
	printf("Time = %s\n", buffer);
    printf("Latitude = %f\n", Latitude);
    printf("NorthSouth = %d\n", NorthSouth);
    printf("Longitude = %f\n", Longitude);
    printf("EastWest = %d\n", EastWest);
    printf("GPSQuality = %d\n", GPSQuality);
    printf("NumberOfSatellitesInUse = %d\n", NumberOfSatellitesInUse);
    printf("HorizontalDilutionOfPrecision = %f\n", HorizontalDilutionOfPrecision);
    printf("AntennaAltitudeMeters = %f\n", AntennaAltitudeMeters);
    printf("GeoidalSeparationMeters = %f\n", GeoidalSeparationMeters);
    printf("AgeOfDifferentialGPSDataSeconds = %f\n", AgeOfDifferentialGPSDataSeconds);
    printf("DifferentialReferenceStationID = %d\n", DifferentialReferenceStationID);
}

void GpsPacket::readGpsPacket(char* cBuff){    
    char *pSep; char*pText; int cnt=0; string strBuff[1000];
			pText = cBuff;
			pSep = strsep(&pText,",");
			strBuff[cnt] = string(pSep); cnt++;
			if(pSep!=NULL && (strcmp(pSep, "$GNGGA")==0 | strcmp(pSep, "$GPGGA")==0)){
				while((pSep = strsep(&pText,","))!=NULL){
					//printf("[%d] pSep=[%s]\n", cnt ,pSep);
					strBuff[cnt++] = string(pSep);
				}
				// time [1]
				struct tm tm;
				if(strlen(strBuff[1].c_str())!=0) strptime(strBuff[1].c_str(), "%H%M%S", &tm);
				time_t t = mktime(&tm);
				Time = t;

				// latitude [2]
				if(strlen(strBuff[2].c_str())!=0) Latitude = stod(strBuff[2].c_str());

				// Unknown=0 North=1 South=2 [3]
				string strTmp = strBuff[3];
				if(strcmp(strTmp.c_str(),"N")==0) NorthSouth=1;
				else if(strcmp(strTmp.c_str(),"S")==0) NorthSouth=2;
				
				// longitude [4]
				if(strlen(strBuff[4].c_str())!=0) Longitude = stod(strBuff[4].c_str());
				
				// Unknown=0 East=1 West=2 [5]
				strTmp = strBuff[5];
				if(strcmp(strTmp.c_str(),"E")==0) EastWest=1;
				else if(strcmp(strTmp.c_str(),"W")==0) EastWest=2;
				
				// GPS Quality [6]
				if(strlen(strBuff[6].c_str())!=0) GPSQuality = stoi(strBuff[6].c_str());
				
				// NumberOfSatellitesInUse [7] 
				if(strlen(strBuff[7].c_str())!=0) NumberOfSatellitesInUse = stoi(strBuff[7].c_str());
				
				// HorizontalDilutionOfPrecision [8]
				if(strlen(strBuff[8].c_str())!=0) HorizontalDilutionOfPrecision = stod(strBuff[8].c_str());
				
				// AntennaAltitudeMeters [9]
				string isMeter = strBuff[10];
				if(strlen(strBuff[9].c_str())!=0) AntennaAltitudeMeters = stod(strBuff[9].c_str());
				
				// GeoidalSeparationMeters [11]
				string isMeter2 = strBuff[12];
				if(strlen(strBuff[11].c_str())!=0) GeoidalSeparationMeters = stod(strBuff[11].c_str());
				
				// AgeOfDifferentialGPSDataSeconds [13]
				if(strlen(strBuff[13].c_str())!=0) { AgeOfDifferentialGPSDataSeconds = stod(strBuff[13].c_str());}
				
				// DifferentialReferenceStationID [14]
				if(strlen(strBuff[14].c_str())!=0){DifferentialReferenceStationID = stoi(strBuff[14].c_str());}
				
				// checksum [15]
				string checksum = strBuff[15];
			}
    /*
            char *pSep; char*pText; int cnt=0; string strBuff[1000];
			pText = cBuff;
			pSep = strsep(&pText,",");
			strBuff[cnt] = string(pSep); cnt++;
			if(pSep!=NULL && (strcmp(pSep, "$GNGGA")==0 | strcmp(pSep, "$GPGGA")==0)){
				while((pSep = strsep(&pText,","))!=NULL){
					printf("[%d] pSep=[%s]\n", cnt ,pSep);
					strBuff[cnt++] = string(pSep);
				}
				// time [1]
				struct tm tm;
				if(strlen(strBuff[1].c_str())!=0) strptime(strBuff[1].c_str(), "%H%M%S", &tm);
				time_t t = mktime(&tm);
				mGpsPacket.Time = t;

				// latitude [2]
				if(strlen(strBuff[2].c_str())!=0) mGpsPacket.Latitude = stod(strBuff[2].c_str());

				// Unknown=0 North=1 South=2 [3]
				string strTmp = strBuff[3];
				if(strcmp(strTmp.c_str(),"N")==0) mGpsPacket.NorthSouth=1;
				else if(strcmp(strTmp.c_str(),"S")==0) mGpsPacket.NorthSouth=2;
				
				// longitude [4]
				if(strlen(strBuff[4].c_str())!=0) mGpsPacket.Longitude = stod(strBuff[4].c_str());
				
				// Unknown=0 East=1 West=2 [5]
				strTmp = strBuff[5];
				if(strcmp(strTmp.c_str(),"E")==0) mGpsPacket.EastWest=1;
				else if(strcmp(strTmp.c_str(),"W")==0) mGpsPacket.EastWest=2;
				
				// GPS Quality [6]
				if(strlen(strBuff[6].c_str())!=0) mGpsPacket.GPSQuality = stoi(strBuff[6].c_str());
				
				// NumberOfSatellitesInUse [7] 
				if(strlen(strBuff[7].c_str())!=0) mGpsPacket.NumberOfSatellitesInUse = stoi(strBuff[7].c_str());
				
				// HorizontalDilutionOfPrecision [8]
				if(strlen(strBuff[8].c_str())!=0) mGpsPacket.HorizontalDilutionOfPrecision = stod(strBuff[8].c_str());
				
				// AntennaAltitudeMeters [9]
				string isMeter = strBuff[10];
				if(strlen(strBuff[9].c_str())!=0) mGpsPacket.AntennaAltitudeMeters = stod(strBuff[9].c_str());
				
				// GeoidalSeparationMeters [11]
				string isMeter2 = strBuff[12];
				if(strlen(strBuff[11].c_str())!=0) mGpsPacket.GeoidalSeparationMeters = stod(strBuff[11].c_str());
				
				// AgeOfDifferentialGPSDataSeconds [13]
				if(strlen(strBuff[13].c_str())!=0) { mGpsPacket.AgeOfDifferentialGPSDataSeconds = stod(strBuff[13].c_str());}
				
				// DifferentialReferenceStationID [14]
				if(strlen(strBuff[14].c_str())!=0){mGpsPacket.DifferentialReferenceStationID = stoi(strBuff[14].c_str());}
				
				// checksum [15]
				string checksum = strBuff[15];

				mGpsPacket.displayGpsPacket();
			}*/
}