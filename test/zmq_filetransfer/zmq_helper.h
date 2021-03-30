#pragma once
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

inline static bool s_sendmore (void *context, const void *data) {

	zmq::socket_t socket(*(zmq::context_t*)context,ZMQ_PUB);
	socket.bind("tcp://*:5563");
    bool rc = socket.send(data, ZMQ_SNDMORE);

    return (rc);
}
inline static bool s_send (void *socket, zmq::message_t &data, int flags = 0) {


	//bool rc = socket.send(data, flags);

    // return (rc);
    return 1;
}