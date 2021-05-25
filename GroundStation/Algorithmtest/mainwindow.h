#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QListWidget>

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
    QDir dir;
    QFileInfoList list;
    ~MainWindow();

private slots:
//    void on_pushButton_clicked();
//    void on_pushButton_2_clicked();
//    void on_listView_activated(const QModelIndex &index);
    void on_pushButton_select_clicked();

//    void on_pushButton_open_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

//    Ui::MainWindow listDir;
};
#endif // MAINWINDOW_H
