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
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionExit;
    QWidget *centralWidget;
    QTextBrowser *textBrowser_status;
    QPushButton *pushButton_save_file;
    QPushButton *pushButton_newFile;
    QLabel *label_leftShank;
    QLabel *label_rightShank;
    QCustomPlot *trunk;
    QLabel *label_trunk;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_4;
    QCustomPlot *leftThigh;
    QCustomPlot *rightThigh;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_5;
    QCustomPlot *leftShank;
    QCustomPlot *rightShank;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_leftThigh;
    QLabel *label_rightThigh;
    QMenuBar *menuBar;
    QMenu *menuCalls;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1152, 800);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowser_status = new QTextBrowser(centralWidget);
        textBrowser_status->setObjectName(QStringLiteral("textBrowser_status"));
        textBrowser_status->setGeometry(QRect(20, 630, 681, 101));
        pushButton_save_file = new QPushButton(centralWidget);
        pushButton_save_file->setObjectName(QStringLiteral("pushButton_save_file"));
        pushButton_save_file->setGeometry(QRect(250, 510, 211, 101));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(18);
        pushButton_save_file->setFont(font);
        pushButton_newFile = new QPushButton(centralWidget);
        pushButton_newFile->setObjectName(QStringLiteral("pushButton_newFile"));
        pushButton_newFile->setGeometry(QRect(20, 510, 211, 101));
        pushButton_newFile->setFont(font);
        label_leftShank = new QLabel(centralWidget);
        label_leftShank->setObjectName(QStringLiteral("label_leftShank"));
        label_leftShank->setGeometry(QRect(722, 450, 202, 27));
        label_leftShank->setFont(font);
        label_rightShank = new QLabel(centralWidget);
        label_rightShank->setObjectName(QStringLiteral("label_rightShank"));
        label_rightShank->setGeometry(QRect(930, 450, 201, 27));
        label_rightShank->setFont(font);
        trunk = new QCustomPlot(centralWidget);
        trunk->setObjectName(QStringLiteral("trunk"));
        trunk->setGeometry(QRect(810, 90, 221, 161));
        label_trunk = new QLabel(centralWidget);
        label_trunk->setObjectName(QStringLiteral("label_trunk"));
        label_trunk->setGeometry(QRect(810, 50, 221, 27));
        label_trunk->setFont(font);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(710, 450, 411, 29));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(710, 290, 411, 151));
        horizontalLayout_4 = new QHBoxLayout(widget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        leftThigh = new QCustomPlot(widget1);
        leftThigh->setObjectName(QStringLiteral("leftThigh"));

        horizontalLayout_4->addWidget(leftThigh);

        rightThigh = new QCustomPlot(widget1);
        rightThigh->setObjectName(QStringLiteral("rightThigh"));
        leftThigh->raise();

        horizontalLayout_4->addWidget(rightThigh);

        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(710, 480, 411, 161));
        horizontalLayout_5 = new QHBoxLayout(widget2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        leftShank = new QCustomPlot(widget2);
        leftShank->setObjectName(QStringLiteral("leftShank"));

        horizontalLayout_5->addWidget(leftShank);

        rightShank = new QCustomPlot(widget2);
        rightShank->setObjectName(QStringLiteral("rightShank"));

        horizontalLayout_5->addWidget(rightShank);

        widget3 = new QWidget(centralWidget);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(710, 260, 411, 29));
        horizontalLayout = new QHBoxLayout(widget3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_leftThigh = new QLabel(widget3);
        label_leftThigh->setObjectName(QStringLiteral("label_leftThigh"));
        label_leftThigh->setFont(font);

        horizontalLayout->addWidget(label_leftThigh);

        label_rightThigh = new QLabel(widget3);
        label_rightThigh->setObjectName(QStringLiteral("label_rightThigh"));
        label_rightThigh->setFont(font);

        horizontalLayout->addWidget(label_rightThigh);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1152, 23));
        menuCalls = new QMenu(menuBar);
        menuCalls->setObjectName(QStringLiteral("menuCalls"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCalls->menuAction());
        menuCalls->addAction(actionConnect);
        menuCalls->addAction(actionDisconnect);
        menuCalls->addSeparator();
        menuCalls->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        pushButton_save_file->setText(QApplication::translate("MainWindow", "Save Record File", 0));
        pushButton_newFile->setText(QApplication::translate("MainWindow", "New Recored File", 0));
        label_leftShank->setText(QApplication::translate("MainWindow", "Left Shank", 0));
        label_rightShank->setText(QApplication::translate("MainWindow", "Right Shank", 0));
        label_trunk->setText(QApplication::translate("MainWindow", "Trunk", 0));
        label_leftThigh->setText(QApplication::translate("MainWindow", "Left Thigh", 0));
        label_rightThigh->setText(QApplication::translate("MainWindow", "Right Thigh", 0));
        menuCalls->setTitle(QApplication::translate("MainWindow", "Calls", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
