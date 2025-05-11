#include "hmulticontrolwrapper.h"
#include "HMultiControlSDK.h"

using namespace hnnk;
class HMultiControlWrapper::Impl {
public:
    hnnk::HMultiControlSDK *multiControl;
};


HMultiControlWrapper::HMultiControlWrapper(QObject *parent)
    : QObject(parent), m_impl(new Impl) {

    initial();

    connect(m_impl->multiControl, &HMultiControlSDK::notifyDeviceNameUpdate,
            this, &HMultiControlWrapper::notifyDeviceNameUpdate);

    connect(m_impl->multiControl->m_dataSystem, &HDataSystem_interface::emitSearchNetDeviceOver,
            this, &HMultiControlWrapper::emitSearchNetDeviceOver);

    connect(m_impl->multiControl->m_dataSystem, &HDataSystem_interface::emitMsgBox,
            this, &HMultiControlWrapper::emitMsgBox);

    connect(m_impl->multiControl, &HMultiControlSDK::emitGyroData,
            this, &HMultiControlWrapper::emitGyroData);

    connect(m_impl->multiControl, &HMultiControlSDK::notifyBlinkDetectionResult,
            this, &HMultiControlWrapper::notifyBlinkDetectionResult);

    connect(m_impl->multiControl, &HMultiControlSDK::notifyAttenDetectionResult,
            [this](double val) {emit this->notifyAttenDetectionResult(val*100);});

    connect(m_impl->multiControl, &HMultiControlSDK::notifyConnectState,
            this, &HMultiControlWrapper::notifyConnectState);

    connect(m_impl->multiControl, &HMultiControlSDK::notifyCalibrationResult,
            this, &HMultiControlWrapper::notifyCalibrationResult);

    connect(m_impl->multiControl, &HMultiControlSDK::notifyCaliTrigger,
            this, &HMultiControlWrapper::notifyCaliTrigger);


    //通知读取脑电信号
    connect(m_impl->multiControl->m_dataSystem, &HDataSystem_interface::emitEvent
            , this, &HMultiControlWrapper::emitEvent);
    //通知读取脑电通道及采样数据(int chs, int rate)设备总的通道数， 采样率
    connect(m_impl->multiControl->m_dataSystem, &HDataSystem_interface::emitChsAndSampRate
            , this, &HMultiControlWrapper::emitChsAndSampRate);
    //通知读取陀螺仪，通道状态， 电量三种数据（QVector<hnnk::GYRODATA> gyroDatas, QVector<unsigned char> channoff, double battery）
    connect(m_impl->multiControl->m_dataSystem, &HDataSystem_interface::emitAddtionData
            , this, &HMultiControlWrapper::emitAddtionData);
    //通知连接状态发生改变
    connect(m_impl->multiControl->m_dataSystem, &HDataSystem_interface::emitConnectChange
            , this, &HMultiControlWrapper::emitConnectChange);
    //通知读取设备自检结果(hnnk::AmpTestInfo info)
    connect(m_impl->multiControl->m_dataSystem, &HDataSystem_interface::emitUpdateAmpTestInfo
            , this, &HMultiControlWrapper::emitUpdateAmpTestInfo);
    //通知读取本地edf数据（脑电信号， 基本参数， 第几通道）
    connect(m_impl->multiControl->m_dataSystem, &HDataSystem_interface::emitEdfData
            , this, &HMultiControlWrapper::emitEdfData);
}

// 析构函数中释放 Impl
HMultiControlWrapper::~HMultiControlWrapper() {
    delete m_impl->multiControl;
    delete m_impl;
}


void HMultiControlWrapper::initial() {
    m_impl->multiControl = new HMultiControlSDK(this);
    m_impl->multiControl->setLicense("c180dec8f4d94af6be5860436ca26003");
    m_impl->multiControl->lauchCollector(DATA_FIRSTGENERAL, hnnk::NET_COM);
}

void HMultiControlWrapper::resetLocation()
{
    m_impl->multiControl->resetLocation();
}

void HMultiControlWrapper::connectDevice(DataAppOperator dataOperator, QString name)
{
    m_impl->multiControl->connectDevice(name);
}

void HMultiControlWrapper::setSensitivity(int sensitivity)
{
    m_impl->multiControl->setSensitivity(sensitivity);
}

bool HMultiControlWrapper::initEegDataCollectorEnv(hnnk::DSPROTOCOLTYPE type, hnnk::DSNETTYPE netType)
{
    return m_impl->multiControl->m_dataSystem->initEegDataCollectorEnv(type, netType);
}

void HMultiControlWrapper::getGraphValidateCode(QPixmap &lable, QString &imageId)
{
    m_impl->multiControl->getGraphValidateCode(lable, imageId);
}

QString HMultiControlWrapper::registAccounter(const QString accountName, const QString pwd, const QString graphCode, const QString imagId)
{
    return m_impl->multiControl->registAccounter(accountName, pwd, graphCode, imagId);
}

QString HMultiControlWrapper::login(const QString accountName, const QString pwd, const QString graphCode, const QString imagId)
{
    return m_impl->multiControl->login(accountName, pwd, graphCode, imagId);
}

QString HMultiControlWrapper::launchCalibration(int timeStep, bool isOnline)
{
    return m_impl->multiControl->launchCalibration(timeStep, isOnline);
}

QDir HMultiControlWrapper::getModelDir()
{
    return m_impl->multiControl->getModelDir();
}

QString HMultiControlWrapper::launchBlinkDetection(int algoType, QString modelName)
{
    return m_impl->multiControl->launchBlinkDetection(algoType, modelName);
}

void HMultiControlWrapper::stopBlinkDetection()
{
    m_impl->multiControl->stopBlinkDetection();
}

void HMultiControlWrapper::onSearchDeviceList()
{
    m_impl->multiControl->searchDeviceList();
}

BasicParameter HMultiControlWrapper::getParameter()
{
    return m_impl->multiControl->m_dataSystem->getParameter();
}

void HMultiControlWrapper::onEventDispatcher(hnnk::DataAppOperator type, QVariant val)
{
    return m_impl->multiControl->m_dataSystem->eventDispatcher(type, val);
}

void HMultiControlWrapper::onSetEpochInfo(int eegch, int eventch, int epochlen, int other)
{
    return m_impl->multiControl->m_dataSystem->setEpochInfo(eegch, eventch, epochlen, other);
}




