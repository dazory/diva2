// test/zmq_filetransfer/pub.cpp
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include <time.h>
#include <assert.h>
#include <stdlib.h>       
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

class data {
public:
int a, b, c, d;
};

int main () {
    printf("start main\n");

    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5563");
    printf("connect!\n");

    data c_msg;
    c_msg.a=1; c_msg.b=2;c_msg.c=3;c_msg.d=4;
       
    while (1) {
    
        zmq::message_t msg(&c_msg, sizeof(data), NULL);
        publisher.send(msg);
        printf("send!\n");

        printf("sleeping...\n");
        sleep (1);
        printf("sleep complete!\n");

    }
    return 0;
}