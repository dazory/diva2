#include "camthread.h"
#include <zmq.hpp>
#include <time.h>
#include <sys/time.h>
#include <iomanip>

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}
camThread::camThread(QObject *parent) : QThread(parent)
{
}

void camThread::run(){
    zmq::context_t ctx(1);
     zmq::socket_t cam_sub( ctx, ZMQ_SUB);
    cam_sub.connect("tcp://10.8.0.8:5563");
    cam_sub.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3);

    file.open("cam_delay.csv");

    while(!stop_flag){
        sensors::Cam cam;
        string topic=s_recv(cam_sub);
        
        zmq::message_t msg;
        cam_sub.recv(&msg);
        cv::Mat frame;

        //protobuf parsing
        cam.ParseFromArray(msg.data(), msg.size());

        //전송 delay 측정
        struct timeval tv;
        gettimeofday(&tv, NULL);
        double cur=1000000*tv.tv_sec + tv.tv_usec;
        file<<cur-cam.timestamp()<<",us\n";

        //Decoding to Mat
        vector<uchar> data(cam.image_data().begin(), cam.image_data().end());
        frame=cv::imdecode(data, cv::IMREAD_COLOR);

        //BGR -> RGB
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

        //QImage 만들어서 signal 전송
        QImage image(frame.size().width, frame.size().height, QImage::Format_RGB888);
        memcpy(image.scanLine(0), frame.data, static_cast<size_t>(image.width() * image.height() * frame.channels()));
        emit send_qimage(image);
         
    }
}
void camThread::stop(){
    stop_flag = true;
    file.close();
}