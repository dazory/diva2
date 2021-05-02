#pragma once
#include "zmq.hpp"
#include "message.pb.h"
#include <string>
#include <iostream>


int main ()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::Person person; //fill a person data
    person.set_id(1234);
    person.set_name("john");
    person.set_email("john@mycompany.com");
    tutorial::Person::PhoneNumber* phone_number = person.add_phone();
    phone_number->set_number("1234567");
    phone_number->set_type(tutorial::Person::MOBILE);
    phone_number = person.add_phone();
    phone_number->set_number("7654321");
    phone_number->set_type(tutorial::Person::HOME);

    //  Prepare our context and socket
    zmq::context_t context (1);
    // Note we use here a PAIR socket, only 1 way message
    zmq::socket_t socket (context, ZMQ_PAIR);

    std::cout << "Connecting to server" << std::endl;
    socket.connect ("tcp://localhost:5555");

    std::string msg_str;
    person.SerializeToString(&msg_str);
    // create a zmq message from the serialized string
    zmq::message_t request (msg_str.size());
    memcpy ((void *) request.data (), msg_str.c_str(), msg_str.size());
    std::cout << "Sending Person data ..." << std::endl;
    socket.send (request);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}