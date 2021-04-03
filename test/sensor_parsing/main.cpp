#include "GpsParsingThread.h"
#include "ImuParsingThread.h"
#include "CamParsingThread.h"

using namespace std;

int main(int argc, char * argv[]){
    zmq::context_t context(1);

    //GpsParsingThread gps_parsing_thread;
    //쓰레드로 클래스의 멤버함수 부르기 위해 이렇게 작성함
    //thread gps_parsing(&GpsParsingThread::run, &gps_parsing_thread, &context);

    //CamParsingThread cam_parsing_thread;
    //thread cam_parsing(&CamParsingThread::run, &cam_parsing_thread, &context);

    ImuParsingThread imu_parsing_thread;
    thread imu_parsing(&ImuParsingThread::run, &imu_parsing_thread, &context);

    //gps_parsing.join();
    imu_parsing.join();

    return 0;
}