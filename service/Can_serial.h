// diva2/test/sensor_connection/Can_serial.cpp

#ifndef Can_serial_h
#define Can_serial_h

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>

class Can_serial{
public:

	struct termios stOldState;
	struct termios stNewState;

	void init_serial(int iDev, int speed){
		tcgetattr(iDev, &stOldState);
		bzero(&stNewState, sizeof(stNewState));

		stNewState.c_cflag = speed | CRTSCTS | CS8 | CLOCAL | CREAD;
		stNewState.c_iflag = IGNPAR | ICRNL;
		stNewState.c_oflag = 0;
		stNewState.c_lflag = ICANON;
		bzero(stNewState.c_cc, NCCS);
		stNewState.c_cc[VMIN] = 1;

		tcflush(iDev, TCIFLUSH);
		tcsetattr(iDev, TCSANOW, &stNewState);
	}

	void close_serial(int iDev){
		// tcsetattr(iDev, TCSANOW, &stOldState);
		// close(iDev);
	}


};

#endif