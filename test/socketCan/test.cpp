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

int main(void)
{
	int s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	const char *ifname = "vcan0";

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

	frame.can_id  = 0x123;
	frame.can_dlc = 2;
	frame.data[0] = 0x11;
	frame.data[1] = 0x22;

	nbytes = write(s, &frame, sizeof(struct can_frame));

	sensors::Can can;
	can.set_can_id(frame.can_id);
	can.set_can_dlc(frame.can_dlc);
	size_t data_size = sizeof(frame.data);
	printf("data size= %d\n", data_size);
    can.mutable_data()->resize(data_size);
    memcpy((void*)can.mutable_data()->data(), (void*)frame.data, data_size);

	printf("Wrote %d bytes\n", nbytes);

	printf("start SerializeToArray\n");
	int data_len = can.ByteSize();
    unsigned char data[data_len] = "\0";
    can.SerializeToArray(data, data_len);
    printf("end SerializeToArray\n");
    for (auto i = 0; i < data_len; i++)
        printf("%02X ", data[i]);
    printf("\n");

	
	return 0;
}