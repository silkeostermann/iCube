/****************************************************************************
** Meta object code from reading C++ file 'DynamicPinguin.h'
**
** Created: Tue Mar 20 15:24:13 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DynamicPinguin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DynamicPinguin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DynamicPinguin[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   62,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DynamicPinguin[] = {
    "DynamicPinguin\0\0image,size\0"
    "SquaresProcessed(const Image*,int)\0"
    "squares,size\0ProcessSquares(const Square*,int)\0"
};

const QMetaObject DynamicPinguin::staticMetaObject = {
    { &ModuleInterface::staticMetaObject, qt_meta_stringdata_DynamicPinguin,
      qt_meta_data_DynamicPinguin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DynamicPinguin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DynamicPinguin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DynamicPinguin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DynamicPinguin))
        return static_cast<void*>(const_cast< DynamicPinguin*>(this));
    if (!strcmp(_clname, "org.iCubes.ModuleInterface/1.0"))
        return static_cast< ModuleInterface*>(const_cast< DynamicPinguin*>(this));
    return ModuleInterface::qt_metacast(_clname);
}

int DynamicPinguin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ModuleInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SquaresProcessed((*reinterpret_cast< const Image*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: ProcessSquares((*reinterpret_cast< const Square*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DynamicPinguin::SquaresProcessed(const Image * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
