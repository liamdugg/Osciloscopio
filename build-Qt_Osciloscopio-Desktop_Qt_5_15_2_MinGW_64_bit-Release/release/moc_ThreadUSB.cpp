/****************************************************************************
** Meta object code from reading C++ file 'ThreadUSB.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QT_Osciloscopio/Qt_Osciloscopio/USB/ThreadUSB.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ThreadUSB.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadUSB_t {
    QByteArrayData data[18];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadUSB_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadUSB_t qt_meta_stringdata_ThreadUSB = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ThreadUSB"
QT_MOC_LITERAL(1, 10, 12), // "datoNuevoADC"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 16), // "QVector<double>*"
QT_MOC_LITERAL(4, 41, 4), // "data"
QT_MOC_LITERAL(5, 46, 19), // "datoNuevoMediciones"
QT_MOC_LITERAL(6, 66, 10), // "dataSignal"
QT_MOC_LITERAL(7, 77, 9), // "modChange"
QT_MOC_LITERAL(8, 87, 4), // "Modo"
QT_MOC_LITERAL(9, 92, 3), // "mod"
QT_MOC_LITERAL(10, 96, 10), // "timeChange"
QT_MOC_LITERAL(11, 107, 30), // "SignalData::samplimngFrecuency"
QT_MOC_LITERAL(12, 138, 2), // "fs"
QT_MOC_LITERAL(13, 141, 8), // "modoNone"
QT_MOC_LITERAL(14, 150, 12), // "modoConected"
QT_MOC_LITERAL(15, 163, 15), // "modoDisconected"
QT_MOC_LITERAL(16, 179, 8), // "modoDato"
QT_MOC_LITERAL(17, 188, 10) // "modoSignal"

    },
    "ThreadUSB\0datoNuevoADC\0\0QVector<double>*\0"
    "data\0datoNuevoMediciones\0dataSignal\0"
    "modChange\0Modo\0mod\0timeChange\0"
    "SignalData::samplimngFrecuency\0fs\0"
    "modoNone\0modoConected\0modoDisconected\0"
    "modoDato\0modoSignal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadUSB[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       1,   46, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   40,    2, 0x0a /* Public */,
      10,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

 // enums: name, alias, flags, count, data
       8,    8, 0x0,    5,   51,

 // enum data: key, value
      13, uint(ThreadUSB::modoNone),
      14, uint(ThreadUSB::modoConected),
      15, uint(ThreadUSB::modoDisconected),
      16, uint(ThreadUSB::modoDato),
      17, uint(ThreadUSB::modoSignal),

       0        // eod
};

void ThreadUSB::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadUSB *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->datoNuevoADC((*reinterpret_cast< QVector<double>*(*)>(_a[1]))); break;
        case 1: _t->datoNuevoMediciones((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->modChange((*reinterpret_cast< Modo(*)>(_a[1]))); break;
        case 3: _t->timeChange((*reinterpret_cast< SignalData::samplimngFrecuency(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThreadUSB::*)(QVector<double> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadUSB::datoNuevoADC)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ThreadUSB::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadUSB::datoNuevoMediciones)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadUSB::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_ThreadUSB.data,
    qt_meta_data_ThreadUSB,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadUSB::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadUSB::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadUSB.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ThreadUSB::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ThreadUSB::datoNuevoADC(QVector<double> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreadUSB::datoNuevoMediciones(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
