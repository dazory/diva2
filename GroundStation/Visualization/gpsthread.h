#ifndef GPSTHREAD_H
#define GPSTHREAD_H

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
#include <zmq.hpp>
#include <google/protobuf/text_format.h>
#include "../../protobuf/sensors.pb.h"

using namespace std;

class gpsThread : public QThread
{
     Q_OBJECT
public:
    explicit gpsThread(QObject *parent = 0);

    bool stop_flag = false;
    double Convert_to_dd(double raw);

    double latitude=0, longitude=0, hdop=0;

    ofstream file;

public slots:
    void stop();

private:
    void run() override;

signals:
    void send_ll(QString, QString, double);
    void send_end();

};

#endif // GPSTHREAD_H
