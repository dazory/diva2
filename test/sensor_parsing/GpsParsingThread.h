
#pragma once
#include <zmq.hpp>
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

class GpsParsingThread{
    public:
        GpsParsingThread();
        void run(void*, zmq::socket_t *);
        void stop();
    private:
        string latitude;
        string longtitude;
        bool stop_flag=false;
};

inline static bool 
ss_sendmore(zmq::socket_t & socket, const std::string & string) {
    zmq::message_t message(string.size());
    memcpy(message.data(), string.data(), string.size());
    bool rc = socket.send(message, ZMQ_SNDMORE);
    return (rc);
}

inline static bool
ss_send(zmq::socket_t & socket, const std::string & string, int flags = 0) {
        zmq::message_t message(string.size());
        memcpy(message.data(), string.data(), string.size());
        bool rc = socket.send(message, flags);
        return (rc);
    }