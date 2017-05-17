/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDisconnect;
    QAction *actionExit;
    QAction *actionCalibration;
    QAction *actionConnect_Left_Thigh_IMU;
    QAction *actionConnect_Right_Thigh_IMU;
    QAction *actionLeft_Shank_IMU;
    QAction *actionRight_Shank_IMU;
    QAction *actionLeft_Foot_IMU;
    QAction *actionRight_Foot_IMU;
    QAction *actionWaist;
    QWidget *centralWidget;
    QTextBrowser *textBrowser_status;
    QPushButton *pushButton_save_file;
    QPushButton *pushButton_newFile;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QCustomPlot *leftShank;
    QCustomPlot *rightShank;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QCustomPlot *trunk;
    QCustomPlot *leftThigh;
    QCustomPlot *rightThigh;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_trunk;
    QLabel *label_leftThigh;
    QLabel *label_rightThigh;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_leftShank;
    QLabel *label_rightShank;
    QMenuBar *menuBar;
    QMenu *menuCalls;
    QMenu *menuConnect;
    QMenu *menuAction;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1152, 818);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionCalibration = new QAction(MainWindow);
        actionCalibration->setObjectName(QStringLiteral("actionCalibration"));
        actionConnect_Left_Thigh_IMU = new QAction(MainWindow);
        actionConnect_Left_Thigh_IMU->setObjectName(QStringLiteral("actionConnect_Left_Thigh_IMU"));
        actionConnect_Right_Thigh_IMU = new QAction(MainWindow);
        actionConnect_Right_Thigh_IMU->setObjectName(QStringLiteral("actionConnect_Right_Thigh_IMU"));
        actionLeft_Shank_IMU = new QAction(MainWindow);
        actionLeft_Shank_IMU->setObjectName(QStringLiteral("actionLeft_Shank_IMU"));
        actionRight_Shank_IMU = new QAction(MainWindow);
        actionRight_Shank_IMU->setObjectName(QStringLiteral("actionRight_Shank_IMU"));
        actionLeft_Foot_IMU = new QAction(MainWindow);
        actionLeft_Foot_IMU->setObjectName(QStringLiteral("actionLeft_Foot_IMU"));
        actionRight_Foot_IMU = new QAction(MainWindow);
        actionRight_Foot_IMU->setObjectName(QStringLiteral("actionRight_Foot_IMU"));
        actionWaist = new QAction(MainWindow);
        actionWaist->setObjectName(QStringLiteral("actionWaist"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowser_status = new QTextBrowser(centralWidget);
        textBrowser_status->setObjectName(QStringLiteral("textBrowser_status"));
        textBrowser_status->setGeometry(QRect(30, 660, 711, 101));
        pushButton_save_file = new QPushButton(centralWidget);
        pushButton_save_file->setObjectName(QStringLiteral("pushButton_save_file"));
        pushButton_save_file->setGeometry(QRect(750, 520, 341, 130));
        QFont font;
        font.setFamily(QStringLiteral("Ebrima"));
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        pushButton_save_file->setFont(font);
        pushButton_newFile = new QPushButton(centralWidget);
        pushButton_newFile->setObjectName(QStringLiteral("pushButton_newFile"));
        pushButton_newFile->setGeometry(QRect(750, 380, 341, 130));
        pushButton_newFile->setFont(font);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 370, 711, 281));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        leftShank = new QCustomPlot(layoutWidget);
        leftShank->setObjectName(QStringLiteral("leftShank"));

        horizontalLayout_5->addWidget(leftShank);

        rightShank = new QCustomPlot(layoutWidget);
        rightShank->setObjectName(QStringLiteral("rightShank"));

        horizontalLayout_5->addWidget(rightShank);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 50, 1061, 281));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        trunk = new QCustomPlot(layoutWidget1);
        trunk->setObjectName(QStringLiteral("trunk"));

        horizontalLayout->addWidget(trunk);

        leftThigh = new QCustomPlot(layoutWidget1);
        leftThigh->setObjectName(QStringLiteral("leftThigh"));

        horizontalLayout->addWidget(leftThigh);

        rightThigh = new QCustomPlot(layoutWidget1);
        rightThigh->setObjectName(QStringLiteral("rightThigh"));

        horizontalLayout->addWidget(rightThigh);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 18, 1061, 34));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_trunk = new QLabel(layoutWidget2);
        label_trunk->setObjectName(QStringLiteral("label_trunk"));
        QFont font1;
        font1.setFamily(QStringLiteral("Ebrima"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        label_trunk->setFont(font1);

        horizontalLayout_3->addWidget(label_trunk);

        label_leftThigh = new QLabel(layoutWidget2);
        label_leftThigh->setObjectName(QStringLiteral("label_leftThigh"));
        label_leftThigh->setFont(font1);

        horizontalLayout_3->addWidget(label_leftThigh);

        label_rightThigh = new QLabel(layoutWidget2);
        label_rightThigh->setObjectName(QStringLiteral("label_rightThigh"));
        label_rightThigh->setFont(font1);

        horizontalLayout_3->addWidget(label_rightThigh);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(30, 340, 711, 34));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_leftShank = new QLabel(layoutWidget3);
        label_leftShank->setObjectName(QStringLiteral("label_leftShank"));
        label_leftShank->setFont(font1);

        horizontalLayout_2->addWidget(label_leftShank);

        label_rightShank = new QLabel(layoutWidget3);
        label_rightShank->setObjectName(QStringLiteral("label_rightShank"));
        label_rightShank->setFont(font1);

        horizontalLayout_2->addWidget(label_rightShank);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1152, 21));
        menuCalls = new QMenu(menuBar);
        menuCalls->setObjectName(QStringLiteral("menuCalls"));
        menuConnect = new QMenu(menuCalls);
        menuConnect->setObjectName(QStringLiteral("menuConnect"));
        menuAction = new QMenu(menuBar);
        menuAction->setObjectName(QStringLiteral("menuAction"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCalls->menuAction());
        menuBar->addAction(menuAction->menuAction());
        menuCalls->addAction(menuConnect->menuAction());
        menuCalls->addAction(actionDisconnect);
        menuCalls->addSeparator();
        menuCalls->addAction(actionExit);
        menuConnect->addAction(actionConnect_Left_Thigh_IMU);
        menuConnect->addAction(actionConnect_Right_Thigh_IMU);
        menuConnect->addAction(actionLeft_Shank_IMU);
        menuConnect->addAction(actionRight_Shank_IMU);
        menuConnect->addAction(actionLeft_Foot_IMU);
        menuConnect->addAction(actionRight_Foot_IMU);
        menuConnect->addAction(actionWaist);
        menuAction->addAction(actionCalibration);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionCalibration->setText(QApplication::translate("MainWindow", "Calibration", 0));
        actionConnect_Left_Thigh_IMU->setText(QApplication::translate("MainWindow", "Left Thigh IMU", 0));
        actionConnect_Right_Thigh_IMU->setText(QApplication::translate("MainWindow", "Right Thigh IMU", 0));
        actionLeft_Shank_IMU->setText(QApplication::translate("MainWindow", "Left Shank IMU", 0));
        actionRight_Shank_IMU->setText(QApplication::translate("MainWindow", "Right Shank IMU", 0));
        actionLeft_Foot_IMU->setText(QApplication::translate("MainWindow", "Left Foot IMU", 0));
        actionRight_Foot_IMU->setText(QApplication::translate("MainWindow", "Right Foot IMU", 0));
        actionWaist->setText(QApplication::translate("MainWindow", "Waist", 0));
        pushButton_save_file->setText(QApplication::translate("MainWindow", "Save Record File", 0));
        pushButton_newFile->setText(QApplication::translate("MainWindow", "New Recored File", 0));
        label_trunk->setText(QApplication::translate("MainWindow", "Trunk", 0));
        label_leftThigh->setText(QApplication::translate("MainWindow", "Left Thigh", 0));
        label_rightThigh->setText(QApplication::translate("MainWindow", "Right Thigh", 0));
        label_leftShank->setText(QApplication::translate("MainWindow", "Left Shank", 0));
        label_rightShank->setText(QApplication::translate("MainWindow", "Right Shank", 0));
        menuCalls->setTitle(QApplication::translate("MainWindow", "Calls", 0));
        menuConnect->setTitle(QApplication::translate("MainWindow", "Connect", 0));
        menuAction->setTitle(QApplication::translate("MainWindow", "Action", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
