/* references
    - https://en.wikipedia.org/wiki/SocketCAN
*/
// g++ main.cpp -o main
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "../protobuf/sensors.pb.h"

#include <sstream>
#include <bitset>
#include <boost/algorithm/string.hpp>
#include <iomanip>
//  Created by 전예찬 on 01/02/2019.
//  Copyright © 2019 Esk. All rights reserved.
//  Compiled by Xcode(Apple LLVM version 8.0.0 (clang-800.0.42.1))
//
 
#include <iostream>
#include <stdint.h>
#include <cmath>

void fromBitToDec(char* data, int bit_start, int bit_length, int* dst);
int fromBytesToDec(char* data, int bit_start, int bit_length);

int main(void)
{
	int s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	//const char *ifname = "vcan0";
    const char *ifname = "can0";

	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1) {
		perror("Error while opening socket");
		return -1;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("Error in socket bind");
		return -2;
	}

    while(1){
		int nbytes;
		nbytes = read(s, &frame, sizeof(struct can_frame));
		if (nbytes < 0) {
			perror("Read");
			return 1;
		}

		int fid = frame.can_id;
		// printf("fid = %d\n", fid);
		
		/*
		if(fid==688){ // Handle Angle

			// (DBC) 주어진 것
			int bit_start = 0;
			int bit_length = 16;
			float scale = 0.1;
			float offset = 0;
			
			char data[frame.can_dlc];
			for(int i=0; i<frame.can_dlc; i++){
				data[i] = frame.data[i];
				// printf("%02X ", data[i]);
			}
			int dec = fromBytesToDec(data, bit_start, bit_length);
			printf("Handle Angle=%fDeg\n",offset + scale * (float)dec);

			usleep(1000);
		}
		if(fid == 1345){ // Turn light
			// (DBC) 주어진 것
			// int bit_start = 24;
			// int bit_length = 2;
			// int scale = 1;
			// int offset = 0;
			
			int bit_start = 19;
			int bit_length = 1;
			int scale = 1;
			int offset = 0;

			char data[frame.can_dlc];
			for(int i=0; i<frame.can_dlc; i++){
				data[i] = frame.data[i];
				printf("%02X ", data[i]);
			}
			printf("\n");
			int bin[bit_length];
			fromBitToDec(data, bit_start, bit_length, bin);
			printf("Turn Light : Left(%d) ",bin[0]);

			bit_start = 62;
			bit_length = 1;
			scale = 1;
			offset = 0;

			fromBitToDec(data, bit_start, bit_length, bin);
			printf("Right(%d) \n",bin[0]);

			usleep(1000);

		}
		if(fid == 790){ // Vehicle Speed (790=DIVA) // 1366 rpm
			
			// (DBC) 주어진 것
			// int bit_start = 48;
			// int bit_length = 8;
			// int scale = 1;
			// int offset = 0;
			
			// int bit_start = 16;
			// int bit_length = 16;
			// int scale = 1;
			// int offset = 0;

			int bit_start = 16;
			int bit_length = 16;
			float scale = 0.25;
			int offset = 0;

			char data[frame.can_dlc];
			for(int i=0; i<frame.can_dlc; i++){
				data[i] = frame.data[i];
			}
			int dec = fromBytesToDec(data, bit_start, bit_length);
			printf("Vehicle Speed=%frpm\n",offset + scale * (float)dec);

			usleep(1000);

		}*/
		if(fid == 1322){ // GEAR
			
			// (DBC) 주어진 것
			int bit_start = 9;
			int bit_length = 4;
			int scale = 1;
			int offset = 0;

			char data[frame.can_dlc];
			for(int i=0; i<frame.can_dlc; i++){
				data[i] = frame.data[i];
			}
			int bin[bit_length];
			fromBitToDec(data, bit_start, bit_length, bin);
			printf("Gear : P(%d) R(%d) N(%d) D(%d)\n",bin[0], bin[1], bin[2], bin[3]);

			usleep(1000);
		}
	}
	
	return 0;
}

void fromBitToDec(char* data, int bit_start, int bit_length, int* dst){
	int byte_start = bit_start/8;
    int offset = bit_start % 8;
    // printf("[BIT] from %d (length:%d, offset = %d)\n", bit_start, bit_length, offset);

    // <read to hex>
    // printf("[HEX] \n");
    char hex[1];
    hex[0] = data[byte_start];
    // printf("hex[%d] %02X \n", 0, hex[0]);
    
    // hex to dec
    // printf("[DEC]\n");
    int dec = 0;
    for(int i=0; i<1; i++){
        // dec = (dec << 8) | hex[i];
        // printf("[%d] %d + %d", i, dec*0x100, hex[i]);
        dec = (dec * 0x100) + hex[i];
        // printf(" = %d\n", dec);
    }
    // printf("dec=%d\n",dec);

    // <dec to binary>
    int bin[8];
    // printf("[BIN]\n");
    //for(int i=0; dec>0; i++)    
    for(int i=0; i<8; i++)    
    {    
        bin[i]=dec%2;
        dec= dec/2;
        // printf("[%d] bin=%d dec=%d\n", i, bin[i], dec);
    }

    // <binary parsing>
    // printf("[TARGET]\n");
    for(int i=offset; i<offset+bit_length; i++){
        // printf("bin[%d] = %d = dst[%d]\n", i, bin[i], i-offset);
        // bin[7-i]
        dst[i-offset] = bin[i];
    }

}

int fromBytesToDec(char* data, int bit_start, int bit_length){
	// <bit to byte>
    int byte_start = bit_start/8;
    int byte_length = bit_length/8;
    // printf("[BYTE] from %d (length:%d)\n", byte_start, byte_length);

    // <read to hex>
    // printf("[HEX] \n");
    char hex[8] = {0};
    for(int i=byte_start; i<byte_start+byte_length; i++){
        hex[i-byte_start] = data[i];
        // printf("hex[%d] %02X \n", i-byte_start, hex[i-byte_start]);
    }
    hex[byte_length] = '\0';

    // <little endian>
    // printf("[LITTLE ENDIAN] \n");
    char tmp;
    for(int i=0; i<byte_length/2; i++){
        tmp = hex[i];
        hex[i] = hex[byte_length-i-1];
        hex[byte_length-i-1]=tmp;
        
    }
    for(int i=0; i<byte_length; i++){
        // printf("hex[%d] = %02X\n", i, hex[i]);
    }
    
    // hex to dec
    // printf("[DEC]\n");
    int dec = 0;
    for(int i=0; i<byte_length; i++){
        // dec = (dec << 8) | hex[i];
        // printf("[%d] %d + %d", i, dec*0x100, hex[i]);
        dec = (dec * 0x100) + hex[i];
        // printf(" = %d\n", dec);
    }
    // printf("dec=%d\n",dec);
	return dec;
}