#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QLocale>
#include <QDateTime>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QFuture>
#include <QDir>
#include <QtConcurrent/QtConcurrent>
//#include <QtSerialPort/QSerialPort>
#include "LpmsSensorManagerI.h"
#include "LpmsSensorI.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void recordData_Thread();
    void updateView();

private slots:

    void on_pushButton_save_file_clicked();

    void on_pushButton_newFile_clicked();

    void on_actionConnect_triggered();

private:
    Ui::MainWindow *ui;
    ImuData d;
    LpmsSensorI* lpms_LT;
    LpmsSensorI* lpms_RT;
    LpmsSensorI* lpms_LS;
    LpmsSensorI* lpms_RS;
    LpmsSensorI* lpms_waist;
    LpmsSensorI* lpms_RF;  //thigh, shank, foot
    LpmsSensorManagerI* manager;
    QFile *file;
//    QFile *eulerAngleFile;
    QTimer* timer_;
    double eulerAngle[3];
    float quaternionLT[4], quaternionRT[4], quaternionLS[4], quaternionRS[4], quaternionWaist[4];
    //QSerialPort *port;

    void record_data();
    void quaternionToEuler(float* quaternion, float* eulerAngle);
};

#endif // MAINWINDOW_H
