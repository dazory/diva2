#include "lidarthread.h"
#include <sys/time.h>

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

lidarThread::lidarThread(QObject* parent) : QThread(parent)
{
    ptr_cloud.reset( new pcl::PointCloud<pcl::PointXYZ>);
}

void lidarThread::run(){
    zmq::context_t ctx(1);
    zmq::socket_t lidar_sub(ctx, ZMQ_SUB);
    lidar_sub.connect("tcp://10.8.0.8:5563");
    lidar_sub.setsockopt(ZMQ_SUBSCRIBE, "LIDAR", 5);

    file.open("lidar_delay.csv");

    while(!stop_flag){
        sensors::Lidar lidar;
        string topic=s_recv(lidar_sub);
        zmq::message_t msg;
        lidar_sub.recv(&msg);

        //protobuf parsing
        lidar.ParseFromArray(msg.data(), msg.size());

        //size크기의 PointCloud 생성
        int size=(int)lidar.size();
        cloud.resize(size);

        //생성한 PointCloud에 point들 좌표 삽입
        int i=0;
        for (auto & point : cloud) {
            point.x = lidar.data(i).x();
            point.y = lidar.data(i).y();
            point.z = lidar.data(i).z();
            i++;
        }

        //전송 delay 측정
        struct timeval tv;
        gettimeofday(&tv, NULL);
        double cur=1000000*tv.tv_sec + tv.tv_usec;
        file<<cur-lidar.timestamp()<<",us\n";

        //signal
        *ptr_cloud=cloud;
        emit send_lidar(ptr_cloud);
    }
    QCoreApplication::processEvents();
}
void lidarThread::stop(){
    stop_flag = true;
    file.close();
}
