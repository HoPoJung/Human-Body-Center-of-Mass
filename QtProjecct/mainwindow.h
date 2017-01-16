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
#include <QVector>
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
    //Angle data (both quaternion and Euler angle)
    QTimer* timer_;
    double eulerAngle[3];
    float quaternionLT[4], quaternionRT[4], quaternionLS[4], quaternionRS[4], quaternionWaist[4];
    float eulerLT[3], eulerRT[3], eulerLS[3], eulerRS[3], eulerWaist[3];
    QVector<double> xe_LT, xe_LS, xe_RT, xe_RS, xe_Waist; // euler angle in sagittal plane
    QVector<double> xq_LT, xq_LS, xq_RT, xq_RS, xq_Waist; // quaternion data in sagittal plane
    QVector<double> time;
    //QSerialPort *port;

    void record_data();
    void quaternionToEuler(float* quaternion, float* eulerAngle);
    void updateGraph_quaternion(QVector<double> time, QVector<double> leftThigh, QVector<double> rightThigh, QVector<double> leftShank, QVector<double> rightShank, QVector<double> trunk);
    void updateGraph_euler(QVector<double> time, QVector<double> leftThigh, QVector<double> rightThigh, QVector<double> leftShank, QVector<double> rightShank, QVector<double> trunk);

};

#endif // MAINWINDOW_H
