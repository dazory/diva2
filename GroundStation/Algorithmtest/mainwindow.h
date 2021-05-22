#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_clicked();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
