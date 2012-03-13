/****************************************************************************
** Meta object code from reading C++ file 'ObjectProcessor.h'
**
** Created: Fri Mar 9 01:14:59 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Logic/ObjectProcessor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ObjectProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ObjectProcessor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      41,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     106,   81,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ObjectProcessor[] = {
    "ObjectProcessor\0\0processedQuadrilaterals\0"
    "QuadrilateralsProcessed(const Object**)\0"
    "recognizedQuadrilaterals\0"
    "ProcessQuadrilaterals(const Quadrilateral**)\0"
};

void BinaryMath::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BinaryMath *_t = static_cast<BinaryMath *>(_o);
        switch (_id) {
        case 0: _t->QuadrilateralsProcessed((*reinterpret_cast< const Object**(*)>(_a[1]))); break;
        case 1: _t->ProcessQuadrilaterals((*reinterpret_cast< const Square**(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BinaryMath::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BinaryMath::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ObjectProcessor,
      qt_meta_data_ObjectProcessor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BinaryMath::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BinaryMath::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BinaryMath::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectProcessor))
        return static_cast<void*>(const_cast< BinaryMath*>(this));
    return QObject::qt_metacast(_clname);
}

int BinaryMath::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void BinaryMath::QuadrilateralsProcessed(const Object * * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
