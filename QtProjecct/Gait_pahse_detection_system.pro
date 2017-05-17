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

INCLUDEPATH += $$quote(C:\OpenMAT\OpenMAT-1.3.4-x64\include)    \
                $$quote(C:\Program Files\MATLAB\R2013\extern\include)


LIBS += $$quote(C:\OpenMAT\OpenMAT-1.3.4-x64\lib\x64\LpSensor.lib) \
        $$quote(C:\OpenMAT\OpenMAT-1.3.4-x64\lib\x64\LpSensorD.lib) \
        $$quote(C:\Program Files\MATLAB\R2013\extern\lib\win64\microsoft\libeng.lib)    \
        $$quote(C:\Program Files\MATLAB\R2013\extern\lib\win64\microsoft\libmx.lib)     \
        $$quote(C:\Program Files\MATLAB\R2013\extern\lib\win64\microsoft\libmex.lib)    \
        $$quote(C:\Program Files\MATLAB\R2013\extern\lib\win64\microsoft\libmat.lib)

