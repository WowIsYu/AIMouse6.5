/****************************************************************************
** Meta object code from reading C++ file 'blinkcalibration.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../blinkcalibration.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'blinkcalibration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS = QtMocHelpers::stringData(
    "BlinkCalibration",
    "onCaliTrigger",
    "",
    "onCalibrationResult",
    "isOk",
    "score",
    "on_beginCaliButton_clicked",
    "onChooseBlueEvent",
    "hnnk::DataAppOperator",
    "type",
    "name",
    "initBlinkCali"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[17];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[5];
    char stringdata5[6];
    char stringdata6[27];
    char stringdata7[18];
    char stringdata8[22];
    char stringdata9[5];
    char stringdata10[5];
    char stringdata11[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS_t qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS = {
    {
        QT_MOC_LITERAL(0, 16),  // "BlinkCalibration"
        QT_MOC_LITERAL(17, 13),  // "onCaliTrigger"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 19),  // "onCalibrationResult"
        QT_MOC_LITERAL(52, 4),  // "isOk"
        QT_MOC_LITERAL(57, 5),  // "score"
        QT_MOC_LITERAL(63, 26),  // "on_beginCaliButton_clicked"
        QT_MOC_LITERAL(90, 17),  // "onChooseBlueEvent"
        QT_MOC_LITERAL(108, 21),  // "hnnk::DataAppOperator"
        QT_MOC_LITERAL(130, 4),  // "type"
        QT_MOC_LITERAL(135, 4),  // "name"
        QT_MOC_LITERAL(140, 13)   // "initBlinkCali"
    },
    "BlinkCalibration",
    "onCaliTrigger",
    "",
    "onCalibrationResult",
    "isOk",
    "score",
    "on_beginCaliButton_clicked",
    "onChooseBlueEvent",
    "hnnk::DataAppOperator",
    "type",
    "name",
    "initBlinkCali"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBlinkCalibrationENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    2,   45,    2, 0x08,    2 /* Private */,
       6,    0,   50,    2, 0x08,    5 /* Private */,
       7,    2,   51,    2, 0x0a,    6 /* Public */,
      11,    0,   56,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Float,    4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    9,   10,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject BlinkCalibration::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBlinkCalibrationENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BlinkCalibration, std::true_type>,
        // method 'onCaliTrigger'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCalibrationResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'on_beginCaliButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onChooseBlueEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<hnnk::DataAppOperator, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'initBlinkCali'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void BlinkCalibration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BlinkCalibration *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onCaliTrigger(); break;
        case 1: _t->onCalibrationResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2]))); break;
        case 2: _t->on_beginCaliButton_clicked(); break;
        case 3: _t->onChooseBlueEvent((*reinterpret_cast< std::add_pointer_t<hnnk::DataAppOperator>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->initBlinkCali(); break;
        default: ;
        }
    }
}

const QMetaObject *BlinkCalibration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BlinkCalibration::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBlinkCalibrationENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BlinkCalibration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
