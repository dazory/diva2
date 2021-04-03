#include "CamParsingThread.h"
#include "../service/zmq_helper.h"

using namespace std;

CamParsingThread::CamParsingThread() {}


void CamParsingThread::run(void * context, zmq::socket_t * pub) {
    printf("start (in CamParsingThread::run)\n");

    zmq::socket_t subscriber( * (zmq::context_t *)context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3); //raw data를 sub으로 받음.
    //subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);//raw data를 sub으로 받음.
    printf("complete to connect with socket (in CamParsingThread::run)\n");

    while (!stop_flag) {
        printf("start in while(1) (in CamParsingThread::run)\n");

        // read topic
        zmq::message_t msgtopic = s_recv(subscriber); //topic받아옴 -> CAM 만 받음
        string topic = (const char *)msgtopic.data();
        printf("topic= %s\n", topic);

        //데이터 받아서 디코딩
        cv::Mat img_decode;
        zmq::message_t rcv;
        subscriber.recv(& rcv);
        vector<uchar> data;
        data.resize(rcv.size());
        memcpy(data.data(), rcv.data(), rcv.size());
        img_decode = cv::imdecode(data, cv::IMREAD_COLOR);

        //BGR -> RGB 해서 Qt에 전송
        cv::cvtColor(img_decode, img_decode, cv::COLOR_BGR2RGB);
        vector<uchar> buffer;
        cv::imencode(".jpg", img_decode, buffer);
        s_send_idx(*pub,SENSOR_CAM);
        zmq::message_t msg(buffer.size());
        memcpy(msg.data(), buffer.data(), buffer.size());
        pub->send(msg);

        cv::imshow("receive_image", img_decode);
        cv::waitKey(0);

    }
}

void CamParsingThread::stop() {
stop_flag = true;
}