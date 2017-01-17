#include "mainwindow.h"
#include "ui_mainwindow.h"

bool b_saving_file = false;
int gait_event;
#define Heel_Strike 1
#define Stance 2
#define Heel_OFF 3
#define Swing 4

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer_ = new QTimer(this);
    timer_->stop();
    timer_->setInterval(10);


    QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(updateView()));
    QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(recordData_Thread()));

    ui->pushButton_newFile->setDisabled(true);
    ui->pushButton_save_file->setDisabled(true);

    //add quaternion graph
    ui->leftThigh->addGraph();
    ui->leftShank->addGraph();
    ui->trunk->addGraph();
    ui->rightThigh->addGraph();
    ui->rightShank->addGraph();

    //add Euler angle graph
    ui->leftThigh->addGraph();
    ui->leftShank->addGraph();
    ui->trunk->addGraph();
    ui->rightThigh->addGraph();
    ui->rightShank->addGraph();

}

MainWindow::~MainWindow()
{
    manager->removeSensor(lpms_LT);
    manager->removeSensor(lpms_LT);
    manager->removeSensor(lpms_LS);
    manager->removeSensor(lpms_RS);
    manager->removeSensor(lpms_waist);
    manager->removeSensor(lpms_RF);
    delete manager;
    delete ui;
}

void MainWindow::updateView()
{
    static double milisecond;
    bool sensorConnected_hasData = lpms_LT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LT->hasImuData()
            && lpms_RT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RT->hasImuData() &&
            lpms_LS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LS->hasImuData() &&
            lpms_RS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RS->hasImuData() &&
            lpms_waist->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_waist->hasImuData();

    if (sensorConnected_hasData)
    {
        d = lpms_LT->getCurrentData();
        this->xe_LT.push_back(d.r[0]);  //roll(bank)
//        this->eulerAngle[2] = d.r[1]; //pitch(alttitude)
//        this->eulerAngle[1] = d.r[2]; //yaw(heading)
        d = lpms_LS->getCurrentData();
        this->xe_LS.push_back(d.r[0]);
        d = lpms_RT->getCurrentData();
        this->xe_RT.push_back(d.r[0]);
        d = lpms_RS->getCurrentData();
        this->xe_RS.push_back(d.r[0]);
        d = lpms_waist->getCurrentData();
        this->xe_Waist.push_back(d.r[0]);

        this->lpms_LT->getQuaternion(this->quaternionLT);
        this->lpms_RT->getQuaternion(this->quaternionRT);
        this->lpms_LS->getQuaternion(this->quaternionLS);
        this->lpms_RS->getQuaternion(this->quaternionRS);
        this->lpms_waist->getQuaternion(this->quaternionWaist);
        this->time_e.push_back(milisecond);
    }

    if(time_e.size() % 50 == 0){
        this->updateGraph_quaternion(time_e, xe_LT, xe_LS, xe_RT, xe_RS, xe_Waist);
        if(time_e.size() % 6000 == 0)
        {
            xq_LT.clear();
            xq_LS.clear();
            xq_RT.clear();
            xq_RS.clear();
            xq_Waist.clear();
            time_e.clear();
            milisecond = 0;
        }
    }

    milisecond++;


}

void MainWindow::record_data()
{
    static double milisecond;
    if(b_saving_file)
    {
        QTextStream out(file);
//        QTextStream euler_out(eulerAngleFile);
        out << QString::number(this->quaternionLT[0]) << "\t" << QString::number(this->quaternionLT[1])
                << "\t" << QString::number(this->quaternionLT[2]) << "\t" << QString::number(this->quaternionLT[3])
                << "\t" << QString::number(this->quaternionRT[0]) << "\t" << QString::number(this->quaternionRT[1])
                << "\t" << QString::number(this->quaternionRT[2]) << "\t" << QString::number(this->quaternionRT[3])
                << "\t" << QString::number(this->quaternionLS[0]) << "\t" << QString::number(this->quaternionLS[1])
                << "\t" << QString::number(this->quaternionLS[2]) << "\t" << QString::number(this->quaternionLS[3])
                << "\t" << QString::number(this->quaternionRS[0]) << "\t" << QString::number(this->quaternionRS[1])
                << "\t" << QString::number(this->quaternionRS[2]) << "\t" << QString::number(this->quaternionRS[3])
                << "\t" << QString::number(this->quaternionWaist[0]) << "\t" << QString::number(this->quaternionWaist[1])
                << "\t" << QString::number(this->quaternionWaist[2]) << "\t" << QString::number(this->quaternionWaist[3]);
        out << endl;
    }
    this->quaternionToEuler(this->quaternionLT, this->eulerLT);
    this->quaternionToEuler(this->quaternionLS, this->eulerLS);
    this->quaternionToEuler(this->quaternionRT, this->eulerRT);
    this->quaternionToEuler(this->quaternionRS, this->eulerRS);
    this->quaternionToEuler(this->quaternionWaist, this->eulerWaist);

    this->xq_LT.push_back(eulerLT[0]);
    this->xq_LS.push_back(eulerLS[0]);
    this->xq_RT.push_back(eulerRT[0]);
    this->xq_RS.push_back(eulerRS[0]);
    this->xq_Waist.push_back(eulerWaist[0]);
    this->time_q.push_back(milisecond);

    if(time_q.size() % 50 == 0){
        this->updateGraph_quaternion(time_q, xq_LT, xq_LS, xq_RT, xq_RS, xq_Waist);
        if(time_q.size() % 6000 == 0)
        {
            xq_LT.clear();
            xq_LS.clear();
            xq_RT.clear();
            xq_RS.clear();
            xq_Waist.clear();
            time_q.clear();
            milisecond = 0;
        }
    }

    milisecond++;
}

