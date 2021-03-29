#include "GpsParsingThread.h"

using namespace std;

GpsParsingThread::GpsParsingThread(){}

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

void GpsParsingThread::run(void* context){
    zmq::socket_t gps_sub(*(zmq::context_t*)context, ZMQ_SUB);
    gps_sub.connect("tcp://localhost::5563");
    gps_sub.setsockopt(ZMQ_SUBSCRIBE, "GPS", 3);

   // zmq::socket_t gps_pub(context, ZMQ_PUB);
    //gps_pub.bind("tcp://localhost::5564");

    while (!stop_flag) {
        std::string topic = s_recv(gps_sub);         //topic받아옴
        std::string gps_data = s_recv(gps_sub);      //topic 이후의 데이터를 저장

        //gps_data에서 $GPGGA로 시작하는 데이터를 , 를 기준으로 파싱
        string str_arr[1000];
        int str_cnt = 0;
        char str_buff[100];
        strcpy(str_buff, gps_data.c_str());
        char * tok = strtok(str_buff, ",");

        if (tok != NULL && strcmp(tok, "$GPGGA") == 0) {
            while (tok != nullptr) {
                str_arr[str_cnt++] = string(tok);
                tok = strtok(nullptr, ",");
            }
	        //위도 경도 정보 추출
            cout<<"GPS Data Received"<<endl;
            cout << str_arr[2] << "," << str_arr[3] <<endl;

            if(str_arr[2].length()<1 || str_arr[4].length()<1){
                latitude="0";
                longtitude="0";
            }
            else{
                latitude=str_arr[2];
                longtitude=str_arr[4];
            }

            //Qt로 전송
           // s_sendmore(gps_pub, "GPS");
            //s_sendmore(gps_pub, latitude);
            //s_send(gps_pub, longtitude);
        }
        
    }
}

void GpsParsingThread::stop(){
    stop_flag=true;
}
