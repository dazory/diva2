/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label;
    QLabel *label_2;
    QGraphicsView *graphicsView_2;
    QLabel *label_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_select;
    QListWidget *listDir;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1512, 776);
        MainWindow->setStyleSheet(QString::fromUtf8("QLabel{ \n"
"border-radius: 2px;\n"
"padding: 2px;\n"
"background-color: rgba(0, 0, 128, 1.0);\n"
"font: bold italic 15px;\n"
"color:white;\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"    color:rgba(0, 0, 128, 1.0);\n"
"    background-color: white;\n"
"    border-color: white;\n"
"    border-width: 1px;\n"
"    border-style: solid;\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}\n"
"\n"
"QPushButton{ \n"
"border-radius: 2px;\n"
"padding: 2px;\n"
"background-color: rgba(0, 0, 128, 1.0);\n"
"font: bold italic 15px;\n"
"color:white;\n"
"}\n"
"\n"
"background-color : rgb(173, 127, 168)\n"
"\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 130, 191, 25));
        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(20, 210, 191, 25));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 100, 61, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 180, 91, 21));
        graphicsView_2 = new QGraphicsView(centralwidget);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(340, 70, 1041, 581));
        graphicsView_2->setStyleSheet(QString::fromUtf8(""));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(840, 30, 61, 21));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(100, 660, 89, 25));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 300, 71, 20));
        pushButton_select = new QPushButton(centralwidget);
        pushButton_select->setObjectName(QString::fromUtf8("pushButton_select"));
        pushButton_select->setGeometry(QRect(20, 260, 131, 21));
        listDir = new QListWidget(centralwidget);
        listDir->setObjectName(QString::fromUtf8("listDir"));
        listDir->setGeometry(QRect(20, 330, 256, 311));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1512, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "lidar", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "cam", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "can", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "imu", nullptr));
        comboBox->setItemText(4, QApplication::translate("MainWindow", "gps", nullptr));

        comboBox_2->setItemText(0, QApplication::translate("MainWindow", "Lane Detection", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("MainWindow", "Object Detection", nullptr));

        label->setText(QApplication::translate("MainWindow", "Sensor", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Algorithm", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Result", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "play", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "File list", nullptr));
        pushButton_select->setText(QApplication::translate("MainWindow", "select directory", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
