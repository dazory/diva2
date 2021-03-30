#pragma once
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

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

// inline static bool s_send_str (zmq::socket_t & publisher, const std::string &string, int flags = 0) {
//     zmq::message_t message(string.size());
//     memcpy(message.data(), string.data(), string.size());
//     bool rc = publisher.send(message, flags);

//     return (rc);
// }
// inline static bool s_send_str (zmq::socket_t & publisher, zmq::message_t &data, int flags = 0) {

//     bool rc = publisher.send(data, flags);

//     return (rc);
// }

// inline static bool
// s_sendmore (zmq::socket_t & socket, const std::string & string) {

//     zmq::message_t message(string.size());
//     memcpy (message.data(), string.data(), string.size());

//     bool rc = socket.send (message, ZMQ_SNDMORE);
//     return (rc);
// }

// inline static bool
// s_send (zmq::socket_t & socket, const std::string & string, int flags = 0) {

//     zmq::message_t message(string.size());
//     memcpy (message.data(), string.data(), string.size());

//     bool rc = socket.send (message, flags);
// }
