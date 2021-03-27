//  zmq test code
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <assert.h>
using namespace std;

int main(){
    cout<< "hello diva2:zmq test\n";

    pid_t pid;

   printf( "자식 프로세스 생성");
   pid   = fork();

   switch( pid)
   {
        case -1  :
        {
            printf( "자식 프로세스 생성 실패\n");
            return -1;
        }
        case 0   :
        {
            printf("자식 프로세스 입니다.\n");
            printf ("Connecting to hello world server…\n");
            void *context = zmq_ctx_new ();
            void *requester = zmq_socket (context, ZMQ_REQ);
            zmq_connect (requester, "tcp://localhost:5555");

            int request_nbr;
            for (request_nbr = 0; request_nbr != 10; request_nbr++) {
                char buffer [10];
                printf ("Sending Hello %d…\n", request_nbr);
                zmq_send (requester, "Hello", 5, 0);
                zmq_recv (requester, buffer, 10, 0);
                printf ("Received World %d\n", request_nbr);
            }
            zmq_close (requester);
            zmq_ctx_destroy (context);
            }
        default  :
        {
            printf("부모 프로세스 입니다.\n");
            printf( "자식 프로세스의 pid는 %d입니다.\n", pid);
            //  Socket to talk to clients
            void *context = zmq_ctx_new ();
            void *responder = zmq_socket (context, ZMQ_REP);
            int rc = zmq_bind (responder, "tcp://*:5555");
            assert (rc == 0);

            while (1) {
                char buffer [10];
                zmq_recv (responder, buffer, 10, 0);
                printf ("Received Hello\n");
                sleep (1);          //  Do some 'work'
                zmq_send (responder, "World", 5, 0);
            }
        }
    }

    return 0;

}