void MainWindow::quaternionToEuler(float *quaternion, float *eulerAngle)
{
    //ZXY Rotation sequence
    const float r2d = 57.5958f;
    float w = *quaternion;
    float x = *(quaternion + 1);
    float y = *(quaternion + 2);
    float z = *(quaternion + 3);

    float r11 = 2* (x*y + w*z);
    float r12 = w*w + x*x - y*y - z*z;
    float r21 = -2* (x*z - w*y);
    float r31 = 2* (y*z + w*x);
    float r32 = w*w - x*x - y*y + z*z;

    *(eulerAngle + 2) = (float)atan2(r11, r12) * r2d;
    *(eulerAngle + 1) = (float)asin(r21) * r2d;
    *(eulerAngle) = (float)atan2(r31, r32) * r2d;
}

void MainWindow::updateGraph_quaternion(QVector<double> time, QVector<double> leftThigh, QVector<double> rightThigh, QVector<double> leftShank, QVector<double> rightShank, QVector<double> trunk)
{
    //set line color
    ui->leftThigh->graph(0)->setPen(QPen(Qt::blue));
    ui->leftShank->graph(0)->setPen(QPen(Qt::blue));
    ui->rightThigh->graph(0)->setPen(QPen(Qt::blue));
    ui->rightShank->graph(0)->setPen(QPen(Qt::blue));
    ui->trunk->graph(0)->setPen(QPen(Qt::blue));

    ui->leftThigh->graph(0)->setData(time, leftThigh);
    ui->leftShank->graph(0)->setData(time, leftShank);
    ui->trunk->graph(0)->setData(time, trunk);
    ui->rightThigh->graph(0)->setData(time, rightThigh);
    ui->rightShank->graph(0)->setData(time, rightShank);

    //give the axes some labels
    ui->leftShank->xAxis->setLabel("time");
    ui->leftThigh->xAxis->setLabel("time");
    ui->trunk->xAxis->setLabel("time");
    ui->rightThigh->xAxis->setLabel("time");
    ui->rightShank->xAxis->setLabel("time");

    //setAxis
    ui->leftShank->xAxis->setRange(0, 6000);
    ui->leftShank->yAxis->setRange(-90, 90);
    ui->trunk->xAxis->setRange(0, 6000);
    ui->trunk->yAxis->setRange(-90, 90);
    ui->rightThigh->xAxis->setRange(0, 6000);
    ui->rightThigh->yAxis->setRange(-90, 90);
    ui->rightShank->xAxis->setRange(0, 6000);
    ui->rightShank->yAxis->setRange(-90, 90);
    ui->leftThigh->xAxis->setRange(0, 6000);
    ui->leftThigh->yAxis->setRange(-90, 90);

    ui->leftThigh->replot();
    ui->leftShank->replot();
    ui->trunk->replot();
    ui->rightThigh->replot();
    ui->rightShank->replot();
}

