#include "CanSensingThread.h"


void getFakeCanData(struct can_frame &frame, int num);
void hex2char(string hex_chars, struct can_frame &frame);
void writingCanData(int wSock);
int getSocket(string devname);
int closeSocket(int socket);
void displayCanFrame(struct can_frame &frame);


CanSensingThread::CanSensingThread()
{
}

void CanSensingThread::run(zmq::socket_t *publisher) // const int devicename, zmq::context_t *context,
{
    string devname = "vcan0";
    
    /* Connect to Socket for reading */
    std::printf("start! (in CanSensing::initialize)\n");
    int rSock = getSocket(devname);

    /* writing fake data to wSock if USE_CAN is 2 */
    pid_t pid=0;
    if(USE_CAN==2)
    {
        pid = fork();
        if(pid!=0) // parent is writing fake can data to socket wSock
        {
            // printf("This is parent process(%d)\n", pid);
            
            /* connect the socket for writing */
            int wSock = getSocket(devname);

            /* writing fake can data to wSocket */
            while(1){ writingCanData(wSock); }

            closeSocket(wSock);
        }
    }

    /* Reading can data from rSock */
    while (pid==0)
    {
        // printf("This is child process(%d)\n", pid);
        if (USE_CAN == 1) // real
        {

        }else if(USE_CAN == 2) // test
        {
            /* Read from rSock */
            struct can_frame r_frame;
            int nBytes = read(rSock, &r_frame, sizeof(struct can_frame));
            //std::printf("read %d bytes (in CanSensingThread::run())\n", nBytes);
            if(nBytes<0){
                perror("Read from rSock");
                exit(-1);
            }

            /* Display what I read */
            // displayCanFrame(r_frame);

            /* Parsing to Proto */
            sensors::Can can;
            can.set_can_id(r_frame.can_id);
            can.set_can_dlc(r_frame.can_dlc);
            size_t size = r_frame.can_dlc;
            can.mutable_data()->resize(size);
            memcpy((void*)can.mutable_data()->data(), (void*)r_frame.data, size);
        
            int data_len = can.ByteSize();
            unsigned char data[data_len] ="\0";
            can.SerializeToArray(data, data_len);
            // for (auto i = 0; i < data_len; i++)
            //     printf("%02X ", data[i]);
            // printf("\n");

            zmq::message_t zmqData(data_len);
            memcpy((void *)zmqData.data(), data, data_len);
            s_send(*publisher, zmqData);
            printf("send complete! [size=%d] (in CanSensingThread::run/while(1))\n", data_len);
        
        }
    }// finish: while(pid==0)

    closeSocket(rSock);
    
}

void getFakeCanData(struct can_frame &frame, int num){
    num = num % 10;
    switch (num)
    {
    case 0:
    { 
        frame.can_id=0x05f0; frame.can_dlc=2;
        string hex_chars("00 00 0e 00 00 00 00 00");
        hex2char(hex_chars, frame);
        break;
    }
    case 1:
    {
        frame.can_id=0x04f0; frame.can_dlc=8;
        string hex_chars("00 00 00 00 00 00 00 00");
        hex2char(hex_chars, frame);
        break;
    }
    case 2:
    {
        frame.can_id=0x0690; frame.can_dlc=8;
        string hex_chars("00 00 00 00 00 00 00 00");
        hex2char(hex_chars, frame);
        break;
    }
    case 3:
    {
        frame.can_id=0x04f0; frame.can_dlc=8;
        string hex_chars("00 00 00 00 00 00 00 00");
        hex2char(hex_chars, frame);
        break;
    }
    case 4:
    {
        frame.can_id=0x05f0; frame.can_dlc=2;
        string hex_chars("00 00 00 00 00 00 00 00");
        hex2char(hex_chars, frame);
        break;
    }
    case 5:
    {
        frame.can_id=0x0690; frame.can_dlc=8;
        string hex_chars("00 00 00 00 00 00 00 00");
        hex2char(hex_chars, frame);
        break;
    }
    case 6:
    {
        frame.can_id=0x04f0; frame.can_dlc=8;
        string hex_chars("00 00 00 80 00 eb b6 13");
        hex2char(hex_chars, frame);
        break;
    }
    case 7:
    {
        frame.can_id=0x0130; frame.can_dlc=8;
        string hex_chars("00 00 40 ff 00 00 41 3d");
        hex2char(hex_chars, frame);
        break;
    }
    case 8:
    {
        frame.can_id=0x0131; frame.can_dlc=8;
        string hex_chars("00 00 40 00 00 00 41 9b");
        hex2char(hex_chars, frame);
        break;
    }
    case 9:
    {
        frame.can_id=0x0140; frame.can_dlc=8;
        string hex_chars("00 00 00 00 02 29 21 f0");
        hex2char(hex_chars, frame);
        break;
    }
    default:
    {
        frame.can_id=0x0153; frame.can_dlc=0;
        break;
    }
    }
}


void hex2char(string hex_chars, struct can_frame &frame){
    // std::string hex_chars("E8 48 D8 FF FF 8B 0D");
    std::istringstream hex_chars_stream(hex_chars);
    std::vector<unsigned char> bytes;

    unsigned int c;
    for(int i=0; i<CAN_MAX_DLEN; i++){
        hex_chars_stream >> std::hex >> c;
        frame.data[i] = c;
    }
}

void writingCanData(int wSock){
    /* writing fake can data to wSocket */
    struct can_frame wFrame;
    getFakeCanData(wFrame, rand());
    if(write(wSock, &wFrame, sizeof(struct can_frame))!=sizeof(struct can_frame)){
        perror("Write fake can data to wSock");
        exit(-1);
    }
}

int getSocket(string devname){
    int rSock;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;
    printf("CAN Sockets Demo\r\n");

    if((rSock=socket(PF_CAN,SOCK_RAW, CAN_RAW))<0){
        perror("Socket");
        exit(-1);
    }
    strcpy(ifr.ifr_name, devname.c_str());
    ioctl(rSock, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if(bind(rSock, (struct sockaddr *)&addr, sizeof(addr))<0){
        perror("Bind");
        exit(-1);
    }

    return rSock;
}

int closeSocket(int socket){
    int num = close(socket); 
    if(num<0){
        perror("Close");
        exit(-1);
    }
    return num;
}

void displayCanFrame(struct can_frame &frame){
    std::printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
    for(int i=0; i<frame.can_dlc; i++)
        std::printf("%02X ", frame.data[i]);
    std::printf("\r\n");
}