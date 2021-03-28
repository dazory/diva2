#include <zmq.hpp> // https://github.com/zeromq/cppzmq
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <string.h> 
#include <time.h> 
#include <assert.h> 
#include <stdlib.h>
#include <stdio.h> 
#include <stdarg.h> 
#include <signal.h> 
#include <sys/time.h> 
#include <unistd.h> 
#include <fstream>
#include <thread>

using namespace std;

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

void gpsthread(){
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "GPS", 3);

    std::string path = "/home/diva2/Documents/GPS/gps_data.csv";
    ofstream out(path);
    while (1) {
        std::string topic = s_recv(subscriber);         //topic받아옴
        std::string gps_data = s_recv(subscriber);      //topic 이후의 데이터를 저장

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
	    //out으로 바꾸면 csv에 저장됨
            cout << str_arr[1] << "," << str_arr[2] << "," << str_arr[3] << endl;
        }
        
        sleep (1);
    }
}

int main() {
    thread gps(gpsthread);
    gps.join();

    return 0;
}