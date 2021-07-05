#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>

#include <iostream>
#include <cstring>
#include <fstream>

#include "../../service/Timestamp.h"
#include <google/protobuf/text_format.h>
#include "../../protobuf/sensors.pb.h"

class canThread : public QThread
{
	Q_OBJECT

public:
    canThread(QObject *parent = 0);

    bool stop_flag = false;

    ofstream file;

signals:
	void send_speed(float);
	void send_handle(QString);
	void send_gear(int);
	void send_turn(int);
	void send_end();

public slots:
	void stop();
private:
    void run() override;
};

#endif // CANTHREAD_H
