#pragma once
#include "GpsSensing.h"

Speed_spec speeds[] = {
	
	{"1200", B1200},
	{"2400", B2400},
	{"4800", B4800},
	{"9600", B9600},
	{"19200", B19200},
	{"38400", B38400},
	{"57600", B57600},
	{"115200", B115200},
	{NULL, 0}
};

GpsSensing::GpsSensing(){
	mGpsPacket = GpsPacket();
}

int GpsSensing::initialize(string devname){ //const char *devname
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

int GpsSensing::getBaudrate(const char * baudrate){
	printf("start! (in GpsSensing::getBaudrate)\n");

    Speed_spec *s;
	int speed = B9600; //default
	for(s = speeds; s->name; s++) {
		if(strcmp(s->name, baudrate) == 0) { //same brate in speed_spec 
		speed = s->flag; //change spped value to user input
		break;
		}
	}

	printf("finish! (in GpsSensing::getBaudrate)\n");
    return speed;
}

GpsPacket GpsSensing::getGpsPacket(){
	return mGpsPacket;
}