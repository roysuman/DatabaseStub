/****************************************************************************
** Meta object code from reading C++ file 'openproject.h'
**
** Created: Mon Mar 17 10:32:08 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "openproject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openproject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_openProject[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      22,   12,   12,   12, 0x0a,
      27,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_openProject[] = {
    "openProject\0\0browse()\0ok()\0cancel()\0"
};

const QMetaObject openProject::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_openProject,
      qt_meta_data_openProject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &openProject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *openProject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *openProject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_openProject))
        return static_cast<void*>(const_cast< openProject*>(this));
    return QDialog::qt_metacast(_clname);
}

int openProject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: browse(); break;
        case 1: ok(); break;
        case 2: cancel(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
