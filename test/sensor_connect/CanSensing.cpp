// #pragma once
// #include "CanSensing.h"

// /* 참고
//     예제 C SocketCAN 코드: https://www.beyondlogic.org/example-c-socketcan-code/
//     can_frame 구조: include/linux/can.h

// */

// CanSensing::CanSensing(){
	
// }

// int CanSensing::getSocket(const char *devname){ // devname = "can0" (or dev1, vcan0 etc.)
//     printf("start! (in CanSensing::initialize)\n");

//     int s;
//     if((s=socket(PF_CAN, SOCK_RAW, CAN_RAW))<0){
// 		printf("(ERROR) Fail to create a socket (in CanSensing::initialize)\n");
//         return 1;
//     }
//     printf("Accepts three parameters (domain/protocol family(PF_CAN), type of socket(raw or datagram) and socket protocol (in CanSensing::initialize)\n");

//     struct ifreq ifr;
//     strcpy(ifr.ifr_name, devname);
//     ioctl(s, SIOCGIFINDEX, &ifr);
//     printf("사용할 인터페이스 이름(%s)에 대한 인터페이스 인덱스를 검색 (in CanSensing::initialize)\n", devname);

//     struct sockaddr_can addr;
//     memset(&addr, 0, sizeof(addr));
//     addr.can_family = AF_CAN;
//     addr.can_ifindex = ifr.ifr_ifindex;

//     if(bind(s,(struct sockaddr *)&addr, sizeof(addr))<0){
//         printf("(ERROR) Fail to bind the socket to the CAN interface (in CanSensing::initialize)\n");
//         perror("Bind");
//         return 1;
//     }
//     printf("Binding the socket to the CAN interface (in CanSensing::initialize)\n");

//     return s;
// }
