#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QListWidget>
#include <QLabel>

#include <string>

#include "AlgorithmThread.h"
#include "ModelRunThread.h"


using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
//    void on_pushButton_exit_clicked();
//    void on_pushButton_select_clicked();
//    void on_pushButton_open_clicked();
//    void on_pushButton_save_clicked();
    //void on_pushButton_clicked();
    QDir data_path;
    QDir config_path;
    QDir weight_path;
    QDir input_path;
    QFileInfoList list;
    ~MainWindow();

    QLabel *originalImageWidget;
    QLabel *resultImageWidget;
    QLabel *fpsWidget;

public slots:
    void display_original(QImage image, QImage image_result, QString fps);
    // void display_original(QImage image, QImage image_result);


private slots:
    void on_pb_Play_clicked();
    void on_cb_Sensor_currentIndexChanged(int index);
    void on_cb_Algorithm_currentIndexChanged(int index);
    void on_pb_Select_ConfigFile_clicked();
    void on_pb_Select_WeightFile_clicked();
    void on_pb_Select_DataFile_clicked();
    void on_pb_Select_Directory_clicked();

//    void on_pushButton_select_clicked();
//    void on_pushButton_clicked();
//    void on_comboBox_currentIndexChanged(int index);
//    void on_comboBox_2_currentIndexChanged(int index);
//    void on_pushButton_3_clicked();
//    void on_pushButton_4_clicked();
//    void on_pushButton_open_clicked();

private:
    Ui::MainWindow *ui;
    class AlgorithmThread::AlgorithmThread *algorithmThread;
    class ModelRunThread::ModelRunThread *modelRunThread;

//    Ui::MainWindow listDir;
};
#endif // MAINWINDOW_H
