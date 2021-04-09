#pragma once
#include "CanSensing.h"

/* References
    - https://www.beyondlogic.org/example-c-socketcan-code/
    - https://github.com/craigpeacock/CAN-Examples
*/

CanSensing::CanSensing(){
	// mCanPacket = CanPacket();
}

int CanSensing::initialize(string devname){ 
	printf("start! (in CanSensing::initialize)\n");

    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;
    printf("CAN Sockets Demo\r\n");

    if((s=socket(PF_CAN,SOCK_RAW, CAN_RAW))<0){
        perror("Socket");
        return 1;
    }
    strcpy(ifr.ifr_name, devname.c_str());
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if(bind(s, (struct sockaddr *)&addr, sizeof(addr))<0){
        perror("Bind");
        return 1;
    }

    frame.can_id = 0x555;
    frame.can_dlc = 5;
    sprintf((char*)frame.data, "Hello");

    if(write(s, &frame, sizeof(struct can_frame))!=sizeof(struct can_frame)){
        perror("Write");
        return 1;
    }
    
    if(close(s)<0){
        perror("Close");
        return 1;
    }

    return 0;
}

// int CanSensing::getBaudrate(const char * baudrate){
// 	printf("start! (in CanSensing::getBaudrate)\n");

//     Speed_spec *s;
// 	int speed = B9600; //default
// 	for(s = speeds; s->name; s++) {
// 		if(strcmp(s->name, baudrate) == 0) { //same brate in speed_spec 
// 		speed = s->flag; //change spped value to user input
// 		break;
// 		}
// 	}

// 	printf("finish! (in CanSensing::getBaudrate)\n");
//     return speed;
// }

// CanPacket CanSensing::getCanPacket(){
// 	return mCanPacket;
// }