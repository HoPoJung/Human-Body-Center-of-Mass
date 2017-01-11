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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionExit;
    QWidget *centralWidget;
    QPushButton *pushButton_ConnectDevice;
    QTextBrowser *textBrowser_status;
    QLCDNumber *lcdNumber_heelAngle;
    QPushButton *pushButton_save_file;
    QPushButton *pushButton_newFile;
    QLabel *label_heel;
    QLabel *label_force_heel;
    QLCDNumber *lcdNumber_force_heel;
    QLabel *label_force_heel_2;
    QLabel *label_force_heel_3;
    QLCDNumber *lcdNumber_force_heel_2;
    QLCDNumber *lcdNumber_force_heel_3;
    QMenuBar *menuBar;
    QMenu *menuCalls;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1152, 648);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_ConnectDevice = new QPushButton(centralWidget);
        pushButton_ConnectDevice->setObjectName(QStringLiteral("pushButton_ConnectDevice"));
        pushButton_ConnectDevice->setGeometry(QRect(10, 10, 141, 31));
        textBrowser_status = new QTextBrowser(centralWidget);
        textBrowser_status->setObjectName(QStringLiteral("textBrowser_status"));
        textBrowser_status->setGeometry(QRect(20, 480, 731, 101));
        lcdNumber_heelAngle = new QLCDNumber(centralWidget);
        lcdNumber_heelAngle->setObjectName(QStringLiteral("lcdNumber_heelAngle"));
        lcdNumber_heelAngle->setGeometry(QRect(50, 130, 101, 31));
        pushButton_save_file = new QPushButton(centralWidget);
        pushButton_save_file->setObjectName(QStringLiteral("pushButton_save_file"));
        pushButton_save_file->setGeometry(QRect(10, 70, 141, 31));
        pushButton_newFile = new QPushButton(centralWidget);
        pushButton_newFile->setObjectName(QStringLiteral("pushButton_newFile"));
        pushButton_newFile->setGeometry(QRect(10, 40, 141, 31));
        label_heel = new QLabel(centralWidget);
        label_heel->setObjectName(QStringLiteral("label_heel"));
        label_heel->setGeometry(QRect(20, 110, 121, 21));
        label_force_heel = new QLabel(centralWidget);
        label_force_heel->setObjectName(QStringLiteral("label_force_heel"));
        label_force_heel->setGeometry(QRect(20, 170, 121, 21));
        lcdNumber_force_heel = new QLCDNumber(centralWidget);
        lcdNumber_force_heel->setObjectName(QStringLiteral("lcdNumber_force_heel"));
        lcdNumber_force_heel->setGeometry(QRect(50, 190, 101, 31));
        label_force_heel_2 = new QLabel(centralWidget);
        label_force_heel_2->setObjectName(QStringLiteral("label_force_heel_2"));
        label_force_heel_2->setGeometry(QRect(10, 230, 141, 21));
        label_force_heel_3 = new QLabel(centralWidget);
        label_force_heel_3->setObjectName(QStringLiteral("label_force_heel_3"));
        label_force_heel_3->setGeometry(QRect(20, 290, 141, 21));
        lcdNumber_force_heel_2 = new QLCDNumber(centralWidget);
        lcdNumber_force_heel_2->setObjectName(QStringLiteral("lcdNumber_force_heel_2"));
        lcdNumber_force_heel_2->setGeometry(QRect(50, 250, 101, 31));
        lcdNumber_force_heel_3 = new QLCDNumber(centralWidget);
        lcdNumber_force_heel_3->setObjectName(QStringLiteral("lcdNumber_force_heel_3"));
        lcdNumber_force_heel_3->setGeometry(QRect(60, 310, 101, 31));
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
        pushButton_ConnectDevice->setText(QApplication::translate("MainWindow", "Connect Devices", 0));
        pushButton_save_file->setText(QApplication::translate("MainWindow", "Save Record File", 0));
        pushButton_newFile->setText(QApplication::translate("MainWindow", "New Recored File", 0));
        label_heel->setText(QApplication::translate("MainWindow", "Heel Inclination", 0));
        label_force_heel->setText(QApplication::translate("MainWindow", "Force Senso Heelr", 0));
        label_force_heel_2->setText(QApplication::translate("MainWindow", "Force Senso Meta1", 0));
        label_force_heel_3->setText(QApplication::translate("MainWindow", "Force Senso Meta2", 0));
        menuCalls->setTitle(QApplication::translate("MainWindow", "Calls", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
