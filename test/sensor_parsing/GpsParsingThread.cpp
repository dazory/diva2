#include "GpsParsingThread.h"
#include "../service/zmq_helper.h"

using namespace std;

GpsParsingThread::GpsParsingThread(){}

// inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
//     zmq::message_t message;
//     socket.recv(& message, flags);
// 	std::cout << "receive: \"" << (const char*)message.data() << "\"... done." << std::endl;

//     return std::string(static_cast < char *> (message.data()), message.size());
// }

// inline static zmq::message_t s_recv(zmq::socket_t & socket, int flags = 0) {
//     zmq::message_t message;
//     socket.recv(& message, flags);
// 	//std::cout << "receive: \"" << (const char*)message.data() << "\"... done." << std::endl;

//     return message;
// }

void GpsParsingThread::run(void* context, zmq::socket_t* pub){
    zmq::socket_t gps_sub(*(zmq::context_t*)context, ZMQ_SUB);
    gps_sub.connect("tcp://localhost:5563");
    gps_sub.setsockopt(ZMQ_SUBSCRIBE, "GPS", 3);

    while (!stop_flag) {
        zmq::message_t msgtopic = s_recv(gps_sub);
        string topic = (const char *)msgtopic.data();
        zmq::message_t msggps_data = s_recv(gps_sub);
        string gps_data = (const char *)msggps_data.data();
        //std::string topic = s_recv(gps_sub);         //topic받아옴
        //std::string gps_data = s_recv(gps_sub);      //topic 이후의 데이터를 저장

        //printf("s_recv: topic = %s  (in GpsParsingThread::run/while(1))\n",topic.c_str());
        //printf("s_recv: gps_data = %s  (in GpsParsingThread::run/while(1)\n",gps_data.c_str());


        //gps_data에서 $GNGGA로 시작하는 데이터를 , 를 기준으로 파싱
        string str_arr[1000];
        int str_cnt = 0;
        char str_buff[100];
        strcpy(str_buff, gps_data.c_str());
        char * tok = strtok(str_buff, ",");

        if (tok != NULL && strcmp(tok, "$GNGGA") == 0) {
            while (tok != nullptr) {
                str_arr[str_cnt++] = string(tok);
                tok = strtok(nullptr, ",");
            }
	        //위도 경도 정보 추출
            cout<<"*** GPS Data Received ***"<<endl;
            cout <<"  "<< str_arr[2] << "," << str_arr[3] <<endl;

            if(str_arr[2].length()<1 || str_arr[4].length()<1){
                latitude="0";
                longtitude="0";
            }
            else{
                latitude=str_arr[2];
                longtitude=str_arr[4];
            }

            //Qt로 전송
            s_send_idx(*pub, SENSOR_GPS);
            ss_sendmore(*pub, latitude);
            ss_send(*pub, longtitude);
        }
        
    }
}

void GpsParsingThread::stop(){
    stop_flag=true;
}