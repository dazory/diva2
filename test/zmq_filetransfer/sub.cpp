// test/zmq_filetransfer/sub.cpp
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

using namespace std;

class data {
public:
int a, b, c, d;
};

int main () {
    printf("start main\n");

    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
    printf("connect!\n");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    printf("set socket option!\n");

    while (1) {
        zmq::message_t reply;
        subscriber.recv(&reply);
        printf("recv!\n");

        printf("Received reply: %d bytes \n", static_cast<int>(reply.size()));

        data dd = *(data*)reply.data();

	    //out으로 바꾸면 csv에 저장됨
        printf("a=%d, b=%d, c=%d, d=%d\n", dd.a, dd.b, dd.c, dd.d);
        
        printf("sleeping...\n");
        sleep(1);
        printf("sleep complete!\n");

    }
}