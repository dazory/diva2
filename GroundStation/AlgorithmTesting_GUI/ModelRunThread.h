#pragma once

#ifndef MODELRUNTHREAD_H
#define MODELRUNTHREAD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
// #include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class ModelRunThread : public QThread
{
    Q_OBJECT
public:
    explicit ModelRunThread(QObject *parent = 0);
    bool stop_flag = false;
    void set_algorithmIdx(int algoIdx);
    void set_sensorIdx(int sensorIdx);
    void set_datafile(string datafile);
    void set_configfile(string configfile);
    void set_weightfile(string weightfile);
	
private slots:
    void stop();

private:
    void run() override;
    int sensorIdx;
    int algorithmIdx;
    string str_datafile;
    string str_configfile;
    string str_weightfile;


};

#endif // ALGORITHMTESTING_H