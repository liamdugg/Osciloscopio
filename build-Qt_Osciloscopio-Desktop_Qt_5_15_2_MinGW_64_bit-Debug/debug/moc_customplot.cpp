/****************************************************************************
** Meta object code from reading C++ file 'customplot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QT_Osciloscopio/Qt_Osciloscopio/QCustomPlot/customplot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomPlot_t {
    QByteArrayData data[21];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomPlot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomPlot_t qt_meta_stringdata_CustomPlot = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CustomPlot"
QT_MOC_LITERAL(1, 11, 9), // "itemMoved"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 16), // "QCPAbstractItem*"
QT_MOC_LITERAL(4, 39, 4), // "item"
QT_MOC_LITERAL(5, 44, 12), // "QMouseEvent*"
QT_MOC_LITERAL(6, 57, 5), // "event"
QT_MOC_LITERAL(7, 63, 13), // "setTimeChange"
QT_MOC_LITERAL(8, 77, 30), // "SignalData::samplimngFrecuency"
QT_MOC_LITERAL(9, 108, 6), // "mesure"
QT_MOC_LITERAL(10, 115, 11), // "SignalData*"
QT_MOC_LITERAL(11, 127, 10), // "signalData"
QT_MOC_LITERAL(12, 138, 20), // "pushButtonAutoEscala"
QT_MOC_LITERAL(13, 159, 7), // "LeerADC"
QT_MOC_LITERAL(14, 167, 16), // "QVector<double>*"
QT_MOC_LITERAL(15, 184, 4), // "dato"
QT_MOC_LITERAL(16, 189, 14), // "LeerMediciones"
QT_MOC_LITERAL(17, 204, 16), // "setValueDialTime"
QT_MOC_LITERAL(18, 221, 5), // "value"
QT_MOC_LITERAL(19, 227, 16), // "setValueDialVolt"
QT_MOC_LITERAL(20, 244, 17) // "setRangeDialGraph"

    },
    "CustomPlot\0itemMoved\0\0QCPAbstractItem*\0"
    "item\0QMouseEvent*\0event\0setTimeChange\0"
    "SignalData::samplimngFrecuency\0mesure\0"
    "SignalData*\0signalData\0pushButtonAutoEscala\0"
    "LeerADC\0QVector<double>*\0dato\0"
    "LeerMediciones\0setValueDialTime\0value\0"
    "setValueDialVolt\0setRangeDialGraph"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomPlot[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       7,    1,   64,    2, 0x06 /* Public */,
       9,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   70,    2, 0x0a /* Public */,
      13,    1,   71,    2, 0x0a /* Public */,
      16,    1,   74,    2, 0x0a /* Public */,
      17,    1,   77,    2, 0x0a /* Public */,
      19,    1,   80,    2, 0x0a /* Public */,
      20,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,

       0        // eod
};

void CustomPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomPlot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemMoved((*reinterpret_cast< QCPAbstractItem*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        case 1: _t->setTimeChange((*reinterpret_cast< SignalData::samplimngFrecuency(*)>(_a[1]))); break;
        case 2: _t->mesure((*reinterpret_cast< SignalData*(*)>(_a[1]))); break;
        case 3: _t->pushButtonAutoEscala(); break;
        case 4: _t->LeerADC((*reinterpret_cast< QVector<double>*(*)>(_a[1]))); break;
        case 5: _t->LeerMediciones((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setValueDialTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setValueDialVolt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setRangeDialGraph(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CustomPlot::*)(QCPAbstractItem * , QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomPlot::itemMoved)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CustomPlot::*)(SignalData::samplimngFrecuency );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomPlot::setTimeChange)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CustomPlot::*)(SignalData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomPlot::mesure)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CustomPlot::staticMetaObject = { {
    QMetaObject::SuperData::link<QCustomPlot::staticMetaObject>(),
    qt_meta_stringdata_CustomPlot.data,
    qt_meta_data_CustomPlot,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomPlot.stringdata0))
        return static_cast<void*>(this);
    return QCustomPlot::qt_metacast(_clname);
}

int CustomPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CustomPlot::itemMoved(QCPAbstractItem * _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CustomPlot::setTimeChange(SignalData::samplimngFrecuency _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CustomPlot::mesure(SignalData * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
