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

    //setting legend on graph
    ui->leftThigh->legend->setVisible(true);
    ui->leftShank->legend->setVisible(true);
    ui->rightThigh->legend->setVisible(true);
    ui->rightShank->legend->setVisible(true);
    ui->trunk->legend->setVisible(true);
    //set up legend fond size
    QFont legendFont = font();

    legendFont.setPointSize(9);
    ui->leftThigh->legend->setFont(legendFont);
    ui->leftShank->legend->setFont(legendFont);
    ui->rightThigh->legend->setFont(legendFont);
    ui->rightShank->legend->setFont(legendFont);
    ui->trunk->legend->setFont(legendFont);
    //set up legend background color
    ui->leftThigh->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    ui->leftShank->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    ui->rightThigh->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    ui->rightShank->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    ui->trunk->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    //set up legend layout
    ui->leftThigh->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    ui->leftShank->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    ui->rightThigh->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    ui->rightShank->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    ui->trunk->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

    initHumanSkeletonModel();

    //initialize angle & gyro data of matlab variable
//    m_angleRightThigh =  mxCreateDoubleMatrix(3, 1, mxREAL);
//    m_angleRightShank =  mxCreateDoubleMatrix(3, 1, mxREAL);
//    m_angleLeftShank =  mxCreateDoubleMatrix(3, 1, mxREAL);
//    m_gyroRightFoot =  mxCreateDoubleMatrix(3, 1, mxREAL);
//    m_gyroLeftFoot =  mxCreateDoubleMatrix(3, 1, mxREAL);


    m_rightThighArray = mxCreateDoubleMatrix(1, 2, mxREAL);
    m_rightShankArray = mxCreateDoubleMatrix(1, 2, mxREAL);
    m_leftShankArray = mxCreateDoubleMatrix(1, 2, mxREAL);
    m_rightFootArray = mxCreateDoubleMatrix(1, 2, mxREAL);
    m_leftFootArray = mxCreateDoubleMatrix(1, 2, mxREAL);
    m_time = mxCreateDoubleMatrix(1, 2, mxREAL);

    engPutVariable(m_engine, "rightThighArray", m_rightThighArray);
    engPutVariable(m_engine, "rightShankArray", m_rightShankArray);
    engPutVariable(m_engine, "leftShankArray", m_leftShankArray);
    engPutVariable(m_engine, "rightFootArray", m_rightFootArray);
    engPutVariable(m_engine, "leftFootArray", m_leftFootArray);
    engPutVariable(m_engine, "time", m_time);
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
//    bool sensorConnected_hasData = lpms_LT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LT->hasImuData() &&
//            lpms_RS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RS->hasImuData() &&
//            lpms_RT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RT->hasImuData() &&
//            lpms_LS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LS->hasImuData() &&
//            lpms_waist->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_waist->hasImuData() &&
//            lpms_RF->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RF->hasImuData() &&
//            lpms_LF->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LF->hasImuData();

//    if (sensorConnected_hasData)
//    {
        //imudata.r[0] = roll(bank)
        //imudata.r[1] = pitch(alttitude)
        //imudata.r[2] = yaw(heading)

        this->lpms_LT->getQuaternion(this->quaternionLT);
        this->lpms_RT->getQuaternion(this->quaternionRT);
        this->lpms_LS->getQuaternion(this->quaternionLS);
        this->lpms_RS->getQuaternion(this->quaternionRS);
        this->lpms_waist->getQuaternion(this->quaternionWaist);

        d_waist = lpms_waist->getCurrentData();
        d_leftThigh = lpms_LT->getCurrentData();
        d_leftShank = lpms_LS->getCurrentData();
        d_rightThigh = lpms_RT->getCurrentData();
        d_rightShank = lpms_RT->getCurrentData();
        d_leftFoot = lpms_LF->getCurrentData();
        d_rightFoot = lpms_RF->getCurrentData();

        angle_rightThigh[0] = d_rightThigh.r[0];
        angle_rightThigh[1] = d_rightThigh.r[1];
        angle_rightThigh[2] = d_rightThigh.r[2];

        angle_rightShank[0] = d_rightShank.r[0];
        angle_rightShank[1] = d_rightShank.r[1];
        angle_rightShank[2] = d_rightShank.r[2];

        angle_leftShank[0] = d_leftShank.r[0];
        angle_leftShank[1] = d_leftShank.r[1];
        angle_leftShank[2] = d_leftShank.r[2];

        gyro_leftFoot[0] = d_leftFoot.w[0];
        gyro_leftFoot[1] = d_leftFoot.w[1];
        gyro_leftFoot[2] = d_leftFoot.w[2];

        gyro_rightFoot[0] = d_rightFoot.w[0];
        gyro_rightFoot[1] = d_rightFoot.w[1];
        gyro_rightFoot[2] = d_rightFoot.w[2];

        this->time_e.push_back(d_waist.timeStamp);

        m_timestamp = mxCreateDoubleScalar(time_e.last());

        sendAngularDataToMatlab();
        //sendQuaternionDataToMatlab();
        //motionCaptureAnimation();
