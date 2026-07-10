/****************************************************************************
** Meta object code from reading C++ file 'control_mode_panel.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../aichallenge/workspace/src/aichallenge_system/aichallenge_control_rviz_plugin/include/aichallenge_control_rviz_plugin/control_mode_panel.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'control_mode_panel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_aichallenge_control_rviz_plugin__ControlModePanel_t {
    QByteArrayData data[5];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_aichallenge_control_rviz_plugin__ControlModePanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_aichallenge_control_rviz_plugin__ControlModePanel_t qt_meta_stringdata_aichallenge_control_rviz_plugin__ControlModePanel = {
    {
QT_MOC_LITERAL(0, 0, 49), // "aichallenge_control_rviz_plug..."
QT_MOC_LITERAL(1, 50, 22), // "sendControlModeRequest"
QT_MOC_LITERAL(2, 73, 0), // ""
QT_MOC_LITERAL(3, 74, 19), // "sendControlModeStop"
QT_MOC_LITERAL(4, 94, 18) // "sendInitialPoseSet"

    },
    "aichallenge_control_rviz_plugin::ControlModePanel\0"
    "sendControlModeRequest\0\0sendControlModeStop\0"
    "sendInitialPoseSet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_aichallenge_control_rviz_plugin__ControlModePanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void aichallenge_control_rviz_plugin::ControlModePanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControlModePanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sendControlModeRequest(); break;
        case 1: _t->sendControlModeStop(); break;
        case 2: _t->sendInitialPoseSet(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject aichallenge_control_rviz_plugin::ControlModePanel::staticMetaObject = { {
    QMetaObject::SuperData::link<rviz_common::Panel::staticMetaObject>(),
    qt_meta_stringdata_aichallenge_control_rviz_plugin__ControlModePanel.data,
    qt_meta_data_aichallenge_control_rviz_plugin__ControlModePanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *aichallenge_control_rviz_plugin::ControlModePanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *aichallenge_control_rviz_plugin::ControlModePanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_aichallenge_control_rviz_plugin__ControlModePanel.stringdata0))
        return static_cast<void*>(this);
    return rviz_common::Panel::qt_metacast(_clname);
}

int aichallenge_control_rviz_plugin::ControlModePanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rviz_common::Panel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
