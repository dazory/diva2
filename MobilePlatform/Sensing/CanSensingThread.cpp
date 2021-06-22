#pragma once
#include "CanSensingThread.h"
#include <unistd.h>
#include <sys/time.h>

#include <mutex>
std::mutex mtx_lock2;

void fromBitToDec(char *data, int bit_start, int bit_length, int *dst);
int fromBytesToDec(char *data, int bit_start, int bit_length);
// void sendCAN(int can_type, float can_data, zmq::socket_t *pubSock);
void sendCAN(sensors::Can can, zmq::socket_t *pubSock, mutex &m);

CanSensingThread::CanSensingThread()
{
}

void CanSensingThread::run(zmq::socket_t *pubSock, mutex &m)
{
    Timestamp ts;
    printf("[MobilePlatform/Sensing/CanSensingThread] run\n");

    // [Connect CAN device]
    int s;
    int nbytes;
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

    float handleAngle = 0.0;
    float turnLight = 0.0;
    float vehicleSpeed = 0.0;
    float gear = 0.0;

    const char *ifname = "can0"; // CAN DEVICE NAME

    time_t system_time;
    struct tm* systime;
    system_time = time(NULL);
    systime = localtime(&system_time);

    string tm_year = to_string(systime->tm_year + 1900);
    string tm_month = to_string(systime->tm_mon+1);
    string tm_date = to_string(systime->tm_mday);
    if(tm_date.size() == 1){
        tm_date = "0"+tm_date;
    }

    string timestamp;
    timestamp = tm_year + tm_month + tm_date;

    // <make csv file>
    string path = "/home/diva2/DIVA2_DATA/"+timestamp+"_0/CAN/i30_CAN_" + ts.getMilliTime() + ".csv";
    fstream dataFile;
    dataFile.open(path, ios::out);

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1)
    {
        perror("Error while opening socket");
        exit(-1);
    }

    strcpy(ifr.ifr_name, ifname);
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    printf("[MobilePlatform/Sensing/CanSensingThread] %s at index %d\n", ifname, ifr.ifr_ifindex);

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("Error in socket bind");
        exit(-2);
    }

    while (1)
    {
        // [Read 255bytes from GPS]
        int nbytes;
        nbytes = read(s, &frame, sizeof(struct can_frame));

        // < timestamp >
        sensors::Can can;
        struct timeval tv;
        gettimeofday(&tv, NULL);
        can.set_timestamp((tv.tv_sec * 1000000) + (tv.tv_usec));

        if (nbytes < 0)
        {
            perror("[MobilePlatform/Sensing/CanSensingThread] Read Error!");
            exit(1);
        }

        char cSn[50];

        //timestamp
        auto time = chrono::system_clock::now();
        auto mill = chrono::duration_cast<chrono::milliseconds>(time.time_since_epoch());
        long long currentTimeMillis = mill.count();
        int msc = currentTimeMillis % 1000;
        long nowTime = currentTimeMillis / 1000;
        tm *ts = localtime(&nowTime);

        sprintf(cSn, "%04d%02d%02d%02d%02d%02d%03d",
                ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, msc);

        int fid = frame.can_id;
        // printf("fid: %d\n", fid);
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
            for (int i = 0; i < frame.can_dlc; i++)
            {
                data[i] = frame.data[i];
                printf("%02X ", data[i]);
            }
            int dec = fromBytesToDec(data, bit_start, bit_length);
            handleAngle = offset + scale * (float)dec;
            printf("Handle Angle=%fDeg\n", offset + scale * (float)dec);

            // [send CAN]
            can.set_type(HANDLE_ANGLE);
            can.set_data(handleAngle);
            sendCAN(can, pubSock, m);

            dataFile << cSn << "," << handleAngle << "," << turnLight << "," << vehicleSpeed << "," << gear << endl;
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
            for (int i = 0; i < frame.can_dlc; i++)
            {
                data[i] = frame.data[i];
                // printf("%02X ", data[i]);
            }
            // printf("\n");
            int l_bin[bit_length];
            fromBitToDec(data, bit_start, bit_length, l_bin);
            printf("Turn Light : Left(%d) ", l_bin[0]);

            int r_bin[bit_length];
            bit_start = 62;
            bit_length = 1;

            fromBitToDec(data, bit_start, bit_length, r_bin);
            printf("Right(%d) \n", r_bin[0]);

            // default(0),  left(1),  right(2),  both(3)
            int dec = 0;
            if (l_bin[0] == 1)
                dec = 1;
            if (r_bin[0] == 1)
                dec = 2;
            if (l_bin[0] == 1 && r_bin[0] == 1)
                dec = 3;

            turnLight = dec;
            // [send CAN]
            // sendCAN(TURN_LIGHT, (float)dec, pubSock);
            can.set_type(TURN_LIGHT);
            can.set_data(turnLight);
            sendCAN(can, pubSock, m);
            dataFile << cSn << "," << handleAngle << "," << turnLight << "," << vehicleSpeed << "," << gear << endl;

            usleep(10000);

            break;
        }
        case VEHICLE_SPEED: // VEHICLE SPEED
        {
            // (DBC) 주어진 것
            // int bit_start = 16;
            // int bit_length = 16;
            // float scale = 0.25;
            // int offset = 0;

            int bit_start = 48;
            int bit_length = 8;
            float scale = 1.0;
            int offset = 0;

            char data[frame.can_dlc];
            for (int i = 0; i < frame.can_dlc; i++)
            {
                data[i] = frame.data[i];
            }
            int dec = fromBytesToDec(data, bit_start, bit_length);
            printf("Vehicle Speed=%frpm\n", offset + scale * (float)dec);

            vehicleSpeed = (float)(offset + scale * (float)dec);
            // [send CAN]
            // sendCAN(VEHICLE_SPEED, (float)(offset+scale*(float)dec), pubSock);
            can.set_type(VEHICLE_SPEED);
            can.set_data(vehicleSpeed);
            sendCAN(can, pubSock, m);
            dataFile << cSn << "," << handleAngle << "," << turnLight << "," << vehicleSpeed << "," << gear << endl;

            usleep(10000);

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
            for (int i = 0; i < frame.can_dlc; i++)
            {
                data[i] = frame.data[i];
            }
            int bin[bit_length];
            fromBitToDec(data, bit_start, bit_length, bin);
            printf("Gear : P(%d) R(%d) N(%d) D(%d)\n", bin[0], bin[1], bin[2], bin[3]);

            // default(0),  P(1),  R(2),  N(3),  D(4)
            int dec = 0;
            if (bin[0])
                dec = 1;
            if (bin[1])
                dec = 2;
            if (bin[2])
                dec = 3;
            if (bin[3])
                dec = 4;
            gear = dec;
            // [send CAN]
            // sendCAN(GEAR, (float)dec, pubSock);
            can.set_type(GEAR);
            can.set_data((float)dec);
            sendCAN(can, pubSock, m);
            dataFile << cSn << "," << handleAngle << "," << turnLight << "," << vehicleSpeed << "," << gear << endl;

            usleep(10000);

            break;
        }
        default:
        {
            break;
        }
        }
        // [OPTION]
        //usleep(100);
        // sleep(1);

    } // end: while(1)
    dataFile.close();
}

