/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed May 14 22:01:30 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      25,   11,   11,   11, 0x0a,
      39,   11,   11,   11, 0x0a,
      53,   11,   11,   11, 0x0a,
      67,   11,   11,   11, 0x0a,
      75,   11,   11,   11, 0x0a,
      91,   11,   11,   11, 0x0a,
     117,   11,   11,   11, 0x0a,
     142,   11,   11,   11, 0x0a,
     158,   11,   11,   11, 0x0a,
     173,   11,   11,   11, 0x0a,
     189,   11,   11,   11, 0x0a,
     212,   11,   11,   11, 0x0a,
     226,   11,   11,   11, 0x0a,
     257,   11,   11,   11, 0x0a,
     272,   11,   11,   11, 0x0a,
     299,   11,   11,   11, 0x0a,
     330,   11,  325,   11, 0x0a,
     344,   11,  325,   11, 0x0a,
     358,   11,  325,   11, 0x0a,
     372,   11,  325,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0newProject()\0openProject()\0"
    "saveProject()\0addDbServer()\0about()\0"
    "startSniffing()\0saveScenarioCredentials()\0"
    "showPackets(QModelIndex)\0showInterface()\0"
    "showScenario()\0returnControl()\0"
    "genPacketFromTcpDump()\0startServer()\0"
    "startDummyServerDataTransfer()\0"
    "stopSniffing()\0showPacketsAddNewPackets()\0"
    "addNewpacket(QModelIndex)\0bool\0"
    "cancelQuery()\0updateQuery()\0insertQuery()\0"
    "deleteQuery()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->newProject(); break;
        case 1: _t->openProject(); break;
        case 2: _t->saveProject(); break;
        case 3: _t->addDbServer(); break;
        case 4: _t->about(); break;
        case 5: _t->startSniffing(); break;
        case 6: _t->saveScenarioCredentials(); break;
        case 7: _t->showPackets((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->showInterface(); break;
        case 9: _t->showScenario(); break;
        case 10: _t->returnControl(); break;
        case 11: _t->genPacketFromTcpDump(); break;
        case 12: _t->startServer(); break;
        case 13: _t->startDummyServerDataTransfer(); break;
        case 14: _t->stopSniffing(); break;
        case 15: _t->showPacketsAddNewPackets(); break;
        case 16: _t->addNewpacket((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 17: { bool _r = _t->cancelQuery();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: { bool _r = _t->updateQuery();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { bool _r = _t->insertQuery();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 20: { bool _r = _t->deleteQuery();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
