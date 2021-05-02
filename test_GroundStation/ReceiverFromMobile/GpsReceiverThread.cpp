#include "GpsReceiverThread.h"
// #include "../service/Timestamp.h"
#include "../../service/global_name.hpp"
#include "sensors.pb.h"
#include <fstream>
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>

#define PACKET_SIZE 1024
using namespace std;

GpsReceiverThread::GpsReceiverThread(){}

void GpsReceiverThread::run(void *contextRep){
    printf("start (in GpsReceiverThread::run)\n");
    
    // Connect with socket REP with SenderTocloud
    zmq::socket_t socketRep(*(zmq::context_t*)contextRep, ZMQ_REP);
    printf("socketRep\n");
    socketRep.bind(protocol::RECEIVER_FROMMOBILE_REP_TEST); 
    printf("connect\n");
    printf("socket connected (in GpsReceiverThread::run)\n");

    while(1){//!stop_flag){
        printf("while(1) start! (in GpsReceiverThread::run/while(1))\n");
		
        /* RECIEVE FROM MOBILE */
        zmq::message_t msgData;
        socketRep.recv(&msgData);
        printf("Recevied (in GpsReceiverThread::run/while(1))\n");

        sensors::Gps gps;
        unsigned char data[1024] = "\0";
        gps.ParseFromArray(msgData.data(), msgData.size());

        string strTxt;
        google::protobuf::TextFormat::PrintToString(gps, &strTxt);
        cout<<strTxt<<" (in GpsReceiverThread::run/while(1))"<<endl;
        
        /* SEND REPLY TO MOBILE */
        string strOK = "THANK YOU";
        zmq::message_t zmqData(sizeof(strOK));
        memcpy(zmqData.data(), strOK.c_str(), sizeof(strOK));
        s_send(socketRep, zmqData);
        
        /* CONVERT PROTO TO JSON */
        /* ========== 가연이 것 ==================*/
        // string json_string;
        // Json::Value gps_json;
        // gps_json["latitude"] = gps.latitude();
        // gps_json["longtitude"] = gps.longitude();
        // Json::Value data_json;
        // data_json.append(gps_json);

        // Json::StyledWriter writer;
        // json_string = writer.write(gps_json);
        // cout << json_string << endl;
        
        string json_string;
        google::protobuf::util::JsonPrintOptions options;
        options.add_whitespace = true;
        options.always_print_primitive_fields = true;
        options.preserve_proto_field_names = true;
        google::protobuf::util::MessageToJsonString(gps, &json_string, options);
        cout<<json_string<<endl;
        
        std::ofstream ost;
        ost.open("gps.json",std::ios_base::out | std::ios_base::app);
        ost << json_string;

        
        /* OPTIONS */

    }

}

void GpsReceiverThread::stop(){
    stop_flag = true;
}