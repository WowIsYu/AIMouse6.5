#ifndef HMULTICONTROLWRAPPER_H
#define HMULTICONTROLWRAPPER_H

#include "HMultiControlSDK.h"
#include "dataset.h"
#include <QObject>
#include "hdatasystem_interface.h"

namespace hnnk {class HMultiControlSDK;}

class HMultiControlWrapper : public QObject
{
    Q_OBJECT
public:
    explicit HMultiControlWrapper(QObject *parent = nullptr);
    ~HMultiControlWrapper();

public:
    // 初始化
    void initial();

    //陀螺仪坐标回正
    void resetLocation();
    //连接设备
    void connectDevice(hnnk::DataAppOperator dataOperator, QString name);
    //设置陀螺仪坐标灵敏度
    void setSensitivity(int sensitivity);

    bool initEegDataCollectorEnv(hnnk::DSPROTOCOLTYPE type = hnnk::DATA_SECONDGENERAL, hnnk::DSNETTYPE netType = hnnk::NET_SYSBLUE);

    //获取图形验证码
    void getGraphValidateCode(QPixmap &lable, QString &imageId);
    //用户注册
    QStrErrMsg registAccounter(const QString accountName, const QString pwd,
                               const QString graphCode, const QString imagId);
    //用户登录
    QString login(const QString accountName, const QString pwd,
                  const QString graphCode, const QString imagId);

    //启动眨眼校准
    QString launchCalibration(int timeStep, bool isOnline);
    //获取眨眼检测算法用户模型所在目录
    QDir getModelDir();
    //启动算法检测
    QString launchBlinkDetection(int algoType, QString modelName ="");
    //停止算法检测
    void stopBlinkDetection();
    /**
     * @brief getParameter 获取本地保存的设备基本信息, 调用该函数前发起SPO_SELECTINFO 调用
     * @return 本地保存的设备基本信息
     */
    hnnk::BasicParameter getParameter();


public slots:
    void onEventDispatcher(hnnk::DataAppOperator type, QVariant val);

    void onSetEpochInfo(int eegch, int eventch, int epochlen, int other = 0);
    //搜索设备
    void onSearchDeviceList();


private:
    class Impl;
    Impl *m_impl;

signals:
    //SDK事件:搜索到的蓝牙设备名称
    void notifyDeviceNameUpdate(QString);

    void emitSearchNetDeviceOver();

    void emitMsgBox(int type, QString msg);
    //SDK事件:获取陀螺仪坐标值
    void emitGyroData(double x,double y);
    //SDK事件:获取眨眼检测计算结果
    void notifyBlinkDetectionResult(int);
    //SDK事件:获取注意力检测计算结果
    void notifyAttenDetectionResult(double);
    //SDK事件:设备连接状态发生改变
    void notifyConnectState(int state);
    //SDK事件:获取眨眼校准分数
    void notifyCalibrationResult(bool, float score);
    //SDK事件:校准标识触发信号
    void notifyCaliTrigger();

    void emitEvent(QVector<hnnk::EegDataChan> eogVec);
    void emitChsAndSampRate(int chs, int srate);
    void emitAddtionData(QVector<hnnk::GYRODATA> gyroDatas, QVector<unsigned char> channoff, double battery);
    void emitUpdateAmpTestInfo(hnnk::AmpTestInfo);        //自检返回结果
    void emitConnectChange(hnnk::CONNECTUPDATE);
    void emitEdfData(QVector<hnnk::DataPoint> &, QVariant &, int);

};

#endif // HMULTICONTROLWRAPPER_H
