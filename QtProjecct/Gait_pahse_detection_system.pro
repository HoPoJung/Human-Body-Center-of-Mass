#-------------------------------------------------
#
# Project created by QtCreator 2016-06-20T00:26:33
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gait_pahse_detection_system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote(C:\OpenMAT\OpenMAT-1.3.5\include)

LIBS += $$quote(C:\OpenMAT\OpenMAT-1.3.5\lib\x86\LpSensor.lib) \
        $$quote(C:\OpenMAT\OpenMAT-1.3.5\lib\x86\LpSensorD.lib)
