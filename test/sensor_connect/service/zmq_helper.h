#pragma once
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

inline static bool s_sendmore (zmq::socket_t & publisher, const void *data) {
    
    bool rc = publisher.send(data, ZMQ_SNDMORE);

    return (rc);
}

inline static bool s_send (zmq::socket_t & publisher, zmq::message_t &data, int flags = 0) {
    bool rc = publisher.send(data, flags);

    return (rc);
}