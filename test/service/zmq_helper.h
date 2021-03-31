#pragma once
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

enum SENSOR{SENSOR_GPS, SENSOR_IMU, SENSOR_CAN, SENSOR_CAM, SENSOR_LIDAR};

inline static bool s_sendmore (zmq::socket_t & publisher, zmq::message_t &data) {
    int rc = publisher.send(data, ZMQ_SNDMORE);
    printf("rc=%d\n",rc);
    return (rc);
}

inline static bool s_send (zmq::socket_t & publisher, zmq::message_t &data, int flags = 0) {
    int rc = publisher.send(data, flags);
    printf("rc=%d\n",rc);
    return (rc);
}


/* 참고: https://github.com/sansajn/remoteplayer/blob/f4c2abe030758951c2018f44c74039940cfbc2bd/rplay/libs/zmqu/send.hpp */
template <typename T>
inline size_t send_one(zmq::socket_t & sock, T const & t, int flags)  //!< generic POD send support
{
	return sock.send(static_cast<void const *>(&t), sizeof(T), flags);
}


inline static bool s_send_idx (zmq::socket_t & socket, int nSensor) {
    string strIdx = "";
    switch (nSensor)
    {
    case SENSOR_GPS:
        strIdx = "GPS"; break;
    case SENSOR_IMU:
        strIdx = "IMU"; break;
    case SENSOR_CAN:
        strIdx = "CAN"; break;
    case SENSOR_CAM:
        strIdx = "CAM"; break;
    case SENSOR_LIDAR:
        strIdx = "LIDAR"; break;
    default:
        strIdx = ""; break;
    }
    
    size_t size = strIdx.size() + 1;
    zmq::message_t zmqIdx(size);
    memcpy(zmqIdx.data(), strIdx.c_str(), size);
    s_sendmore(socket, zmqIdx);

	 cout<<"zmqIdx = "<<(const char *)zmqIdx.data()<<"  (in s_send_idx())"<<endl;
}

inline static bool s_send_test (zmq::socket_t & socket, int nSensor) {
    string strData = "";
    switch (nSensor)
    {
    case SENSOR_GPS:
        strData = "$GNGGA,015442.00,3458.17997,N,12728.74791,E,1,04,6.67,39.9,M,21.1,M,,*61"; break;
    case SENSOR_IMU:
        strData = ""; break;
    case SENSOR_CAN:
        strData = ""; break;
    case SENSOR_CAM:
        strData = ""; break;
    case SENSOR_LIDAR:
        strData = ""; break;
    default:
        strData = ""; break;
    }
    
    size_t size = strData.size() + 1;
    zmq::message_t zmqData(size);
    memcpy(zmqData.data(), strData.c_str(), size);
    s_send(socket, zmqData);

	 cout<<"zmqData = "<<(const char *)zmqData.data()<<"  (in s_send_test())"<<endl;
}

/* image_zmq/zmq_service.hpp */

// bool s_send_data(void* data, size_t size) {
//     if (size == 0)
//       return false;

//     zmq::message_t data_msg(size + HEADER_OFFSET);
//     long input_time = get_time_since_epoch_count();
//     memcpy(data_msg.data(), (void*)(&input_time), sizeof(long));
//     memcpy(data_msg.data() + sizeof(long), (void*)(&port_), sizeof(int));
//     memcpy(data_msg.data() + HEADER_OFFSET, data, size);
//     sock_srv->send(data_msg);
//     return true;
//   }

//   bool send(Data* data) {
//     if (data->data_size == 0)
//       return false;

//     // zmq::message_t data_msg(data->data_size);

//     // data->to_bytes((char*)(data_msg.data()));

//     // data to message
//     timer.tick();
//     zmq::message_t data_msg(data->data_size + HEADER_OFFSET);

//     // add input time in the header field
//     data->to_bytes((char*)(data_msg.data()) + HEADER_OFFSET);
//     std::cout << "Server memcpy time (us): " << timer.tock_count() << std::endl;
//     // memcpy_time.emplace_back(timer.tock_count());

//     // // send data
//     long input_time = get_time_since_epoch_count();
//     memcpy(data_msg.data(), (void*)(&input_time), sizeof(long));
//     memcpy(data_msg.data() + sizeof(long), (void*)(&port_), sizeof(int));
//     sock_srv->send(data_msg);
//     return true;
//   }