//    }


    if(time_e.size() % 50 == 0){
        this->updateGraph_quaternion(time_q, xq_LT, xq_LS, xq_RT, xq_RS, xq_Waist);
        if(time_e.size() % 6000 == 0)
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

void MainWindow::initHumanSkeletonModel()
{
    //*********
    //initialize human joint data(17x3 array)
    //In the following order
    //waist, hip_left, hip_right, knee_left, knee_right, ankle_left, ankle_right
    //heel_left, Toe_left, Ankle_right, Heel_right, Toe_right, Shoulder_left,
    //Shoulder_right, elbow_left, elbow_right, Hand_left, Hand_right
    //initialize human limb data
    //In following order
    //lowerBack_left, lowerBack_right, upperChest_left, upperChest_right, shoulder_line
    //hip_line, thigh_left, thigh_right, shank_left, shank_right, foot_left, foot_right
    //flatFoot_right, flatFoot_left, footBack_left, footBack_right, upperArm_left, upperArm_right
    //forarm_left, forarm_right
    //(2x3x20 array)
    //*********

     m_engine = engOpen("null");

    humanJoint = new double*[17];
    for (int i = 0; i < 17; i++){
        humanJoint[i] = new double[3];
    }

    humanJoint[0][0] = 0; humanJoint[0][1] = 0; humanJoint[0][2] = 116.7;   //waist
    humanJoint[1][0] = -7; humanJoint[1][1] = 0; humanJoint[1][2] = 100.4;  //hip_left
    humanJoint[2][0] = 7; humanJoint[2][1] = 0; humanJoint[2][2] = 100.4;   //hip_right
    humanJoint[3][0] = -7; humanJoint[3][1] = 0; humanJoint[3][2] = 54.4;   //knee_left
    humanJoint[4][0] = 7; humanJoint[4][1] = 0; humanJoint[4][2] = 54.4;    //knee_right
    humanJoint[5][0] = -7; humanJoint[5][1] = 0; humanJoint[5][2] = 9.4;    //ankle_left
    humanJoint[6][0] = -7; humanJoint[6][1] = 0; humanJoint[6][2] = 0;      //heel_left
    humanJoint[7][0] = -7; humanJoint[7][1] = -29; humanJoint[7][2] = 0;    //toe_left
    humanJoint[8][0] = 7; humanJoint[8][1] = 0; humanJoint[8][2] = 9.4;     //ankle_right
    humanJoint[9][0] = 7; humanJoint[9][1] = 0; humanJoint[9][2] = 0;       //heel_right
    humanJoint[10][0] = 7; humanJoint[10][1] = -29; humanJoint[10][2] = 0;  //toe_right
    humanJoint[11][0] = -20; humanJoint[11][1] = 0; humanJoint[11][2] = 149.2;  //shoulder_left
    humanJoint[12][0] = 20; humanJoint[12][1] = 0; humanJoint[12][2] = 149.2;   //shoulder_right
    humanJoint[13][0] = -20; humanJoint[13][1] = 0; humanJoint[13][2] = 119;    //elbow_left
    humanJoint[14][0] = 20; humanJoint[14][1] = 0; humanJoint[14][2] = 119;     //elboe_right
    humanJoint[15][0] = -20; humanJoint[15][1] = -26.9; humanJoint[15][2] = 119;    //hand_left
    humanJoint[16][0] = 20; humanJoint[16][1] = -26.9; humanJoint[16][2] = 119;     //hand_right

    lowerBack_left = new double*[2];
    lowerBack_right = new double*[2];
    upperChest_left = new double*[2];
    upperChest_right = new double*[2];
    shoulder_line = new double*[2];
    hip_line = new double*[2];
    thigh_left = new double*[2];
    thigh_right = new double*[2];
    shank_left = new double*[2];
    shank_right = new double*[2];
    foot_left = new double*[2];
    foot_right = new double*[2];
    flatFoot_left = new double*[2];
    flatFoot_right = new double*[2];
    footBack_left = new double*[2];
    footBack_right = new double*[2];
    upperArm_left = new double*[2];
    upperArm_right = new double*[2];
    forarm_left = new double*[2];
    forarm_right = new double*[2];

    for(int i = 0; i < 2; i++){
        lowerBack_left[i] = new double[3];
        lowerBack_right[i] = new double[3];
        upperChest_left[i] = new double[3];
        upperChest_right[i] = new double[3];
        shoulder_line[i] = new double[3];
        hip_line[i] = new double[3];
        thigh_left[i] = new double[3];
        thigh_right[i] = new double[3];
        shank_left[i] = new double[3];
        shank_right[i] = new double[3];
        foot_left[i] = new double[3];
        foot_right[i] = new double[3];
        flatFoot_left[i] = new double[3];
        flatFoot_right[i] = new double[3];
        footBack_left[i] = new double[3];
        footBack_right[i] = new double[3];
        upperArm_left[i] = new double[3];
        upperArm_right[i] = new double[3];
        forarm_left[i] = new double[3];
        forarm_right[i] = new double[3];
    }


    //human limb definition
    //lowerBack_left(0, 1)
    lowerBack_left[0][0] = humanJoint[0][0]; lowerBack_left[0][1] = humanJoint[0][1]; lowerBack_left[0][2] = humanJoint[0][2];
    lowerBack_left[1][0] = humanJoint[1][0]; lowerBack_left[1][1] = humanJoint[1][1]; lowerBack_left[1][2] = humanJoint[1][2];
    mxArray *m_lowerBack_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_lowerBack_left) + i*3), (void *)lowerBack_left[i], 3*sizeof(double));
    }
    //lowerBack_right(0, 2)
    lowerBack_right[0][0] = humanJoint[0][0]; lowerBack_right[0][1] = humanJoint[0][1]; lowerBack_right[0][2] = humanJoint[0][2];
    lowerBack_right[1][0] = humanJoint[2][0]; lowerBack_right[1][1] = humanJoint[2][1]; lowerBack_right[1][2] = humanJoint[2][2];
    mxArray *m_lowerBack_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_lowerBack_right) + i*3), (void *)lowerBack_right[i], 3*sizeof(double));
    }
    //upperChest_left(0, 11)
    upperChest_left[0][0] = humanJoint[0][0]; upperChest_left[0][1] = humanJoint[0][1]; upperChest_left[0][2] = humanJoint[0][2];
    upperChest_left[1][0] = humanJoint[11][0]; upperChest_left[1][1] = humanJoint[11][1]; upperChest_left[1][2] = humanJoint[11][2];
    mxArray *m_upperChest_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_upperChest_left) + i*3), (void *)upperChest_left[i], 3*sizeof(double));
    }
    //upperChest_right(0, 12)
    upperChest_right[0][0] = humanJoint[0][0]; upperChest_right[0][1] = humanJoint[0][1]; upperChest_right[0][2] = humanJoint[0][2];
    upperChest_right[1][0] = humanJoint[12][0]; upperChest_right[1][1] = humanJoint[12][1]; upperChest_right[1][2] = humanJoint[12][2];
    mxArray *m_upperChest_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_upperChest_right) + i*3), (void *)upperChest_right[i], 3*sizeof(double));
    }
    //shoulder_line(11, 12)
    shoulder_line[0][0] = humanJoint[11][0]; shoulder_line[0][1] = humanJoint[11][1]; shoulder_line[0][2] = humanJoint[11][2];
    shoulder_line[1][0] = humanJoint[12][0]; shoulder_line[1][1] = humanJoint[12][1]; shoulder_line[1][2] = humanJoint[12][2];\
    mxArray *m_shoulder_line = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_shoulder_line) + i*3), (void *)shoulder_line[i], 3*sizeof(double));
    }
    //hip_line(1, 2)
    hip_line[0][0] = humanJoint[1][0]; hip_line[0][1] = humanJoint[1][1]; hip_line[0][2] = humanJoint[1][2];
    hip_line[1][0] = humanJoint[2][0]; hip_line[1][1] = humanJoint[2][1]; hip_line[1][2] = humanJoint[2][2];
    mxArray *m_hip_line = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_hip_line) + i*3), (void *)hip_line[i], 3*sizeof(double));
    }
    //thigh_left(1, 3)
    thigh_left[0][0] = humanJoint[1][0]; thigh_left[0][1] = humanJoint[1][1]; thigh_left[0][2] = humanJoint[1][2];
    thigh_left[1][0] = humanJoint[3][0]; thigh_left[1][1] = humanJoint[3][1]; thigh_left[1][2] = humanJoint[3][2];
    mxArray *m_thigh_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_thigh_left) + i*3), (void *)thigh_left[i], 3*sizeof(double));
    }
    //thigh_right(2, 4)
    thigh_right[0][0] = humanJoint[2][0]; thigh_right[0][1] = humanJoint[2][1]; thigh_right[0][2] = humanJoint[2][2];
    thigh_right[1][0] = humanJoint[4][0]; thigh_right[1][1] = humanJoint[4][1]; thigh_right[1][2] = humanJoint[4][2];
    mxArray *m_thigh_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_thigh_right) + i*3), (void *)thigh_right[i], 3*sizeof(double));
    }
    //shank_left(3, 5)
    shank_left[0][0] = humanJoint[3][0]; shank_left[0][1] = humanJoint[3][1]; shank_left[0][2] = humanJoint[3][2];
    shank_left[1][0] = humanJoint[5][0]; shank_left[1][1] = humanJoint[5][1]; shank_left[1][2] = humanJoint[5][2];
    mxArray *m_shank_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_shank_left) + i*3), (void *)shank_left[i], 3*sizeof(double));
    }
    //shank_right(4, 8)
    shank_right[0][0] = humanJoint[4][0]; shank_right[0][1] = humanJoint[4][1]; shank_right[0][2] = humanJoint[4][2];
    shank_right[1][0] = humanJoint[8][0]; shank_right[1][1] = humanJoint[8][1]; shank_right[1][2] = humanJoint[8][2];
    mxArray *m_shank_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_shank_right) + i*3), (void *)shank_right[i], 3*sizeof(double));
    }
    //foot_left(5, 6)
    foot_left[0][0] = humanJoint[5][0]; foot_left[0][1] = humanJoint[5][1]; foot_left[0][2] = humanJoint[5][2];
    foot_left[1][0] = humanJoint[6][0]; foot_left[1][1] = humanJoint[6][1]; foot_left[1][2] = humanJoint[6][2];
    mxArray *m_foot_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_foot_left) + i*3), (void *)foot_left[i], 3*sizeof(double));
    }
    //foot_right(8, 9)
    foot_right[0][0] = humanJoint[8][0]; foot_right[0][1] = humanJoint[8][1]; foot_right[0][2] = humanJoint[8][2];
    foot_right[1][0] = humanJoint[9][0]; foot_right[1][1] = humanJoint[9][1]; foot_right[1][2] = humanJoint[9][2];
    mxArray *m_foot_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_foot_right) + i*3), (void *)foot_right[i], 3*sizeof(double));
    }
    //flatFoot_left(6, 7)
    flatFoot_left[0][0] = humanJoint[6][0]; flatFoot_left[0][1] = humanJoint[6][1]; flatFoot_left[0][2] = humanJoint[6][2];
    flatFoot_left[1][0] = humanJoint[7][0]; flatFoot_left[1][1] = humanJoint[7][1]; flatFoot_left[1][2] = humanJoint[7][2];
    mxArray *m_flatFoot_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_flatFoot_left) + i*3), (void *)flatFoot_left[i], 3*sizeof(double));
    }
    //flatFoot_right(9, 10)
    flatFoot_right[0][0] = humanJoint[9][0]; flatFoot_right[0][1] = humanJoint[9][1]; flatFoot_right[0][2] = humanJoint[9][2];
    flatFoot_right[1][0] = humanJoint[10][0]; flatFoot_right[1][1] = humanJoint[10][1]; flatFoot_right[1][2] = humanJoint[10][2];
    mxArray *m_flatFoot_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_flatFoot_right) + i*3), (void *)flatFoot_right[i], 3*sizeof(double));
    }
    //footBack_left(7, 5)
    footBack_left[0][0] = humanJoint[5][0]; footBack_left[0][1] = humanJoint[5][1]; footBack_left[0][2] = humanJoint[5][2];
    footBack_left[1][0] = humanJoint[7][0]; footBack_left[1][1] = humanJoint[7][1]; footBack_left[1][2] = humanJoint[7][2];
    mxArray *m_footBack_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_footBack_left) + i*3), (void *)footBack_left[i], 3*sizeof(double));
    }
    //footBack_right(10, 8)
    footBack_right[0][0] = humanJoint[8][0]; footBack_right[0][1] = humanJoint[8][1]; footBack_right[0][2] = humanJoint[8][2];
    footBack_right[1][0] = humanJoint[10][0]; footBack_right[1][1] = humanJoint[10][1]; footBack_right[1][2] = humanJoint[10][2];
    mxArray *m_footBack_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_footBack_right) + i*3), (void *)footBack_right[i], 3*sizeof(double));
    }
    //upperarm_left(11, 13)
    upperArm_left[0][0] = humanJoint[11][0]; upperArm_left[0][1] = humanJoint[11][1]; upperArm_left[0][2] = humanJoint[11][2];
    upperArm_left[1][0] = humanJoint[13][0]; upperArm_left[1][1] = humanJoint[13][1]; upperArm_left[1][2] = humanJoint[13][2];
    mxArray *m_upperArm_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_upperArm_left) + i*3), (void *)upperArm_left[i], 3*sizeof(double));
    }
    //upperarm_right(12, 14)
    upperArm_right[0][0] = humanJoint[12][0]; upperArm_right[0][1] = humanJoint[12][1]; upperArm_right[0][2] = humanJoint[12][2];
    upperArm_right[1][0] = humanJoint[14][0]; upperArm_right[1][1] = humanJoint[14][1]; upperArm_right[1][2] = humanJoint[14][2];
    mxArray *m_upperArm_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)( mxGetPr(m_upperArm_right) + i*3), (void *)upperArm_right[i], 3*sizeof(double));
    }
    //forarm_left(13, 15)
    forarm_left[0][0] = humanJoint[13][0]; forarm_left[0][1] = humanJoint[13][1]; forarm_left[0][2] = humanJoint[13][2];
    forarm_left[1][0] = humanJoint[15][0]; forarm_left[1][1] = humanJoint[15][1]; forarm_left[1][2] = humanJoint[15][2];
    mxArray *m_forarm_left = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_forarm_left) + i*3), (void *)forarm_left[i], 3*sizeof(double));
    }
    //forarm_right(14, 16)
    forarm_right[0][0] = humanJoint[14][0]; forarm_right[0][1] = humanJoint[14][1]; forarm_right[0][2] = humanJoint[14][2];
    forarm_right[1][0] = humanJoint[16][0]; forarm_right[1][1] = humanJoint[16][1]; forarm_right[1][2] = humanJoint[16][2];
    mxArray *m_forarm_right = mxCreateDoubleMatrix(2, 3, mxREAL);\
    for (int i = 0; i < 2; i++){
        memcpy((void *)(mxGetPr(m_forarm_right) + i*3), (void *)forarm_right[i], 3*sizeof(double));
    }

    mxArray *m_humanJoint = mxCreateDoubleMatrix(17, 3, mxREAL);
    double* ptr_m_humanJoint = mxGetPr(m_humanJoint);
    for ( int i = 0; i < 17; i++){
        memcpy((void *)(ptr_m_humanJoint + i*3), (void *)humanJoint[i], 3*sizeof(double));
    }

    //put variable in Qt to Matlab


    engPutVariable(m_engine, "HumanJoint", m_humanJoint);

    engPutVariable(m_engine, "lowerBack_left", m_lowerBack_left);
    engPutVariable(m_engine, "lowerBack_right", m_lowerBack_right);
    engPutVariable(m_engine, "upperChest_left", m_upperChest_left);
    engPutVariable(m_engine, "upperChest_right", m_upperChest_right);
    engPutVariable(m_engine, "shoulder_line", m_shoulder_line);
    engPutVariable(m_engine, "hip_line", m_hip_line);
    engPutVariable(m_engine, "thigh_left", m_thigh_left);
    engPutVariable(m_engine, "thigh_right", m_thigh_right);
    engPutVariable(m_engine, "shank_left", m_shank_left);
    engPutVariable(m_engine, "shank_right", m_shank_right);
    engPutVariable(m_engine, "foot_left", m_foot_left);
    engPutVariable(m_engine, "foot_right", m_foot_right);
    engPutVariable(m_engine, "flatFoot_left", m_flatFoot_left);
    engPutVariable(m_engine, "flatFoot_right", m_flatFoot_right);
    engPutVariable(m_engine, "footBack_left", m_footBack_left);
    engPutVariable(m_engine, "footBack_right", m_footBack_right);
    engPutVariable(m_engine, "upperArm_left", m_upperArm_left);
    engPutVariable(m_engine, "upperArm_right", m_upperArm_right);
    engPutVariable(m_engine, "forarm_left", m_forarm_left);
    engPutVariable(m_engine, "forarm_right", m_forarm_right);

    //permute and reshape wrong data dimension
    //exchange two columns
    engEvalString(m_engine, "HumanJoint = permute(reshape(HumanJoint, [3, 17]), [2 1])");
    engEvalString(m_engine, "lowerBack_left(1, [2 3]) = lowerBack_left(1, [3 2])");
    engEvalString(m_engine, "lowerBack_left(2, [1 2]) = lowerBack_left(2, [2 1])");
    engEvalString(m_engine, "lowerBack_right(1, [2 3]) = lowerBack_right(1, [3 2])");
    engEvalString(m_engine, "lowerBack_right(2, [1 2]) = lowerBack_right(2, [2 1])");
    engEvalString(m_engine, "upperChest_left(1, [2 3]) = upperChest_left(1, [3 2])");
    engEvalString(m_engine, "upperChest_left(2, [1 2]) = upperChest_left(2, [2 1])");
    engEvalString(m_engine, "upperChest_right(1, [2 3]) = upperChest_right(1, [3 2])");
    engEvalString(m_engine, "upperChest_right(2, [1 2]) = upperChest_right(2, [2 1])");
    engEvalString(m_engine, "shoulder_line(1, [2 3]) = shoulder_line(1, [3 2])");
    engEvalString(m_engine, "shoulder_line(2, [1 2]) = shoulder_line(2, [2 1])");
    engEvalString(m_engine, "hip_line(1, [2 3]) = hip_line(1, [3 2])");
    engEvalString(m_engine, "hip_line(2, [1 2]) = hip_line(2, [2 1])");
    engEvalString(m_engine, "thigh_left(1, [2 3]) = thigh_left(1, [3 2])");
    engEvalString(m_engine, "thigh_left(2, [1 2]) = thigh_left(2, [2 1])");
    engEvalString(m_engine, "thigh_right(1, [2 3]) = thigh_right(1, [3 2])");
    engEvalString(m_engine, "thigh_right(2, [1 2]) = thigh_right(2, [2 1])");
    engEvalString(m_engine, "shank_left(1, [2 3]) = shank_left(1, [3 2])");
    engEvalString(m_engine, "shank_left(2, [1 2]) = shank_left(2, [2 1])");
    engEvalString(m_engine, "shank_right(1, [2 3]) = shank_right(1, [3 2])");
    engEvalString(m_engine, "shank_right(2, [1 2]) = shank_right(2, [2 1])");
    engEvalString(m_engine, "foot_left(1, [2 3]) = foot_left(1, [3 2])");
    engEvalString(m_engine, "foot_left(2, [1 2]) = foot_left(2, [2 1])");
    engEvalString(m_engine, "foot_right(1, [2 3]) = foot_right(1, [3 2])");
    engEvalString(m_engine, "foot_right(2, [1 2]) = foot_right(2, [2 1])");
    engEvalString(m_engine, "flatFoot_left(1, [2 3]) = flatFoot_left(1, [3 2])");
    engEvalString(m_engine, "flatFoot_left(2, [1 2]) = flatFoot_left(2, [2 1])");
    engEvalString(m_engine, "flatFoot_right(1, [2 3]) = flatFoot_right(1, [3 2])");
    engEvalString(m_engine, "flatFoot_right(2, [1 2]) = flatFoot_right(2, [2 1])");
    engEvalString(m_engine, "footBack_left(1, [2 3]) = footBack_left(1, [3 2])");
    engEvalString(m_engine, "footBack_left(2, [1 2]) = footBack_left(2, [2 1])");
    engEvalString(m_engine, "footBack_left([1 2], 3) = footBack_left([2 1], 3)");
    engEvalString(m_engine, "footBack_right(1, [2 3]) = footBack_right(1, [3 2])");
    engEvalString(m_engine, "footBack_right(2, [1 2]) = footBack_right(2, [2 1])");
    engEvalString(m_engine, "footBack_right([1 2], 3) = footBack_right([2 1], 3)");
    engEvalString(m_engine, "upperArm_left(1, [2 3]) = upperArm_left(1, [3 2])");
    engEvalString(m_engine, "upperArm_left(2, [1 2]) = upperArm_left(2, [2 1])");
    engEvalString(m_engine, "upperArm_right(1, [2 3]) = upperArm_right(1, [3 2])");
    engEvalString(m_engine, "upperArm_right(2, [1 2]) = upperArm_right(2, [2 1])");
    engEvalString(m_engine, "forarm_left(1, [2 3]) = forarm_left(1, [3 2])");
    engEvalString(m_engine, "forarm_left(2, [1 2]) = forarm_left(2, [2 1])");
    engEvalString(m_engine, "forarm_right(1, [2 3]) = forarm_right(1, [3 2])");
    engEvalString(m_engine, "forarm_right(2, [1 2]) = forarm_right(2, [2 1])");

}

