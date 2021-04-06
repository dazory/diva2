#include "CamParsingThread.h"
#include "../service/zmq_helper.h"
#include "../service/cam_packet.h"

using namespace std;

CamParsingThread::CamParsingThread() {}


void CamParsingThread::run(void* context, zmq::socket_t *pub) {
    printf("start (in CamParsingThread::run)\n");
    
    zmq::socket_t subscriber(*(zmq::context_t*)context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3);//raw data를 sub으로 받음.
    //subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);//raw data를 sub으로 받음.
    printf("complete to connect with socket (in CamParsingThread::run)\n");
    
    while (!stop_flag) {
        printf("start in while(1) (in CamParsingThread::run)\n");
        
        // read topic
        // zmq::message_t msgtopic = s_recv(subscriber);         //topic받아옴 -> CAM 만 받음
        // string topic = (const char *)msgtopic.data();
        // printf("topic= %s\n",topic);
	
        zmq::message_t msgData = s_recv(subscriber);
        CamPacket mCamPacket;
        memcpy(&mCamPacket, msgData.data(), msgData.size());
        printf("===== CAM ====\n");
        mCamPacket.display();

        /*
        if(topic=="CAM"){
            int cnt = 0;
            int rows, cols, type;
            cv::Mat img;
            void *data;
        
            zmq::message_t rcv_msg;

            subscriber.recv(&rcv_msg,0); // rows
            rows = *(int*)rcv_msg.data();
            subscriber.recv(&rcv_msg, 0); // cols
            cols = *(int*)rcv_msg.data();
            subscriber.recv(&rcv_msg, 0); // type
            type = *(int*)rcv_msg.data();
            subscriber.recv(&rcv_msg, 0); // data
            data = (void*)rcv_msg.data();
            printf("rows=%d, cols=%d type=%d\n", rows, cols, type);
            //std::cout << "rows=" << rows << ", cols=" << cols << ", type=" << type << std::endl;

            if (type == 2) {
                img = cv::Mat(rows, cols, CV_8UC1, data);
            }
            else {
                img = cv::Mat(rows, cols, CV_8UC3, data);
            }

            cv::imshow("receive_image", img);
            cv::waitKey(0);
        }
        */        
    }
}

void CamParsingThread::stop() {
stop_flag = true;
}