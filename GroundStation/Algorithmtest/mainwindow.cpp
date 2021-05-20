#include "mainwindow.h"
#include "ui_mainwindow.h"

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

MainWindow::~MainWindow()
{
    delete ui;
}

