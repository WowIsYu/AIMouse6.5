#ifndef HBLINKCHECK_INTERFACE_H
#define HBLINKCHECK_INTERFACE_H


#include <QObject>
#include <QMetaType>
#include <QtCore/qglobal.h>
#include <QDir>
#include <QMap>
#include <QVariant>
#include "HDataSystem/dataset.h"


#if defined(HBLINKDETECTION_LIBRARY)
#define HBLINKCHECK_EXPORT Q_DECL_EXPORT
#else
#define HBLINKCHECK_EXPORT Q_DECL_IMPORT
#endif
/*
 * 眨眼检测模块，该模块完成眼电数据的分析，分析算法有大数据模型和用户模型。
 * 使用步骤：
 * 1 使用眨眼检测功能之前需要注册、登录。
 * 2 眨眼模型标定
 *    1> 指定眼电数据保存路径
 *    2> 指定模型存放路径
 * 3 选择算法模型（初始化时指定）
 *    通过模型标定过中的返回值（分数）用户自己决定需要什么算法，一般 60分以上可以考虑用户模型，否则建议大数据模型
 * 4 初始化成功后启动眨眼检测
 * 5 不需要检测时退出眨眼检测
 */
#define QStrErrMsg  QString

namespace hnnk
{
class HBLINKCHECK_EXPORT HBlinkDetection : public QObject
{
    Q_OBJECT
public:
    explicit HBlinkDetection(QObject *parent = nullptr);
    virtual ~HBlinkDetection();
    //获取图形验证码,登录和注册都需要使用验证码
    void getGraphCode();

    //用户注册
    void reg(const QString account, const QString password,
             const QString captcha, const QString captchaId);

    //用户登录
    void login(const QString account, const QString password,
               const QString captcha, const QString captchaId);

    //适配模型，该接口需要花5秒左右的时间才会返回
    double readCalibrationScore(QString path, QString &msg);

    //初始化眨眼检测
    void initBlinkDetection( DSPROTOCOLTYPE type, DSNETTYPE netType);

    //启动眨眼检测
    bool launchBlinkDetection(int algoType, QString modelName ="");

    //停止眨眼检测
    void stopBlinkDetection();

    //启动较准
    QString launchCalibration(int timeStep, bool isOnline);

    //停止校准,非大数据模型在使用眨眼前需要先做模型训练，以标定模型，与lauchCalibration 函数相对应
    void stopCalibration();

    //查询设备
    void searchDevice();

    //连接设备
    void connectDevice(QString name);

    //请求设备信息
    void requestDeviceBasicInfo();

    //启动数据采集
    void startAcquisition();

    //停止数据采集
    void stopAcquisition();

    //设置license,在调用在线算法时必须使用这个license
    void setLicense(QString lincese);

    //获取模型所在目录
    QDir getModelDir();
signals:
    //通知结果1 眨眼， 0未眨眼
    void notifyBlinkDetectionResult(int);
    //错误通知消息
    void notifyErrorMsg(QString);
    //通知查询设备结束
    void notifySearchDeviceOver();
    //通知读取通道号和采样率
    void notifyChsAndSampRate(int chs, int srate);      //接收通道信息
    //通知较准结果
    void notifyCalibrationResult(bool, float score);
    void notifyCaliTrigger();
    //更新设备名称
    void notifyDeviceName(QString);
    //更新连接状态
    void notifyConnectChange(hnnk::CONNECTUPDATE);
    //云平台事件：获取图形码
    void notifyGraphEvent(QMap<QString, QVariant>);
    //云平台事件：注册
    void notifyRegisterEvent(QMap<QString, QVariant>);
    //云平台事件：登录
    void notifyLoginEvent(QMap<QString, QVariant>);
private:
    class BlinkDetectionManager;
    BlinkDetectionManager *m_bcManager;
};
}//hnnk
#endif // HBLINKCHECK_INTERFACE_H