//plot the human skeleton model on Matlab
void MainWindow::motionCaptureAnimation()
{
    //calculate limb vector
    engEvalString(m_engine, "v_leftThigh = HumanJoint(2, :) - waist(1, :)");
    engEvalString(m_engine, "v_rightThigh = HumanJoint(3, :) - waist(1, :)");
    engEvalString(m_engine, "v_leftShank = HumanJoint(4, :) - HumanJoint(2, :)");
    engEvalString(m_engine, "v_rightShank = HumanJoint(5, :) - HumanJoint(2, :)");
    engEvalString(m_engine, "v_leftFoot = HumanJoint(7, :) - HumanJoint(6, :)");
    engEvalString(m_engine, "v_rightFoot = HumanJoint(9, :) - HumanJoint(10, :)");
    engEvalString(m_engine, "v_leftFlatFoot = HumanJoint(7, :) - HumanJoint(8, :)");
    engEvalString(m_engine, "v_rightFlatFoot = HumanJoint(10, :) - HumanJoint(11, :)");
    engEvalString(m_engine, "v_leftFootBack = HumanJoint(8, :) - HumanJoint(6, :)");
    engEvalString(m_engine, "v_rightFootBack = HumanJoint(9, :) - HumanJoint(11, :)");
    engEvalString(m_engine, "v_leftThigh = quatrotate(reshape(quaternionLeftThigh, [1 4]), v_leftThigh)");
    engEvalString(m_engine, "v_rightThigh = quatrotate(reshape(quaternionRightThigh, [1 4]), v_rightThigh)");
    engEvalString(m_engine, "v_leftShank = quatrotate(reshape(quaternionLeftShank, [1 4]), v_leftShank)");
    engEvalString(m_engine, "v_rightShank = quatrotate(reshape(quaternionRightShank, [1 4]), v_rightShank)");
    //update new joint coordinate
    engEvalString(m_engine, "HumanJoint(4, :) = HumanJoint(2, :) + v_leftThigh");
    engEvalString(m_engine, "HumanJoint(5, :) = HumanJoint(3, :) + v_rightThigh");
    engEvalString(m_engine, "HumanJoint(6, :) = HumanJoint(4, :) + v_leftShank");
    engEvalString(m_engine, "HumanJoint(9, :) = HumanJoint(5, :) + v_rightShank");
    engEvalString(m_engine, "HumanJoint(7, :) = HumanJoint(6, :) + v_leftFoot");
    engEvalString(m_engine, "HumanJoint(8, :) = HumanJoint(7, :) + v_leftFootFlat");
    engEvalString(m_engine, "HumanJoint(10, :) = HumanJoint(9, :) + v_rightFoot");
    engEvalString(m_engine, "HumanJoint(11, :) = HumanJoint(10, :) + v_rightFlatFoot");


//    engEvalString(m_engine, "figure('unit','normalized','outerposition',[0 0 1 1]),");
    engEvalString(m_engine, "plot3(HumanJoint(:, 1), HumanJoint(:, 2), HumanJoint(:, 3), 'r.', 'markers', 20), grid minor, title(' Human Joint Coordinate '),");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(lowerBack_left(:, 1), lowerBack_left(:, 2), lowerBack_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(lowerBack_right(:, 1), lowerBack_right(:, 2), lowerBack_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(upperChest_left(:, 1), upperChest_left(:, 2), upperChest_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(upperChest_right(:, 1), upperChest_right(:, 2), upperChest_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(shoulder_line(:, 1), shoulder_line(:, 2), shoulder_line(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(hip_line(:, 1), hip_line(:, 2), hip_line(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(thigh_left(:, 1), thigh_left(:, 2), thigh_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(thigh_right(:, 1), thigh_right(:, 2), thigh_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(shank_left(:, 1), shank_left(:, 2), shank_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(shank_right(:, 1), shank_right(:, 2), shank_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(foot_left(:, 1), foot_left(:, 2), foot_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(foot_right(:, 1), foot_right(:, 2), foot_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(flatFoot_left(:, 1), flatFoot_left(:, 2), flatFoot_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(flatFoot_right(:, 1), flatFoot_right(:, 2), flatFoot_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(footBack_left(:, 1), footBack_left(:, 2), footBack_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(footBack_right(:, 1), footBack_right(:, 2), footBack_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(upperArm_left(:, 1), upperArm_left(:, 2), upperArm_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(upperArm_right(:, 1), upperArm_right(:, 2), upperArm_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(forarm_left(:, 1), forarm_left(:, 2), forarm_left(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold on;");
    engEvalString(m_engine, "plot3(forarm_right(:, 1), forarm_right(:, 2), forarm_right(:, 3), 'lineWidth', 2);");
    engEvalString(m_engine, "hold off;");
    engEvalString(m_engine, "set(gca, 'DataAspectRatio', [2 6 3])");
}

void MainWindow::sendQuaternionDataToMatlab()
{
    mxArray* m_quaternionLT = mxCreateDoubleMatrix(4, 1, mxREAL);
    mxArray* m_quaternionRT = mxCreateDoubleMatrix(4, 1, mxREAL);
    mxArray* m_quaternionLS = mxCreateDoubleMatrix(4, 1, mxREAL);
    mxArray* m_quaternionRS = mxCreateDoubleMatrix(4, 1, mxREAL);

    memcpy((void *)mxGetPr(m_quaternionLT), (void *)quaternionLT, sizeof(double)*4);
    memcpy((void *)mxGetPr(m_quaternionRT), (void *)quaternionLT, sizeof(double)*4);
    memcpy((void *)mxGetPr(m_quaternionLS), (void *)quaternionLT, sizeof(double)*4);
    memcpy((void *)mxGetPr(m_quaternionRS), (void *)quaternionLT, sizeof(double)*4);

    engPutVariable(m_engine, "quaternionLeftThigh", m_quaternionLT);
    engPutVariable(m_engine, "quaternionRightThigh", m_quaternionRT);
    engPutVariable(m_engine, "quaternionLeftShank", m_quaternionLS);
    engPutVariable(m_engine, "quaternionRightShank", m_quaternionRS);
}

void MainWindow::sendAngularDataToMatlab()
{
    memcpy((void *)mxGetPr(this->m_angleRightThigh), (void *)angle_rightThigh, sizeof(double)*3);
    memcpy((void *)mxGetPr(this->m_angleRightShank), (void *)angle_rightShank, sizeof(double)*3);
    memcpy((void *)mxGetPr(this->m_angleLeftShank), (void *)angle_leftShank, sizeof(double)*3);
    memcpy((void *)mxGetPr(this->m_gyroLeftFoot), (void *)angle_leftShank, sizeof(double)*3);
    memcpy((void *)mxGetPr(this->m_gyroRightFoot), (void *)gyro_rightFoot, sizeof(double)*3);

    m_angleRightThigh = mxCreateDoubleScalar(angle_rightThigh[0]);
    m_angleRightShank = mxCreateDoubleScalar(angle_rightShank[0]);
    m_angleLeftShank = mxCreateDoubleScalar(angle_leftShank[0]);
    m_gyroLeftFoot = mxCreateDoubleScalar(gyro_leftFoot[0]);
    m_gyroRightFoot = mxCreateDoubleScalar(gyro_rightFoot[0]);

    engPutVariable(m_engine, "append_angleRightThigh", m_angleRightThigh);
    engPutVariable(m_engine, "append_angleRightShank", m_angleRightShank);
    engPutVariable(m_engine, "append_angleLeftShank", m_angleLeftShank);
    engPutVariable(m_engine, "append_gyroLeftFoot", m_gyroLeftFoot);
    engPutVariable(m_engine, "append_gyroRightFoot", m_gyroRightFoot);
    engPutVariable(m_engine, "append_time", m_timestamp);

    engEvalString(m_engine, "rightThighArray = [rightThighArray append_angleRightThigh']");
    engEvalString(m_engine, "rightShankArray = [rightShankArray append_angleRightShank']");
    engEvalString(m_engine, "rightFootArray = [rightFootArray append_gyroRightFoot']");
    engEvalString(m_engine, "leftShankArray = [leftShankArray append_angleLeftShank']");
    engEvalString(m_engine, "leftFootArray = [leftFootArray append_gyroLeftFoot']");
    engEvalString(m_engine, "time = [time append_time]");

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

    //set legend name
    ui->leftThigh->graph(0)->setName("Quaternion");
    ui->leftShank->graph(0)->setName("Quaternion");
    ui->rightThigh->graph(0)->setName("Quaternion");
    ui->rightShank->graph(0)->setName("Quaternion");
    ui->trunk->graph(0)->setName("Quaternion");

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

//void MainWindow::updateGraph_euler(QVector<double> time, QVector<double> leftThigh, QVector<double> rightThigh, QVector<double> leftShank, QVector<double> rightShank, QVector<double> trunk)
//{
//    //set line color
//    ui->leftThigh->graph(1)->setPen(QPen(Qt::red));
//    ui->leftShank->graph(1)->setPen(QPen(Qt::red));
//    ui->rightThigh->graph(1)->setPen(QPen(Qt::red));
//    ui->rightShank->graph(1)->setPen(QPen(Qt::red));
//    ui->trunk->graph(1)->setPen(QPen(Qt::red));

//    ui->leftThigh->graph(1)->setData(time, leftThigh);
//    ui->leftShank->graph(1)->setData(time, leftShank);
//    ui->trunk->graph(1)->setData(time, trunk);
//    ui->rightThigh->graph(1)->setData(time, rightThigh);
//    ui->rightShank->graph(1)->setData(time, rightShank);

//    //set legend name
//    ui->leftThigh->graph(1)->setName("Euler angle");
//    ui->leftShank->graph(1)->setName("Euler angle");
//    ui->rightThigh->graph(1)->setName("Euler angle");
//    ui->rightShank->graph(1)->setName("Euler angle");
//    ui->trunk->graph(1)->setName("Euler angle");

//    //give the axes some labels
//    ui->leftShank->xAxis->setLabel("time");
//    ui->leftThigh->xAxis->setLabel("time");
//    ui->trunk->xAxis->setLabel("time");
//    ui->rightThigh->xAxis->setLabel("time");
//    ui->rightShank->xAxis->setLabel("time");

//    //setAxis
//    ui->leftShank->xAxis->setRange(0, 6000);
//    ui->leftShank->yAxis->setRange(-90, 90);
//    ui->trunk->xAxis->setRange(0, 6000);
//    ui->trunk->yAxis->setRange(-90, 90);
//    ui->rightThigh->xAxis->setRange(0, 6000);
//    ui->rightThigh->yAxis->setRange(-90, 90);
//    ui->rightShank->xAxis->setRange(0, 6000);
//    ui->rightShank->yAxis->setRange(-90, 90);
//    ui->leftThigh->xAxis->setRange(0, 6000);
//    ui->leftThigh->yAxis->setRange(-90, 90);

//    ui->leftThigh->replot();
//    ui->leftShank->replot();
//    ui->trunk->replot();
//    ui->rightThigh->replot();
//    ui->rightShank->replot();
//}

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
    lpms_LT = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E1:3E");
//    while(1)
//    {
//        if(lpms_LT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LT->hasImuData())
//        {
//            lpms_LT->setOrientationOffset(0);
//            lpms_LT->saveCalibrationData();
//            ui->textBrowser_status->append("IMU Left Thigh is connected");
//            break;
//        }
//    }

    lpms_RT = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E0:F2");
//    while(1)
//    {
//        if(lpms_RT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RT->hasImuData())
//        {
//            lpms_RT->setOrientationOffset(0);
//            lpms_RT->saveCalibrationData();
//            ui->textBrowser_status->append("IMU Right Thigh is connected");
//            break;
//        }
//    }

    lpms_LS = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E0:ED");
//    while(1)
//    {
//        if(lpms_LS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LS->hasImuData())
//        {
//            lpms_LS->setOrientationOffset(0);
//            lpms_LS->saveCalibrationData();
//            ui->textBrowser_status->append("IMU Left Shank is connected");
//            break;
//        }
//    }

    lpms_RS = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E0:BB");
//    while(1)
//    {
//        if(lpms_RS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RS->hasImuData())
//        {
//            lpms_RS->setOrientationOffset(0);
//            lpms_RS->saveCalibrationData();
//            ui->textBrowser_status->append("IMU Right Shank is connected");
//            break;
//        }
//    }


    lpms_RF = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E1:4B");
//    while(1)
//    {
//        if(lpms_RF->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RF->hasImuData())
//        {
//            lpms_RF->setOrientationOffset(0);
//            lpms_RF->saveCalibrationData();
//            ui->textBrowser_status->append("IMU Right Foot is connected");
//            break;
//        }
//    }

    lpms_LF = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E0:CF");
//    while(1)
//    {
//        if(lpms_LF->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LF->hasImuData())
//        {
//            lpms_LF->setOrientationOffset(0);
//            lpms_LF->saveCalibrationData();
//            ui->textBrowser_status->append("IMU Left Foot is connected");
//            break;
//        }
//    }

    lpms_waist = manager->addSensor(DEVICE_LPMS_B, "00:04:3E:9F:E0:B3");
//    while(1)
//    {
//        if(lpms_waist->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_waist->hasImuData())
//        {
//            lpms_waist->setOrientationOffset(0);
//            lpms_waist->saveCalibrationData();
//            ui->textBrowser_status->append("IMU Waist is connected");
//            break;
//        }
//    }

    bool sensorConnected_hasData = lpms_LT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LT->hasImuData() &&
            lpms_RS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RS->hasImuData() &&
            lpms_RT->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RT->hasImuData() &&
            lpms_LS->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LS->hasImuData() &&
            lpms_waist->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_waist->hasImuData() &&
            lpms_RF->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_RF->hasImuData() &&
            lpms_LF->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED && lpms_LF->hasImuData();

    if (sensorConnected_hasData){
        lpms_LT->setOrientationOffset(0);
        lpms_LT->saveCalibrationData();
        ui->textBrowser_status->append("IMU Left Thigh is connected");
        lpms_RT->setOrientationOffset(0);
        lpms_RT->saveCalibrationData();
        ui->textBrowser_status->append("IMU Right Thigh is connected");
        lpms_LS->setOrientationOffset(0);
        lpms_LS->saveCalibrationData();
        ui->textBrowser_status->append("IMU Left Shank is connected");
        lpms_RS->setOrientationOffset(0);
        lpms_RS->saveCalibrationData();
        ui->textBrowser_status->append("IMU Right Shank is connected");
        lpms_RF->setOrientationOffset(0);
        lpms_RF->saveCalibrationData();
        ui->textBrowser_status->append("IMU Right Foot is connected");
        lpms_LF->setOrientationOffset(0);
        lpms_LF->saveCalibrationData();
        ui->textBrowser_status->append("IMU Left Foot is connected");
        lpms_waist->setOrientationOffset(0);
        lpms_waist->saveCalibrationData();
        ui->textBrowser_status->append("IMU Waist is connected");
        ui->pushButton_newFile->setEnabled(true);
//        m_engine = engOpen("null");
        timer_->start();
    }
}
