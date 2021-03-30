//#pragma once
#ifndef CAMSENSINGTHREAD_H_
#define CAMSENSINGTHREAD_H_
#include "CamSensing.cpp"

inline static bool S_sendmore(zmq::socket_t &publisher, const void *data)
{

    bool rc = publisher.send(data, ZMQ_SNDMORE);

    return (rc);
}

inline static bool S_send(zmq::socket_t &publisher, zmq::message_t &data, int flags = 0)
{
    bool rc = publisher.send(data, flags);

    return (rc);
}

class CamSensingThread
{
public:
    CamSensingThread();
    static void run(const int devicename, zmq::context_t *context, zmq::socket_t *publisher);
};

CamSensingThread::CamSensingThread()
{
}

void CamSensingThread::run(const int devicename, zmq::context_t *context, zmq::socket_t *publisher)
{

    CamSensing camThread;
    int open = camThread.initialize(devicename);
    cout << "cam open" << endl;
    cout << "open : " << open << endl;
    vector<uchar> buffer;

    while (open)
    {
        camThread.cap.read(camThread.frame);
        cout << "cap read" << endl;
        camThread.cap >> camThread.frame;
        cout << "cap>>frame" << endl;
        imencode(".jpg", camThread.frame, buffer); //image encode -> jpg
        cout << "img encode(jpg)" << endl;

        S_sendmore(*publisher, "CAM");
        cout << "sendmore" << endl;

        zmq::message_t msg(&buffer, sizeof(buffer), NULL);
        bool send_ok = S_send(*publisher, msg);
        if (send_ok)
        {
            cout << "send ok!" << endl;

            string m_time = camThread.ts.getMilliTime();
            string save_path = "/home/dahye/Documents/CAM/webcam_" + m_time + ".jpg";
            int write_ok = imwrite(save_path.c_str(), camThread.frame, camThread.Compression_params);
            if (write_ok)
                cout << "jpg saved" << endl;
            sleep(1);
        }
    }
}

////send ok

// // void CamSensingThread::run(void *context)
// // {

// // }

// #include "CamSensing.h"

// int main()
// {
//     zmq::context_t context(1);
//     zmq::socket_t publisher(context, ZMQ_PUB);
//     publisher.bind("tcp://*:9158"); // here is the binding address
//     //open webcam
//     cap.open(0);
//     vector<uchar> buffer;

//     while (1)
//     {
//         buffer.clear(); //initialize

//         cap.read(frame);
//         cap >> frame;
//         // imshow("frame", frame);
//         // if (waitKey() == 'q')
//         //     destroyAllWindows();
//         imencode(".jpg", frame, buffer);
//         zmq::message_t msg(buffer.size());
//         memcpy(msg.data(), buffer.data(), buffer.size());
//         //  Write two messages, each with an envelope and content
//         s_sendmore(publisher, "CAM_RAW");
//         bool ok = publisher.send(msg); // send data
//         if (!ok)
//         {
//             cout << "send failed" << endl;
//         }
//         else
//         {
//             cout << "send ok" << endl;
//         }
//     }
//     return 0;
// }

#endif //CAMSENSINGTHREAD_H_