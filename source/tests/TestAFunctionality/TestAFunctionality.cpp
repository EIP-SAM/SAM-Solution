/****************************************************************************
** Meta object code from reading C++ file 'TestAFunctionality.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TestAFunctionality.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TestAFunctionality.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestAFunctionality[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   27,   27,   27, 0x05,
      28,   27,   27,   27, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TestAFunctionality[] = {
    "TestAFunctionality\0start()\0\0stop()\0"
};

void TestAFunctionality::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TestAFunctionality *_t = static_cast<TestAFunctionality *>(_o);
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TestAFunctionality::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TestAFunctionality::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestAFunctionality,
      qt_meta_data_TestAFunctionality, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestAFunctionality::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestAFunctionality::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestAFunctionality::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestAFunctionality))
        return static_cast<void*>(const_cast< TestAFunctionality*>(this));
    return QObject::qt_metacast(_clname);
}

int TestAFunctionality::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TestAFunctionality::start()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TestAFunctionality::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
