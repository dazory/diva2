#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPixmap bg("/home/kayeon/Desktop/color.jpeg");

           QPalette p(palette());
           p.setBrush(QPalette::Background, bg);

           setAutoFillBackground(true);
           setPalette(p);

    ui->setupUi(this);
}


//void MainWindow::on_pushButton_exit_clicked()
//{
//    // close window
//    this ->close();
//}

//void MainWindow::on_pushButton_select_clicked()
//{
//    // show exisiting directory
//    dir = QFileDialog::getExistingDirectory();
//    dir.setFilter(QDir::Files | QDir::NoSymLinks);

//    ui->listDir->clear();
//    list = dir.entryInfoList();

//    // loop for file print
//    for(int i = 0; i < list.size(); ++i){
//        QFileInfo fileInfo = list.at(i);
//        ui -> listDir ->addItem(QString("%1").arg(fileInfo.fileName()));
//    }
//}

//void MainWindow::on_pushButton_open_clicked()
//{
//    QString path, filename;

//    // get filename to absolute path
//    filename = QString("%1").arg(list.at(ui->listDir->currentIndex().row()).absoluteFilePath());
//    QFile file(filename);
//    file.open(QIODevice::ReadOnly);

//    // textFile clear and print file list
//    ui->textFile->clear();
//    ui->textFile->append(file.readAll());
//    file.close();

//    QMessageBox msgbox;
//    msgbox.setText("File Opened");
//    msgbox.exec();
//}

//void MainWindow::on_pushButton_save_clicked()
//{
//    QString path, filename;

//    // get filename to absolute path
//    filename = QString("%1").arg(list.at(ui->listDir->currentIndex().row()).absoluteFilePath());

//    // add .text
//    QFile file(filename + ".text");

//    // Insert into the array after encoding.
//    QByteArray bytearray = ui->textFile->toPlainText().toUtf8().left(ui->textFile->toPlainText().length());

//    file.open(QIODevice::WriteOnly);
//    file.write(bytearray);
//    file.close();

//    QMessageBox msgbox;
//    msgbox.setText("File Saved");
//    msgbox.exec();
//}


////출처: https://redcoder.tistory.com/133 [로재의 개발 일기]
///

//void MainWindow::on_pushButton_clicked()
//{
//    QString dir = QFileDialog::getExistingDirectory(this,"file", QDir::currentPath(), QFileDialog::ShowDirsOnly);
//    qDebug()<<dir;
//}

//void MainWindow::on_pushButton_clicked()
//{
////    QString file = QFileDialog::getOpenFileName(this, "file", "/home/kayeon", "Files (*.*)");
////    //각자의 파일 경로로 바꿔야 함
////    qDebug() << file;
//}

MainWindow::~MainWindow()
{
    delete ui;
}


//void MainWindow::on_pushButton_2_clicked()
//{s
//    QString file = QFileDialog::getOpenFileName(this, "file", "/home/kayeon", "Files (*.*)");
//    //각자의 파일 경로로 바꿔야 함
//    qDebug() << file;
//}

//void MainWindow::on_listView_activated(const QModelIndex &index)
//{

//}

void MainWindow::on_pushButton_select_clicked()
{
        // show exisiting directory
        dir = QFileDialog::getExistingDirectory();
        dir.setFilter(QDir::Files | QDir::NoSymLinks);

        ui->listDir-> clear();
        list = dir.entryInfoList();

        // loop for file print
        for(int i = 0; i < list.size(); ++i){
            QFileInfo fileInfo = list.at(i);
            ui -> listDir ->addItem(QString("%1").arg(fileInfo.fileName()));
        }
//        QString path, filename;

//        // get filename to absolute path
//        filename = QString("%1").arg(list.at(ui->listDir->currentIndex().row()).absoluteFilePath());
//        QFile file(filename);
//        file.open(QIODevice::ReadOnly);


    //출처: https://redcoder.tistory.com/133?category=800800 [로재의 개발 일기]
}

//void MainWindow::on_pushButton_open_clicked()
//{
//        QString path, filename;

//        // get filename to absolute path
//        filename = QString("%1").arg(list.at(ui->listDir->currentIndex().row()).absoluteFilePath());
//        QFile file(filename);
//        file.open(QIODevice::ReadOnly);

//        // textFile clear and print file list
//        ui->textFile->clear();
//        ui->textFile->append(file.readAll());
//        file.close();

//        QMessageBox msgbox;
//        msgbox.setText("File Opened");
//        msgbox.exec();

//}
