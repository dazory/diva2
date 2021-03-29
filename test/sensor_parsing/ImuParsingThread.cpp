#include "ImuParsingThread.h"

using namespace std;

class IMUdata {
public:
    float gyrox, gyroy, gyroz, magx, magy, magz, accelx, accely, accelz;
};

ImuParsingThread::ImuParsingThread(){}

void ImuParsingThread::run(void *context) {
    zmq::socket_t imu_sub(*(zmq::context_t*)context, ZMQ_SUB);
    imu_sub.connect("tcp://localhost:5563");
    imu_sub.setsockopt(ZMQ_SUBSCRIBE, "IMU", 3);
    while (!stop_flag) {
        mscl::MipDataPackets packets;
        zmq::message_t imu_data;
        imu_sub.recv(& imu_data);
        packets = * (mscl::MipDataPackets *)imu_data.data(); //MipDataPackets를 받아 저장
        IMUdata temp;

        //xyz가속도 정보 추출
        for (mscl::MipDataPacket packet : packets) {

            int count = 0;
            packet.descriptorSet();
            mscl::MipDataPoints points = packet.data();

            for (mscl::MipDataPoint dataPoint : points) {
                const char * cName = dataPoint.channelName().c_str();

                if (strcmp("scaledAccelX", cName) == 0) {
                    count = 3;
                    temp.accelx = dataPoint.as_float();
                    accel_x=temp.accelx;
                }

                if (count == 2) {
                    temp.accely = dataPoint.as_float();
                    accel_y=temp.accely;
                }
                if (count == 1) {
                    temp.accelz = dataPoint.as_float();
                    accel_z=temp.accelz;
                }
                count--;
                if (count == 0) {
                    cout<<"IMU Data Received\n";
                    cout << "accelx: " << temp.accelx << "//accely: " << temp.accely << "//accelz: " << temp.accelz << endl;
                    //여기서 받은 값을 qt로 넘겨줘야함
                    break;
                }
            }
            if (count == 0) {
                break;
            }
        }
    }
}

void ImuParsingThread::stop(){
    stop_flag=true;
}

