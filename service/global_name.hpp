#ifndef __GLOBAL_NAME_H__
#define __GLOBAL_NAME_H__
#include "string"
#include <termios.h>

using namespace std;

// extern map<string, tuple<string, int>> SensorInfoMap;

namespace protocol
{
    const string SENSING_PUB = "tcp://127.0.0.1:5563";
    const string SENSING_SUB = "tcp://127.0.0.1:5563";
    const string SENDER_TOCLOUD_REQ_TEST = "tcp://localhost:5564"; //tcp://13.125.216.169:5555
    const string SENDER_TOCLOUD_REQ = "tcp://165.246.39.124:5564";//"54.180.155.160:22"; // ubuntu@
    const string RECEIVER_FROMMOBILE_REP_TEST = "tcp://*:5564";
} // namespace protocol

// static map<string, int> SpeedMap;

// static void sensorInfoMap_init();
// void speedMap_init();
// static map<string, IMU> ImuMap;

// void sensorInfoMap_init(){
//     // speedMap_init();
//     SensorInfoMap["GPS"] = make_tuple("/dev/ttyACM0", B1200);//SpeedMap["9600"]);
//     // SensorInfoMap["IMU"] = make_tuple("/dev/ttyACM0",115200);
// }

// void speedMap_init(){
//     SpeedMap["1200"] = B1200;
// 	SpeedMap["2400"] = B2400;
// 	SpeedMap["4800"] = B4800;
// 	SpeedMap["9600"] = B9600;
// 	SpeedMap["19200"] = B19200;
// 	SpeedMap["38400"] = B38400;
// 	SpeedMap["57600"] = B57600;
// 	SpeedMap["115200"] = B115200;
// 	SpeedMap[NULL] = 0;
// }


#endif __GLOBAL_NAME_H__