void sendCAN(sensors::Can can, zmq::socket_t *pubSock, mutex &m)
{
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
    m.lock();
    s_send_idx(*pubSock, SENSOR_CAN);
    s_send(*pubSock, zmqData);
    m.unlock();
    printf("[MobilePlatform/Sensing/GpsSensingThread] Complete to send to PUB Socket\n");
}

void fromBitToDec(char *data, int bit_start, int bit_length, int *dst)
{
    int byte_start = bit_start / 8;
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
    for (int i = 0; i < 1; i++)
    {
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
    for (int i = 0; i < 8; i++)
    {
        bin[i] = dec % 2;
        dec = dec / 2;
        // printf("[%d] bin=%d dec=%d\n", i, bin[i], dec);
    }

    // <binary parsing>
    // printf("[TARGET]\n");
    for (int i = offset; i < offset + bit_length; i++)
    {
        // printf("bin[%d] = %d = dst[%d]\n", i, bin[i], i-offset);
        // bin[7-i]
        dst[i - offset] = bin[i];
    }
}

int fromBytesToDec(char *data, int bit_start, int bit_length)
{
    // <bit to byte>
    int byte_start = bit_start / 8;
    int byte_length = bit_length / 8;
    // printf("[BYTE] from %d (length:%d)\n", byte_start, byte_length);

    // <read to hex>
    // printf("[HEX] \n");
    char hex[8] = {0};
    for (int i = byte_start; i < byte_start + byte_length; i++)
    {
        hex[i - byte_start] = data[i];
        // printf("hex[%d] %02X \n", i-byte_start, hex[i-byte_start]);
    }
    hex[byte_length] = '\0';

    // <little endian>
    // printf("[LITTLE ENDIAN] \n");
    char tmp;
    for (int i = 0; i < byte_length / 2; i++)
    {
        tmp = hex[i];
        hex[i] = hex[byte_length - i - 1];
        hex[byte_length - i - 1] = tmp;
    }
    for (int i = 0; i < byte_length; i++)
    {
        // printf("hex[%d] = %02X\n", i, hex[i]);
    }

    // hex to dec
    // printf("[DEC]\n");
    int dec = 0;
    for (int i = 0; i < byte_length; i++)
    {
        // dec = (dec << 8) | hex[i];
        // printf("[%d] %d + %d", i, dec*0x100, hex[i]);
        dec = (dec * 0x100) + hex[i];
        // printf(" = %d\n", dec);
    }
    // printf("dec=%d\n",dec);
    return dec;
}