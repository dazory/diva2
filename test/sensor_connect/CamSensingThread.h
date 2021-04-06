// //CanSensingThread.h
// #pragma once
// #include <string>
// #include <iostream>
// #include "CanSensing.cpp"

// #include "../service/zmq_helper.h"

// using namespace std;


// class CanSensingThread{
// 	public:
// 	CanSensingThread();
// 	static void run(const char *devicename="can0", void *context=zmq_ctx_new());
// };

// CanSensingThread::CanSensingThread(){

// }

// void CanSensingThread::run(const char *devicename, void *context){
//     printf("start (in CanSensingThread::run)\n");

//     CanSensing canThread;
//     int socket = canThread.getSocket(devicename); // defualt device name = "can0"
//     printf("canThread.getSocket Complete (in CanSensingThread::run)\n");
	
//     while(1){
//         struct can_frame frame;
//         int nbytes = read(socket, &frame, sizeof(struct can_frame));

//         if(nbytes <0){
// 		    printf("(ERROR) Fail to read the socket(%d) (in CanSensingThread::run/while(1))\n",socket);
//             exit(-100);
//         }
//         printf("Read a can_frame: 0x%03X [%d] (in CanSensingThread::run/while(1))", frame.can_id, frame.can_dlc);

//         for(int i=0; i<frame.can_dlc; i++){ 
//             printf("%02X ", frame.data[i]);
//         }
//         printf("\r\n");
//         printf("Complete to read ID, DLC(데이터 길이 코드), payload from CAN (in CanSensingThread::run/while(1))");

//         struct can_filter rfilter [1];
//         rfilter[0].can_id=0x550;
//         rfilter[0].can_mask=0xFF0;
//         // rfilter[1].can_id = 0x200;
//         // rfilter[1].can_mask = 0x700;

//         setsockopt(socket, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
//         printf("filtering out CAN frames that are not relevant (in CanSensingThread::run/while(1))");

//         s_sendmore (context, "CAN");
//         printf("sendmore: \"CAN\" (in CanSensingThread::run/while(1))\n");
        
//         zmq::message_t msg(&frame, sizeof(can_frame), NULL);
//         s_send(context,msg);
// 		printf("send complete! (in CanSensingThread::run/while(1))\n");

//         sleep (1);
//     }
// }
