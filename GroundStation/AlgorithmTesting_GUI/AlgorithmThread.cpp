#pragma once
#include "AlgorithmThread.h"

enum Sensor { lidar, cam, can, imu, gps};

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

AlgorithmThread::AlgorithmThread(QObject *parent) : QThread(parent)
{

}

void AlgorithmThread::lane_detection(){
    zmq::context_t ctx(1);
    zmq::socket_t algorithmTesting_sub(ctx, ZMQ_SUB);
    algorithmTesting_sub.connect("tcp://localhost:9899");
    algorithmTesting_sub.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    printf("[AlgorithmThread::lane_detection] connect\n");

    int frame_cnt = 0;
    float millis_sum = 0;


    while(!stop_flag){
        printf("[AlgorithmThread::lane_detection] while\n");
        // [ Setting ]
        sensors::algorithm_img algo_img;        

        // < receive message from pub(=diva2/GroundStation/AlgorithmTesting/main) >
        zmq::message_t msg;
        cv::Mat frame_original;
        frame_original.create(480, 640, CV_8UC3);
        cv::Mat frame_result;
        frame_result.create(480, 640, CV_8UC3);

        // < parsing serialized data to message >
        // algo_img.ParseFromArray(msg.data(), msg.size());
        algorithmTesting_sub.recv(&msg);
        if((int)(msg.size())==3){
            printf("[AlgorithmThread::lane_detection] The size of msg is only %dbytes\n", msg.size());
            printf("[AlgorithmThread::lane_detection] Finish this program\n");
            break;
        }
        frame_cnt++;
        printf("[AlgorithmThread::lane_detection] msg size = %d\n", msg.size());

        std::string _buff = std::string(static_cast<char *>(msg.data()), msg.size());
        algo_img.ParseFromString(_buff);
        float millis = algo_img.millis_term();
        millis_sum += millis;
        float fps = (float)(1000*frame_cnt)/(float)(millis_sum);
        printf("fps=%f\n", fps);

        // [ Preprocessing for Visualization ]
        // < Setting for original image >
        memcpy((void*)frame_original.data, (void*)(&algo_img.image_original()[0]),
                    frame_original.step[0]*(size_t)frame_original.rows);
        // cv::cvtColor(frame_original, frame_original, cv::COLOR_BGR2RGB);
        
        // < Setting for result image >
        memcpy((void*)frame_result.data, (void*)(&algo_img.image_result()[0]),
                    frame_result.step[0]*(size_t)frame_result.rows);
        // cv::cvtColor(frame_result, frame_result, cv::COLOR_BGR2RGB);
        
        // [ Visualization at Qt GUI ]
        QImage image_original(frame_original.size().width, frame_original.size().height, QImage::Format_RGB888);
        memcpy(image_original.scanLine(0), frame_original.data, 
            static_cast<size_t>(image_original.width() * image_original.height() * frame_original.channels()));
        
        QImage image_result(frame_result.size().width, frame_result.size().height, QImage::Format_RGB888);
        memcpy(image_result.scanLine(0), frame_result.data, 
            static_cast<size_t>(image_result.width() * image_result.height() * frame_result.channels()));
        
        emit send_qimage(image_original, image_result, QString::number(fps)); 
        // emit send_qimage(image_original, image_result);
    }

    printf("[AlgorithmThread::lane_detection] end\n");
    exit(0);
}

