#include "hmulticontrolwrapper.h"
#include "HMultiControlSDK.h"

using namespace hnnk;
class HMultiControlWrapper::Impl {
public:
    hnnk::HMultiControlSDK *multiControl;
};


HMultiControlWrapper::HMultiControlWrapper(QObject *parent)
    : QObject(parent), m_impl(new Impl) {
    m_impl->multiControl = new hnnk::HMultiControlSDK(this);

    initial();

    this->m_dataSystem = m_impl->multiControl->m_dataSystem;

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

void HMultiControlWrapper::searchDeviceList()
{
    m_impl->multiControl->searchDeviceList();
}


