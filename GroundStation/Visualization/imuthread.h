#ifndef IMUTHREAD_H
#define IMUTHREAD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <string>
#include <iostream>
#include <fstream>

#include "mscl/mscl.h"
#include "../../service/Timestamp.h"
#include <google/protobuf/text_format.h>
#include "../../protobuf/sensors.pb.h"

class imuThread : public QThread
{
	Q_OBJECT
public:
    imuThread(QObject *parent = 0);

    bool stop_flag = false;
    float accel_x = 0.1;
	float accel_y = 0.1;
	float accel_z = 0.1;

	ofstream file;

private slots:
    void stop();

private:
	void run() override;
signals : 
    void send_acc(float, float, float);

};

#endif // IMUTHREAD_H
