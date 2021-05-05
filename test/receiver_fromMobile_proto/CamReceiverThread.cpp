#include "CamReceiverThread.h"
#include "../service/Timestamp.h"
#include "../service/global_name.hpp"
#include "../protobuf/sensors.pb.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

#include <fstream>
#include "jsoncpp/json/json.h"
#pragma comment(lib, "jsoncpp\\lib\\lib_json.lib")
#pragma warning(disable : 4996) //error C4996 뜨는 경우

#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>

#define PACKET_SIZE 1024
using namespace cv;

using namespace std;

CamReceiverThread::CamReceiverThread(){}
int protoTypeToCV(const sensors::ChannelOrder& proto_type);

void CamReceiverThread::run(void *contextRep){
    printf("start (in CamReceiverThread::run)\n");
    
    // Connect with socket REP with SenderTocloud
    zmq::socket_t socketRep(*(zmq::context_t*)contextRep, ZMQ_REP);
    printf("socketRep\n");
    socketRep.bind(protocol::RECEIVER_FROMMOBILE_REP_TEST); 
    printf("connect\n");
    printf("socket connected (in CamReceiverThread::run)\n");

    while(1){//!stop_flag){
        printf("while(1) start! (in CamReceiverThread::run/while(1))\n");
		
        /* RECIEVE FROM MOBILE */
        zmq::message_t msgData;
        socketRep.recv(&msgData);
        printf("Recevied (in CamReceiverThread::run/while(1))\n");

        sensors::Cam cam;
        unsigned char data[1024] = "\0";
        cam.ParseFromArray(msgData.data(), msgData.size());

        // CHECK THE IMAGE - 참고: https://github.com/linklab-uva/deepracing/blob/adca1d1a724c4d930e3a5b905a039da5a143a561/data-logger/src/image_logging/utils/opencv_utils.cpp
        cv::Mat frame;
        frame.create(cam.rows(), cam.cols(), protoTypeToCV(cam.channel_order()));
        memcpy((void *) frame.data, (void *)(&(cam.image_data()[0])), frame.step[0] * (size_t)frame.rows );
        
        imshow("test", frame);
        waitKey(0);

        /* SEND REPLY TO MOBILE */
        string strOK = "THANK YOU";
        zmq::message_t zmqData(sizeof(strOK));
        memcpy(zmqData.data(), strOK.c_str(), sizeof(strOK));
        s_send(socketRep, zmqData);
        
        /* CONVERT PROTO TO JSON */
        /* ========== 가연이 것 ==================*/
        // string json_string;
        // Json::Value Cam_json;
        // Cam_json["latitude"] = Cam.latitude();
        // Cam_json["longtitude"] = Cam.longitude();
        // Json::Value data_json;
        // data_json.append(Cam_json);

        // Json::StyledWriter writer;
        // json_string = writer.write(Cam_json);
        // cout << json_string << endl;
        
        /*
        string json_string;
        google::protobuf::util::JsonPrintOptions options;
        options.add_whitespace = true;
        options.always_print_primitive_fields = true;
        options.preserve_proto_field_names = true;
        google::protobuf::util::MessageToJsonString(Cam, &json_string, options);
        cout<<json_string<<endl;
        
        std::ofstream ost;
        ost.open("Cam.json",std::ios_base::out | std::ios_base::app);
        ost << json_string;
        */
        
        /* OPTIONS */

    }

}

void CamReceiverThread::stop(){
    stop_flag = true;
}


int protoTypeToCV(const sensors::ChannelOrder& proto_type)
{
  switch(proto_type)
  {
  case sensors::ChannelOrder::BGR:
  {
    return CV_8UC3;
  }
  case sensors::ChannelOrder::BGRA:
  {
    return CV_8UC4;
  }
  case sensors::ChannelOrder::GRAYSCALE:
  {
    return CV_8U;
  }
  default:
  {
    std::string err = "Unsupported image type: " + google::protobuf::GetEnumDescriptor< sensors::ChannelOrder >()->value(proto_type)->name();
    std::cerr << err << std::endl;
    throw std::runtime_error(err);
  }

  }
}