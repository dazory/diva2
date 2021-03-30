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

    /*
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5563");
    */

    void *context = (void *)zmq_ctx_new();
    assert(context);
    printf("connect!\n");

        void *socket = zmq_socket(context, ZMQ_PUB);
        assert(socket);
        printf("context casting and socket generate!\n");
        // int rc = zmq_bind(socket,"tcp://*:5563");
        int rc = zmq_bind(socket, "tcp://*:5563");
        printf("zmq_connect rc=%d!\n",rc);
        assert(rc==0);
        //socket.bind("tcp://*:5563");
        printf("socket binding!\n");

        
    data c_msg;
    c_msg.a=1; c_msg.b=2;c_msg.c=3;c_msg.d=4;
       
    while (1) {
    
        //zmq::message_t msg(&c_msg, sizeof(data), NULL);
        zmq_msg_t msg; //(%c_msg,sizeof(data),NULL);
        int rc = zmq_msg_init_size(&msg, sizeof(c_msg));
        printf("size: %d\n",sizeof(c_msg));
        memcpy(zmq_msg_data (&msg), &c_msg, sizeof(c_msg));
        printf("message make!\n");
 
        /*
        publisher.send(msg);
        */
        //zmq::socket_t socket(*(zmq::context_t*)context, ZMQ_PUB);

        //socket.send(msg,0);
        //zmq_send(socket, "WOR",3,0);
        // socket_t::send(msg,0);
        zmq_msg_send(&msg, socket, ZMQ_SNDMORE);

        printf("send!\n");

        printf("sleeping...\n");
        sleep (1);
        printf("sleep complete!\n");

    }
    return 0;
}