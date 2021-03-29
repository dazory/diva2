#include "GpsParsingThread.h"
#include "ImuParsingThread.h"

using namespace std;

int main(int argc, char * argv[]){
    void *context=zmq_ctx_new();

    GpsParsingThread gps_parsing_thread;
    //쓰레드로 클래스의 멤버함수 부르기 위해 이렇게 작성함
    thread gps_parsing(&GpsParsingThread::run, &gps_parsing_thread, &context);
    ImuParsingThread imu_parsing_thread;
    thread imu_parsing(&ImuParsingThread::run, &imu_parsing_thread, &context);

    gps_parsing.join();
    imu_parsing.join();

    return 0;
}