void AlgorithmThread::obj_detection(){

    // [ Setting ]
    // < Zeromq >
    void *ctx = zmq_ctx_new();
    void *socketSub = zmq_socket(ctx, ZMQ_REP);
    int rc = -1;
    rc = zmq_connect(socketSub, "tcp://localhost:9899");
    printf("[AlgorithmThread::obj_detection] connect:%d\n", rc);

    // < Input File >
    printf("[AlgorithmThread::obj_detection] get input files\n");
    vector<string> fileName;
    DIR *d = opendir(get_input_path().c_str());
    struct dirent *dir;
    vector<string> fileList;
    int i=0;
    if (d){
        while ((dir = readdir(d)) != NULL){
            string d_name = dir->d_name;
            if((d_name.compare("..")==0) || (d_name.compare(".")==0))
                continue;
            i++;
            fileList.push_back(d_name);
        }
        for(int i=0;i<fileList.size();i++) {
            printf("... %s\n",fileList[i].c_str());
            // doSomething(fileList[i]);
        }
        closedir(d);
    }
    
    // < Variables > 
    int frame_cnt = 0;
    float millis_sum = 0;
    int count = 0;

    
    // [PROTOCOL0: START SIGNAL]
    printf("[zeromq] Protocol%d: Start Signal\n", count++);
    char buf [512];
    int nbytes = zmq_recv (socketSub, buf, 512, 0);
    assert (nbytes != -1);
    printf("[AlgorithmThread::obj_detection] ... recv %d bytes\n", nbytes);
    if(strcmp(buf, "start")==0){
        printf("[AlgorithmThread::obj_detection] ... ... content: %s\n",buf);
    }

    int len;
    string fn;
    while(!stop_flag){
        printf("[AlgorithmThread::obj_detection] while\n");
        // [ Setting ]
        cv::Mat frame_original;
        frame_original.create(480, 640, CV_8UC3);
        cv::Mat frame_result;
        frame_result.create(480, 640, CV_8UC3);

        // [ Communicate ]
        // < Send a file name of original image >
        printf("[AlgorithmThread::obj_detection] [zeromq] Protocol%d: Communicate file name\n",count);
        // len = sprintf(buf,
        //     "/home/diva2/diva2/test/obj_detection/darknet/data/test/testcone%d.jpg",count-1);
        len = sprintf(buf,
            "%s/%s",get_input_path().c_str(), fileList[count].c_str());
        buf[len] = '\0';
        rc = zmq_send(socketSub, buf, len+1, 0);
        assert (rc > 0);
        printf("[AlgorithmThread::obj_detection] ... send result = %d\n", rc);
        printf("[AlgorithmThread::obj_detection] ... ... content: %s\n", buf);
        fn = buf;
        
        // < Receive a file name of result image >
        printf("[AlgorithmThread::obj_detection] ... ready to read\n");
        nbytes = zmq_recv (socketSub, buf, 512, 0);
        assert (nbytes != -1);
        printf("[AlgorithmThread::obj_detection] ... recv%d bytes\n", nbytes);
        printf("[AlgorithmThread::obj_detection] ... ... content: %s\n", buf);
        float milli_second = atof(buf);
        printf("[AlgorithmThread::obj_detection] ... ... content: %f\n", milli_second);
        printf("\n");
        frame_cnt++;

        // [ Image Processing ]
        // < Read an original image >
        cv::Mat mat;
        mat = cv::imread(fn);
        cv::resize(mat, frame_original, cv::Size(640, 480));
        cv::cvtColor(frame_original, frame_original, cv::COLOR_BGR2RGB);
        
        // < Get a result file name >
        char delimeter[] = "/";
        char *result;
        char parsing[20][30];
        char result_filename[512];
        memset(result_filename, '\0', sizeof(char)*512);
        char c_input_path[512];
        strcpy(c_input_path,input_path.c_str());
        result = strtok(c_input_path, delimeter);
        int cnt=0;
        while(result!=NULL){
            strcpy(parsing[cnt++], result);
            result = strtok(NULL, delimeter);
        }
        for(int i=0; i<cnt-1; i++){
            sprintf(result_filename, "%s/%s", result_filename, parsing[i]);
        }
        len = sprintf(result_filename, "%s/%s/%s", result_filename, "result", fileList[count].c_str());
        printf("[AlgorithmThread::obj_detection] ... ... result = %s\n", result_filename);

        // < Resize to 640*480>
        mat = cv::imread(result_filename);
        int width = mat.size().width;
        int height = mat.size().height;
        cv::resize(mat, frame_result, cv::Size(640, 480));
        cv::cvtColor(frame_result, frame_result, cv::COLOR_BGR2RGB);
        // imshow(buf, mat);
        // waitKey(0);
        // destroyAllWindows();

        // [ Visualization at Qt GUI ]
        QImage image_original(frame_original.size().width, frame_original.size().height, QImage::Format_RGB888);
        memcpy(image_original.scanLine(0), frame_original.data, 
            static_cast<size_t>(image_original.width() * image_original.height() * frame_original.channels()));
        
        QImage image_result(frame_result.size().width, frame_result.size().height, QImage::Format_RGB888);
        memcpy(image_result.scanLine(0), frame_result.data, 
            static_cast<size_t>(image_result.width() * image_result.height() * frame_result.channels()));
        
        
        millis_sum += milli_second;
        float fps = frame_cnt/millis_sum;
        printf("[AlgorithmThread::obj_detection] fps = %f\n", fps);
        emit send_qimage(image_original, image_result, QString::number(fps)); 
        // emit send_qimage(image_original, image_result);

        count++;
    }

    printf("[AlgorithmThread::obj_detection] end\n");
    exit(0);

}
void AlgorithmThread::run(){
    printf("[AlgorithmThread::run] start\n");
    printf("   sensorIdx:%d\n", this->sensorIdx);
    printf("   algorithmIdx:%d\n", this->algorithmIdx);
    printf("   input path:%s\n", this->input_path.c_str());
    printf("\n");
    
    if((sensorIdx==Sensor::cam) && (algorithmIdx==0)){
        lane_detection();
    }else if((sensorIdx==Sensor::cam) && (algorithmIdx==1)){
        obj_detection();
    }
    
    printf("[AlgorithmThread::run] end\n");
    exit(0);
}

void AlgorithmThread::stop(){
    stop_flag = true;
}

void AlgorithmThread::set_input_path(string input_path){
    this->input_path = input_path;
}

void AlgorithmThread::set_algorithmIdx(int algoIdx){
    this->algorithmIdx = algoIdx;
}
void AlgorithmThread::set_sensorIdx(int sensorIdx){
    this->sensorIdx = sensorIdx;
}