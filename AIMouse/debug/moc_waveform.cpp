/****************************************************************************
** Meta object code from reading C++ file 'waveform.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../waveform.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'waveform.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSWaveformENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSWaveformENDCLASS = QtMocHelpers::stringData(
    "Waveform",
    "popSetWindows",
    "",
    "on_action_Add_Event_triggered",
    "on_action_Start_Acquisition_triggered",
    "on_action_Stop_Acquisition_triggered",
    "on_action_Open_triggered",
    "on_action_Start_Record_triggered",
    "plotEvent",
    "key",
    "evtNumber",
    "onModifyDeviceName",
    "name",
    "onDealManualMarking",
    "markVal",
    "onMsg",
    "type",
    "msg",
    "onPopMsgBox",
    "onReciveEegData",
    "QList<hnnk::EegDataChan>",
    "eegVec",
    "onDeviceChannelAndSampRate",
    "chs",
    "srate",
    "onAddtionData",
    "QList<GYRODATA>",
    "gyroDatas",
    "QList<uchar>",
    "channoff",
    "battery",
    "onDeviceNameUpdate",
    "devices",
    "onConnectUpdate",
    "CONNECTUPDATE",
    "onUpdateSelfCheckInfo",
    "AmpTestInfo",
    "onChooseBlueEvent",
    "hnnk::DataAppOperator",
    "onReadEdfDataToDouble",
    "QList<hnnk::DataPoint>&",
    "dVecs",
    "QVariant&",
    "otherData",
    "ch",
    "onSearchOver"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWaveformENDCLASS_t {
    uint offsetsAndSizes[92];
    char stringdata0[9];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[30];
    char stringdata4[38];
    char stringdata5[37];
    char stringdata6[25];
    char stringdata7[33];
    char stringdata8[10];
    char stringdata9[4];
    char stringdata10[10];
    char stringdata11[19];
    char stringdata12[5];
    char stringdata13[20];
    char stringdata14[8];
    char stringdata15[6];
    char stringdata16[5];
    char stringdata17[4];
    char stringdata18[12];
    char stringdata19[16];
    char stringdata20[25];
    char stringdata21[7];
    char stringdata22[27];
    char stringdata23[4];
    char stringdata24[6];
    char stringdata25[14];
    char stringdata26[16];
    char stringdata27[10];
    char stringdata28[13];
    char stringdata29[9];
    char stringdata30[8];
    char stringdata31[19];
    char stringdata32[8];
    char stringdata33[16];
    char stringdata34[14];
    char stringdata35[22];
    char stringdata36[12];
    char stringdata37[18];
    char stringdata38[22];
    char stringdata39[22];
    char stringdata40[24];
    char stringdata41[6];
    char stringdata42[10];
    char stringdata43[10];
    char stringdata44[3];
    char stringdata45[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWaveformENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWaveformENDCLASS_t qt_meta_stringdata_CLASSWaveformENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "Waveform"
        QT_MOC_LITERAL(9, 13),  // "popSetWindows"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 29),  // "on_action_Add_Event_triggered"
        QT_MOC_LITERAL(54, 37),  // "on_action_Start_Acquisition_t..."
        QT_MOC_LITERAL(92, 36),  // "on_action_Stop_Acquisition_tr..."
        QT_MOC_LITERAL(129, 24),  // "on_action_Open_triggered"
        QT_MOC_LITERAL(154, 32),  // "on_action_Start_Record_triggered"
        QT_MOC_LITERAL(187, 9),  // "plotEvent"
        QT_MOC_LITERAL(197, 3),  // "key"
        QT_MOC_LITERAL(201, 9),  // "evtNumber"
        QT_MOC_LITERAL(211, 18),  // "onModifyDeviceName"
        QT_MOC_LITERAL(230, 4),  // "name"
        QT_MOC_LITERAL(235, 19),  // "onDealManualMarking"
        QT_MOC_LITERAL(255, 7),  // "markVal"
        QT_MOC_LITERAL(263, 5),  // "onMsg"
        QT_MOC_LITERAL(269, 4),  // "type"
        QT_MOC_LITERAL(274, 3),  // "msg"
        QT_MOC_LITERAL(278, 11),  // "onPopMsgBox"
        QT_MOC_LITERAL(290, 15),  // "onReciveEegData"
        QT_MOC_LITERAL(306, 24),  // "QList<hnnk::EegDataChan>"
        QT_MOC_LITERAL(331, 6),  // "eegVec"
        QT_MOC_LITERAL(338, 26),  // "onDeviceChannelAndSampRate"
        QT_MOC_LITERAL(365, 3),  // "chs"
        QT_MOC_LITERAL(369, 5),  // "srate"
        QT_MOC_LITERAL(375, 13),  // "onAddtionData"
        QT_MOC_LITERAL(389, 15),  // "QList<GYRODATA>"
        QT_MOC_LITERAL(405, 9),  // "gyroDatas"
        QT_MOC_LITERAL(415, 12),  // "QList<uchar>"
        QT_MOC_LITERAL(428, 8),  // "channoff"
        QT_MOC_LITERAL(437, 7),  // "battery"
        QT_MOC_LITERAL(445, 18),  // "onDeviceNameUpdate"
        QT_MOC_LITERAL(464, 7),  // "devices"
        QT_MOC_LITERAL(472, 15),  // "onConnectUpdate"
        QT_MOC_LITERAL(488, 13),  // "CONNECTUPDATE"
        QT_MOC_LITERAL(502, 21),  // "onUpdateSelfCheckInfo"
        QT_MOC_LITERAL(524, 11),  // "AmpTestInfo"
        QT_MOC_LITERAL(536, 17),  // "onChooseBlueEvent"
        QT_MOC_LITERAL(554, 21),  // "hnnk::DataAppOperator"
        QT_MOC_LITERAL(576, 21),  // "onReadEdfDataToDouble"
        QT_MOC_LITERAL(598, 23),  // "QList<hnnk::DataPoint>&"
        QT_MOC_LITERAL(622, 5),  // "dVecs"
        QT_MOC_LITERAL(628, 9),  // "QVariant&"
        QT_MOC_LITERAL(638, 9),  // "otherData"
        QT_MOC_LITERAL(648, 2),  // "ch"
        QT_MOC_LITERAL(651, 12)   // "onSearchOver"
    },
    "Waveform",
    "popSetWindows",
    "",
    "on_action_Add_Event_triggered",
    "on_action_Start_Acquisition_triggered",
    "on_action_Stop_Acquisition_triggered",
    "on_action_Open_triggered",
    "on_action_Start_Record_triggered",
    "plotEvent",
    "key",
    "evtNumber",
    "onModifyDeviceName",
    "name",
    "onDealManualMarking",
    "markVal",
    "onMsg",
    "type",
    "msg",
    "onPopMsgBox",
    "onReciveEegData",
    "QList<hnnk::EegDataChan>",
    "eegVec",
    "onDeviceChannelAndSampRate",
    "chs",
    "srate",
    "onAddtionData",
    "QList<GYRODATA>",
    "gyroDatas",
    "QList<uchar>",
    "channoff",
    "battery",
    "onDeviceNameUpdate",
    "devices",
    "onConnectUpdate",
    "CONNECTUPDATE",
    "onUpdateSelfCheckInfo",
    "AmpTestInfo",
    "onChooseBlueEvent",
    "hnnk::DataAppOperator",
    "onReadEdfDataToDouble",
    "QList<hnnk::DataPoint>&",
    "dVecs",
    "QVariant&",
    "otherData",
    "ch",
    "onSearchOver"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWaveformENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  134,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,  137,    2, 0x08,    3 /* Private */,
       4,    0,  138,    2, 0x08,    4 /* Private */,
       5,    0,  139,    2, 0x08,    5 /* Private */,
       6,    0,  140,    2, 0x08,    6 /* Private */,
       7,    0,  141,    2, 0x08,    7 /* Private */,
       8,    2,  142,    2, 0x08,    8 /* Private */,
      11,    1,  147,    2, 0x08,   11 /* Private */,
      13,    1,  150,    2, 0x08,   13 /* Private */,
      15,    2,  153,    2, 0x08,   15 /* Private */,
      18,    2,  158,    2, 0x0a,   18 /* Public */,
      19,    1,  163,    2, 0x0a,   21 /* Public */,
      22,    2,  166,    2, 0x0a,   23 /* Public */,
      25,    3,  171,    2, 0x0a,   26 /* Public */,
      31,    1,  178,    2, 0x0a,   30 /* Public */,
      33,    1,  181,    2, 0x0a,   32 /* Public */,
      35,    1,  184,    2, 0x0a,   34 /* Public */,
      37,    2,  187,    2, 0x0a,   36 /* Public */,
      39,    3,  192,    2, 0x0a,   39 /* Public */,
      45,    0,  199,    2, 0x0a,   43 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   16,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   16,   17,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   23,   24,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 28, QMetaType::Double,   27,   29,   30,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, 0x80000000 | 34,    2,
    QMetaType::Void, 0x80000000 | 36,    2,
    QMetaType::Void, 0x80000000 | 38, QMetaType::QString,   16,   12,
    QMetaType::Void, 0x80000000 | 40, 0x80000000 | 42, QMetaType::Int,   41,   43,   44,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Waveform::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSWaveformENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWaveformENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWaveformENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Waveform, std::true_type>,
        // method 'popSetWindows'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_action_Add_Event_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_Start_Acquisition_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_Stop_Acquisition_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_Open_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_Start_Record_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'plotEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onModifyDeviceName'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onDealManualMarking'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onPopMsgBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onReciveEegData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<hnnk::EegDataChan>, std::false_type>,
        // method 'onDeviceChannelAndSampRate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onAddtionData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<GYRODATA>, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<unsigned char>, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onDeviceNameUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onConnectUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<CONNECTUPDATE, std::false_type>,
        // method 'onUpdateSelfCheckInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<AmpTestInfo, std::false_type>,
        // method 'onChooseBlueEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<hnnk::DataAppOperator, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onReadEdfDataToDouble'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<hnnk::DataPoint> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVariant &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onSearchOver'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Waveform::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Waveform *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->popSetWindows((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->on_action_Add_Event_triggered(); break;
        case 2: _t->on_action_Start_Acquisition_triggered(); break;
        case 3: _t->on_action_Stop_Acquisition_triggered(); break;
        case 4: _t->on_action_Open_triggered(); break;
        case 5: _t->on_action_Start_Record_triggered(); break;
        case 6: _t->plotEvent((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->onModifyDeviceName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->onDealManualMarking((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->onMsg((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->onPopMsgBox((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->onReciveEegData((*reinterpret_cast< std::add_pointer_t<QList<hnnk::EegDataChan>>>(_a[1]))); break;
        case 12: _t->onDeviceChannelAndSampRate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 13: _t->onAddtionData((*reinterpret_cast< std::add_pointer_t<QList<GYRODATA>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<uchar>>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 14: _t->onDeviceNameUpdate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->onConnectUpdate((*reinterpret_cast< std::add_pointer_t<CONNECTUPDATE>>(_a[1]))); break;
        case 16: _t->onUpdateSelfCheckInfo((*reinterpret_cast< std::add_pointer_t<AmpTestInfo>>(_a[1]))); break;
        case 17: _t->onChooseBlueEvent((*reinterpret_cast< std::add_pointer_t<hnnk::DataAppOperator>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 18: _t->onReadEdfDataToDouble((*reinterpret_cast< std::add_pointer_t<QList<hnnk::DataPoint>&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant&>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 19: _t->onSearchOver(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<uchar> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Waveform::*)(QString );
            if (_t _q_method = &Waveform::popSetWindows; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *Waveform::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Waveform::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWaveformENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Waveform::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void Waveform::popSetWindows(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
