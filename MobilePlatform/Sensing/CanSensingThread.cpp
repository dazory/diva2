#pragma once
#include "CanSensingThread.h"
#include <unistd.h>

void fromBitToDec(char* data, int bit_start, int bit_length, int* dst);
int fromBytesToDec(char* data, int bit_start, int bit_length);
void sendCAN(int can_type, float can_data, zmq::socket_t *pubSock);

CanSensingThread::CanSensingThread()
{
}

void CanSensingThread::run(zmq::socket_t *pubSock)
{
    printf("[MobilePlatform/Sensing/CanSensingThread] run\n");

    // [Connect CAN device]
    int s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

    const char *ifname = "can0"; // CAN DEVICE NAME

    // <make csv file>
    fstream dataFile;
    dataFile.open("can.csv", ios::out);

    if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1) {
		perror("Error while opening socket");
		exit(-1);
	}

    strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

    printf("[MobilePlatform/Sensing/CanSensingThread] %s at index %d\n", ifname, ifr.ifr_ifindex);

    if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("Error in socket bind");
		exit(-2);
	}

    
    clock_t clk_bef = clock(); 
    time_t clk_now = clock();
    float handleAngle =0.0;
    float turnLight = 0.0;
    float vehicleSpeed = 0.0;
    float gear = 0.0;

    while (1)
    {
        // [Read 255bytes from GPS]
        int nbytes;
		nbytes = read(s, &frame, sizeof(struct can_frame));
		if (nbytes < 0) {
			perror("[MobilePlatform/Sensing/CanSensingThread] Read Error!");
			exit(1);
		}

        int fid = frame.can_id;
		switch (fid)
        {
        case HANDLE_ANGLE: // HANDLE_ANGLE
        {
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
            handleAngle = offset + scale * (float)dec;
			printf("Handle Angle=%fDeg\n",handleAngle);
            
            sendCAN(HANDLE_ANGLE,handleAngle, pubSock);
            dataFile<<clock()<<","<<handleAngle<<","<<turnLight<<","<<vehicleSpeed<<","<<gear<<endl;
        
            break;
        }
        case TURN_LIGHT: // TURN LIGHT
        {
            // (DBC) 주어진 것
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
			int l_bin[bit_length];
			fromBitToDec(data, bit_start, bit_length, l_bin);
			printf("Turn Light : Left(%d) ",l_bin[0]);

            int r_bin[bit_length];
			bit_start = 62;
			bit_length = 1;
			
            fromBitToDec(data, bit_start, bit_length, r_bin);
			printf("Right(%d) \n",r_bin[0]);

            // default(0),  left(1),  right(2),  both(3)
            int dec = 0;
            if(l_bin[0]==1) dec = 1;
            if(r_bin[0]==1) dec = 2;
            if(l_bin[0]==1&&r_bin[0]==1) dec = 3;
            turnLight = dec;
            sendCAN(HANDLE_ANGLE, turnLight, pubSock);
            dataFile<<clock()<<","<<handleAngle<<","<<turnLight<<","<<vehicleSpeed<<","<<gear<<endl;

			usleep(1000);


            break;
        }
        case VEHICLE_SPEED: // VEHICLE SPEED
        {
            // (DBC) 주어진 것
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
            
            vehicleSpeed = (float)(offset+scale*(float)dec);
            sendCAN(HANDLE_ANGLE, vehicleSpeed, pubSock);
            dataFile<<clock()<<","<<handleAngle<<","<<turnLight<<","<<vehicleSpeed<<","<<gear<<endl;
			usleep(1000);
            
            break;
        }
        case GEAR: // GEAR
        {
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

            // default(0),  P(1),  R(2),  N(3),  D(4)
            int dec = 0;
            if(bin[0]) dec = 1;
            if(bin[1]) dec = 2;
            if(bin[2]) dec = 3;
            if(bin[3]) dec = 4;
            gear = dec;
            sendCAN(HANDLE_ANGLE, gear, pubSock);
            dataFile<<clock()<<","<<handleAngle<<","<<turnLight<<","<<vehicleSpeed<<","<<gear<<endl;

			usleep(1000);

            break;
        }
        default:
        {
                break;
        }
        }

        /*
        // [Store the GPS data]
        // <Make json object>
        Json::Value json_dataset;
        string path = "can.json"; // TO-DO: the rule of file name
        ifstream in(path.c_str());
        if(in.is_open()) in >> json_dataset;
        printf("[MobilePlatform/Sensing/CanSensingThread] Make Json Object (path:%s)\n",path.c_str()); 

        Json::Value json_data; 
        // json_data["gpgga"] = string(cBuff); // TO-DO: gpgga?
        json_dataset.append(json_data);
        printf("[MobilePlatform/Sensing/CanSensingThread] Append a json data\n");

        Json::StyledWriter jsonWriter;
        ofstream out(path.c_str());
        out<<jsonWriter.write(json_dataset);
        out.close();
        printf("[MobilePlatform/Sensing/CanSensingThread] complete to make json file at \"%s\"\n",path.c_str());
        */

        // [OPTION]
        usleep(100);
        // sleep(1);
        // <save csv file>
        
    } // end: while(1)
    // <close csv file>
    dataFile.close();

}

void sendCAN(int can_type, float can_data, zmq::socket_t *pubSock){
    // [Parsing to Proto]
    sensors::Can can;
    can.set_type((float)can_type);
    can.set_data(can_data);

    // <Serialization>
    int data_len = can.ByteSize();
    unsigned char data[data_len] = "\0";
    can.SerializeToArray(data, data_len);
    printf("[MobilePlatform/Sensing/CanSensingThread] Serialize\n");
    for (auto i = 0; i < data_len; i++)
        printf("%02X ", data[i]);
    printf("\n");

    // [Send to PUB socket]
    // <Send Message
    zmq::message_t zmqData(data_len);
    memcpy((void *)zmqData.data(), data, data_len);
    s_send_idx(*pubSock, SENSOR_CAN);
    s_send(*pubSock, zmqData);
    printf("[MobilePlatform/Sensing/GpsSensingThread] Complete to send to PUB Socket\n");
        
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