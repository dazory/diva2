#ifndef __GLOBAL_NAME_H__
#define __GLOBAL_NAME_H__
#include "string"
using namespace std;

namespace protocol
{
    const string SENSING_PUB = "tcp://*:5563";
    const string SENSING_SUB = "tcp://localhost:5563";
    const string SENDER_TOCLOUD_PUB = "tcp://*:5564";
} // namespace protocol

#endif __GLOBAL_NAME_H__