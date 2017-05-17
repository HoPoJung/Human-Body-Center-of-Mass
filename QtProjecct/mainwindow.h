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
#include <QVector3D>
//#include <QtSerialPort/QSerialPort>
#include "LpmsSensorManagerI.h"
#include "LpmsSensorI.h"
#include <iostream>
#include <string>
#include <cmath>
#include "engine.h"
#include "matrix.h"

#pragma comment (lib, "libmat.lib")
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libeng.lib")

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
    void initHumanSkeletonModel();
    void motionCaptureAnimation();
    void sendQuaternionDataToMatlab();
    void sendAngularDataToMatlab();

private slots:

    void on_pushButton_save_file_clicked();

    void on_pushButton_newFile_clicked();

    void on_actionConnect_Left_Thigh_IMU_triggered();

    void on_actionConnect_Right_Thigh_IMU_triggered();

    void on_actionLeft_Shank_IMU_triggered();

    void on_actionRight_Shank_IMU_triggered();

    void on_actionLeft_Foot_IMU_triggered();

    void on_actionRight_Foot_IMU_triggered();

    void on_actionWaist_triggered();

    void on_actionCalibration_triggered();

private:
    Ui::MainWindow *ui;
    ImuData d_waist, d_leftThigh, d_rightThigh, d_leftShank, d_rightShank, d_leftFoot, d_rightFoot;
    LpmsSensorI* lpms_LT;
    LpmsSensorI* lpms_RT;
    LpmsSensorI* lpms_LS;
    LpmsSensorI* lpms_RS;
    LpmsSensorI* lpms_waist;
    LpmsSensorI* lpms_RF;  //thigh, shank, foot
    LpmsSensorI* lpms_LF;
    LpmsSensorManagerI* manager;
    QFile *file;
//    QFile *eulerAngleFile;
    //Angle data (both quaternion and Euler angle)
    QTimer* timer_;
    double eulerAngle[3];
    float quaternionLT[4], quaternionRT[4], quaternionLS[4], quaternionRS[4], quaternionWaist[4];
    float eulerLT[3], eulerRT[3], eulerLS[3], eulerRS[3], eulerWaist[3];
    double angle_rightThigh[3], angle_rightShank[3], angle_leftShank[3], gyro_rightFoot[3], gyro_leftFoot[3];
    QVector<double> xq_LT, xq_LS, xq_RT, xq_RS, xq_Waist; // quaternion data in sagittal plane
    QVector<double> time_q, time_e; //Euler time, quaternion time
    //QSerialPort *port;

    void record_data();
    void quaternionToEuler(float* quaternion, float* eulerAngle);
    void updateGraph_quaternion(QVector<double> time, QVector<double> leftThigh, QVector<double> rightThigh, QVector<double> leftShank, QVector<double> rightShank, QVector<double> trunk);
    //void updateGraph_euler(QVector<double> time, QVector<double> leftThigh, QVector<double> rightThigh, QVector<double> leftShank, QVector<double> rightShank, QVector<double> trunk);

    //matlab private data member, human joint data
    Engine *m_engine;
    double **humanJoint;
    mxArray* m_angleRightThigh;
    mxArray* m_angleRightShank;
    mxArray* m_angleLeftShank;
    mxArray* m_gyroRightFoot;
    mxArray* m_gyroLeftFoot;

    mxArray* m_rightThighArray;
    mxArray* m_rightShankArray;
    mxArray* m_leftShankArray;
    mxArray* m_rightFootArray;
    mxArray* m_leftFootArray;
    mxArray* m_timestamp;
    mxArray* m_time;


    //declare human limb
    double **lowerBack_left;
    double **lowerBack_right;
    double **upperChest_left;
    double **upperChest_right;
    double **shoulder_line;
    double **hip_line;
    double **thigh_left;
    double **thigh_right;
    double **shank_left;
    double **shank_right;
    double **foot_left;
    double **foot_right;
    double **flatFoot_left;
    double **flatFoot_right;
    double **footBack_left;
    double **footBack_right;
    double **upperArm_left;
    double **upperArm_right;
    double **forarm_left;
    double **forarm_right;
};

#endif // MAINWINDOW_H
