/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[477];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "recordData_Thread"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "updateView"
QT_MOC_LITERAL(4, 41, 22), // "initHumanSkeletonModel"
QT_MOC_LITERAL(5, 64, 22), // "motionCaptureAnimation"
QT_MOC_LITERAL(6, 87, 26), // "sendQuaternionDataToMatlab"
QT_MOC_LITERAL(7, 114, 23), // "sendAngularDataToMatlab"
QT_MOC_LITERAL(8, 138, 31), // "on_pushButton_save_file_clicked"
QT_MOC_LITERAL(9, 170, 29), // "on_pushButton_newFile_clicked"
QT_MOC_LITERAL(10, 200, 41), // "on_actionConnect_Left_Thigh_I..."
QT_MOC_LITERAL(11, 242, 42), // "on_actionConnect_Right_Thigh_..."
QT_MOC_LITERAL(12, 285, 33), // "on_actionLeft_Shank_IMU_trigg..."
QT_MOC_LITERAL(13, 319, 34), // "on_actionRight_Shank_IMU_trig..."
QT_MOC_LITERAL(14, 354, 32), // "on_actionLeft_Foot_IMU_triggered"
QT_MOC_LITERAL(15, 387, 33), // "on_actionRight_Foot_IMU_trigg..."
QT_MOC_LITERAL(16, 421, 24), // "on_actionWaist_triggered"
QT_MOC_LITERAL(17, 446, 30) // "on_actionCalibration_triggered"

    },
    "MainWindow\0recordData_Thread\0\0updateView\0"
    "initHumanSkeletonModel\0motionCaptureAnimation\0"
    "sendQuaternionDataToMatlab\0"
    "sendAngularDataToMatlab\0"
    "on_pushButton_save_file_clicked\0"
    "on_pushButton_newFile_clicked\0"
    "on_actionConnect_Left_Thigh_IMU_triggered\0"
    "on_actionConnect_Right_Thigh_IMU_triggered\0"
    "on_actionLeft_Shank_IMU_triggered\0"
    "on_actionRight_Shank_IMU_triggered\0"
    "on_actionLeft_Foot_IMU_triggered\0"
    "on_actionRight_Foot_IMU_triggered\0"
    "on_actionWaist_triggered\0"
    "on_actionCalibration_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->recordData_Thread(); break;
        case 1: _t->updateView(); break;
        case 2: _t->initHumanSkeletonModel(); break;
        case 3: _t->motionCaptureAnimation(); break;
        case 4: _t->sendQuaternionDataToMatlab(); break;
        case 5: _t->sendAngularDataToMatlab(); break;
        case 6: _t->on_pushButton_save_file_clicked(); break;
        case 7: _t->on_pushButton_newFile_clicked(); break;
        case 8: _t->on_actionConnect_Left_Thigh_IMU_triggered(); break;
        case 9: _t->on_actionConnect_Right_Thigh_IMU_triggered(); break;
        case 10: _t->on_actionLeft_Shank_IMU_triggered(); break;
        case 11: _t->on_actionRight_Shank_IMU_triggered(); break;
        case 12: _t->on_actionLeft_Foot_IMU_triggered(); break;
        case 13: _t->on_actionRight_Foot_IMU_triggered(); break;
        case 14: _t->on_actionWaist_triggered(); break;
        case 15: _t->on_actionCalibration_triggered(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
