/****************************************************************************
** Meta object code from reading C++ file 'crossline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QT_Osciloscopio/Qt_Osciloscopio/QCustomPlot/crossline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'crossline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CrossLine_t {
    QByteArrayData data[17];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CrossLine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CrossLine_t qt_meta_stringdata_CrossLine = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CrossLine"
QT_MOC_LITERAL(1, 10, 12), // "onMouseMoved"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 37, 5), // "event"
QT_MOC_LITERAL(5, 43, 11), // "onItemMoved"
QT_MOC_LITERAL(6, 55, 16), // "QCPAbstractItem*"
QT_MOC_LITERAL(7, 72, 4), // "item"
QT_MOC_LITERAL(8, 77, 6), // "update"
QT_MOC_LITERAL(9, 84, 24), // "checkBoxUpdateHorizontal"
QT_MOC_LITERAL(10, 109, 5), // "index"
QT_MOC_LITERAL(11, 115, 22), // "checkBoxUpdateVertical"
QT_MOC_LITERAL(12, 138, 8), // "LineMode"
QT_MOC_LITERAL(13, 147, 6), // "lmNone"
QT_MOC_LITERAL(14, 154, 6), // "lmFree"
QT_MOC_LITERAL(15, 161, 14), // "lmFollowCursor"
QT_MOC_LITERAL(16, 176, 9) // "lmTracing"

    },
    "CrossLine\0onMouseMoved\0\0QMouseEvent*\0"
    "event\0onItemMoved\0QCPAbstractItem*\0"
    "item\0update\0checkBoxUpdateHorizontal\0"
    "index\0checkBoxUpdateVertical\0LineMode\0"
    "lmNone\0lmFree\0lmFollowCursor\0lmTracing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CrossLine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       1,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    2,   42,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,
       9,    1,   48,    2, 0x0a /* Public */,
      11,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 3,    7,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,

 // enums: name, alias, flags, count, data
      12,   12, 0x0,    4,   59,

 // enum data: key, value
      13, uint(CrossLine::lmNone),
      14, uint(CrossLine::lmFree),
      15, uint(CrossLine::lmFollowCursor),
      16, uint(CrossLine::lmTracing),

       0        // eod
};

void CrossLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CrossLine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onMouseMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->onItemMoved((*reinterpret_cast< QCPAbstractItem*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        case 2: _t->update(); break;
        case 3: _t->checkBoxUpdateHorizontal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->checkBoxUpdateVertical((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CrossLine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CrossLine.data,
    qt_meta_data_CrossLine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CrossLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CrossLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CrossLine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CrossLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
