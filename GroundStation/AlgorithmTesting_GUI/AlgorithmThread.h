#pragma once

#ifndef ALGORITHMTESTING_H
#define ALGORITHMTESTING_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
// #include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>

#include <zmq.hpp>
#include <zmq.h>
#include "../../protobuf/sensors.pb.h"

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace std;

class AlgorithmThread : public QThread
{
    Q_OBJECT
public:
    explicit AlgorithmThread(QObject *parent = 0);
    bool stop_flag = false;
    void set_input_path(string input_path);
    void set_algorithmIdx(int algoIdx);
    string get_input_path(){return input_path;}
    void set_sensorIdx(int sensorIdx);
    void lane_detection();
    void obj_detection();
private slots:
    void stop();

private:
    void run() override;
    string input_path;
    int sensorIdx;
    int algorithmIdx;
	
signals :
    void send_qimage(QImage, QImage, QString);
	// void send_qimage(QImage, QImage);
	// void send_acc(float, float, float);
    

};

#endif // ALGORITHMTESTING_H