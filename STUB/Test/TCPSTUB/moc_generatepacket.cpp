/****************************************************************************
** Meta object code from reading C++ file 'generatepacket.h'
**
** Created: Fri Mar 14 14:59:31 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "generatepacket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'generatepacket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uSTUB_INT qt_meta_data_GeneratePacket[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const STUB_CHAR qt_meta_stringdata_GeneratePacket[] = {
    "GeneratePacket\0"
};

const QMetaObject GeneratePacket::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GeneratePacket,
      qt_meta_data_GeneratePacket, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneratePacket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneratePacket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneratePacket::qt_metacast(const STUB_CHAR *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneratePacket))
        return static_cast<void*>(const_cast< GeneratePacket*>(this));
    return QDialog::qt_metacast(_clname);
}

STUB_INT GeneratePacket::qt_metacall(QMetaObject::Call _c, STUB_INT _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