void MainWindow::updateGraph_euler(QVector<double> time, QVector<double> leftThigh, QVector<double> rightThigh, QVector<double> leftShank, QVector<double> rightShank, QVector<double> trunk)
{
    //set line color
    ui->leftThigh->graph(1)->setPen(QPen(Qt::red));
    ui->leftShank->graph(1)->setPen(QPen(Qt::red));
    ui->rightThigh->graph(1)->setPen(QPen(Qt::red));
    ui->rightShank->graph(1)->setPen(QPen(Qt::red));
    ui->trunk->graph(1)->setPen(QPen(Qt::red));

    ui->leftThigh->graph(1)->setData(time, leftThigh);
    ui->leftShank->graph(1)->setData(time, leftShank);
    ui->trunk->graph(1)->setData(time, trunk);
    ui->rightThigh->graph(1)->setData(time, rightThigh);
    ui->rightShank->graph(1)->setData(time, rightShank);

    //give the axes some labels
    ui->leftShank->xAxis->setLabel("time");
    ui->leftThigh->xAxis->setLabel("time");
    ui->trunk->xAxis->setLabel("time");
    ui->rightThigh->xAxis->setLabel("time");
    ui->rightShank->xAxis->setLabel("time");

    //setAxis
    ui->leftShank->xAxis->setRange(0, 6000);
    ui->leftShank->yAxis->setRange(-90, 90);
    ui->trunk->xAxis->setRange(0, 6000);
    ui->trunk->yAxis->setRange(-90, 90);
    ui->rightThigh->xAxis->setRange(0, 6000);
    ui->rightThigh->yAxis->setRange(-90, 90);
    ui->rightShank->xAxis->setRange(0, 6000);
    ui->rightShank->yAxis->setRange(-90, 90);
    ui->leftThigh->xAxis->setRange(0, 6000);
    ui->leftThigh->yAxis->setRange(-90, 90);

    ui->leftThigh->replot();
    ui->leftShank->replot();
    ui->trunk->replot();
    ui->rightThigh->replot();
    ui->rightShank->replot();
}

void MainWindow::on_pushButton_save_file_clicked()
{
    b_saving_file = false;
    ui->textBrowser_status->append("Recorded file is saved");
    file->close();
//    eulerAngleFile->close();
}



void MainWindow::on_pushButton_newFile_clicked()
{
    QLocale locale = QLocale(QLocale::English);
    QDate date = QDate::currentDate();
    QString dateString = locale.toString(date, "yyyyMMdd");
    QTime time = QTime::currentTime();
    QString timeString = locale.toString(time, "hhmmss");
    QString filePath = "./Data/" + dateString + "_" + timeString + ".csv";
//    QString euler_filepath = "./Data/" + dateString + "_" + timeString + "euler.csv";
//    ui->textBrowser_status->append("File is saved, " + filePath);

    if(timer_->isActive())
    {
        if(!QDir("Folder").exists())
            QDir().mkdir("Data");
        file = new QFile(filePath);
//        eulerAngleFile = new QFile(euler_filepath);
        b_saving_file = true;
    }
    else
        ui->textBrowser_status->append("Please open device fisrt");
    file->open(QIODevice::WriteOnly | QIODevice::Text);
//    eulerAngleFile->open(QIODevice::WriteOnly | QIODevice::Text);
    ui->pushButton_newFile->setDisabled(true);
    ui->pushButton_save_file->setEnabled(true);


}

void MainWindow::recordData_Thread()
{
    QFuture<void> future = QtConcurrent::run(this, &MainWindow::record_data);
    future.waitForFinished();
}



void MainWindow::on_actionConnect_triggered()
{
    manager = LpmsSensorManagerFactory();
    lpms_LT = manager->addSensor(DEVICE_LPMS_B2, "00:04:3E:9F:E1:3E");
    lpms_RT = manager->addSensor(DEVICE_LPMS_B2, "00:04:3E:9F:E0:F2");
    lpms_LS = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E0:ED");
    lpms_RS = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E0:BB");
    lpms_waist = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E0:B3");

    while(1)
    {
        if(lpms_RT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LT->hasImuData())
        {
            ui->textBrowser_status->append("IMU Left Thigh is connected");
            break;
        }
    }

    while(1)
    {
        if(lpms_RT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RT->hasImuData())
        {
            ui->textBrowser_status->append("IMU Right Thigh is connected");
            break;
        }
    }
    while(1)
    {
        if(lpms_LS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LS->hasImuData())
        {
            ui->textBrowser_status->append("IMU Left Shank is connected");
            break;
        }
    }
    while(1)
    {
        if(lpms_RS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RS->hasImuData())
        {
            ui->textBrowser_status->append("IMU Left Shank is connected");
            break;
        }
    }
    while(1)
    {
        if(lpms_waist->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_waist->hasImuData())
        {
            ui->textBrowser_status->append("IMU Left Shank is connected");
            ui->pushButton_newFile->setEnabled(true);
            timer_->start();
            break;
        }
    }

}
