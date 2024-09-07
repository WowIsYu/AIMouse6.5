#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QMenuBar>
#include <vector>

#include "choosedevice.h"
#include "markingtester.h"


#include <HMultiControlSDK/include/hdatasystem_interface.h>
#include "HMultiControlSDK/include/dataset.h"

#include "qcustomplot.h"

using namespace hnnk;

namespace Ui {
class Waveform;
}

enum UsingState           ///三种使用方式，不记录（仅可视化波形）、记录、读取文件
{
    STATE_NOT_RECORD,
    STATE_RECORD,
    STATE_READ
};

class Waveform : public QWidget
{
    Q_OBJECT

public:
    explicit Waveform(QWidget *parent = nullptr);
    ~Waveform();
    /**
     * @brief setupPlotEdfChan 绘制edf通道波形
     * @param customPlot
     */
    void setupPlotEdfChan(QCustomPlot *customPlot);
    /**
     * @brief lauchCollector 初始化数据采集环境，选择协议
     * @param index1 参数1是数据协议类型
     * @param index2 参数2是通信协议类型
     */
    void lauchCollector(int index1,int index2);
private slots:
    /******************************************************
 * 界面控件响应函数
 * ****************************************************/
    /**
     * @brief on_action_Add_Event_triggered 触发弹出打标窗口
     */
    void on_action_Add_Event_triggered();

    /**
     * @brief on_action_Start_Acquisition_triggered 开始读取脑电数据
     */
    void on_action_Start_Acquisition_triggered();

    /**
     * @brief on_action_Stop_Acquisition_triggered 停止脑电数据
     */
    void on_action_Stop_Acquisition_triggered();

    /**
     * @brief on_action_Open_triggered 读取静态edf文件
     */
    void on_action_Open_triggered();

    /**
     * @brief on_action_Record_triggered 记录edf文件
     */
    void on_action_Start_Record_triggered();

    /**
     * @brief plotEvent 绘制标记
     * @param key
     * @param evtNumber 标记值
     */
    void plotEvent(double key,int evtNumber);


    /**
     * @brief onDeviceName 修改蓝牙名称
     * @param name 新的蓝牙名称
     */
    void onModifyDeviceName(QString name);

    /**
     * @brief onDealManualMarking 手动打标
     * @param markVal 标值
     */
    void onDealManualMarking(int markVal);

    void onMsg(int type, QString msg);
public:
    QString m_edfWritePath;   ///edf文件写入路径
    QVector<QVector<int>> m_plotColor = {{255,0,0},{255,165,0},{255,255,0},{0,255,0},{0,0,255},
                                         {30/2,144/2,255/2}, {50/2,205/2,50/2}, {255/2,0,255/2},
                                         {238/2,44/2,44/2},  {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}, {255/2,255/2,255/2},
                                         {255/2,255/2,255/2}, {255/2,255/2,255/2}};

    double m_timeCur = 0;
    double m_lastPointKey = 0;
    double m_rangeRight = 8;
signals:
    /**
     * @brief popSetWindows 弹出参数设置窗口
     * @param QString  设备名
     */
    void popSetWindows(QString);

public slots:
    void onPopMsgBox(int type, QString msg);

    /**
     * @brief onReciveEegData 接收脑电数据
     * @param eegVec  脑电数据
     */
    void onReciveEegData(QVector<hnnk::EegDataChan> eegVec);

    /**
     * @brief onDeviceChannelAndSampRate 通道及采样率信息
     * @param chs 通道数
     * @param srate 采集率
     */
    void onDeviceChannelAndSampRate(int chs, int srate);

    /**
     * @brief onAddtionData  附加数据，陀螺仪，通道状态数据，电量数据
     * @param gyroDatas  陀螺仪
     * @param channoff  通道状态数据
     * @param battery  电量数据
     */
    void onAddtionData(QVector<GYRODATA> gyroDatas, QVector<unsigned char>channoff, double battery);

    /**
     * @brief deviceActive 搜索到的设备名信息：名称由两部分组成：name:mac
     * @param devices
     */
    void onDeviceNameUpdate(QString devices);

    /**
     * @brief onConnectUpdate 设备连接状态
     */
    void onConnectUpdate(CONNECTUPDATE);

    /**
     * @brief onUpdateSelfCheckInfo 一键诊断返回信息
     * @note 更新通道号及采样频率信息显示在界面
     */
    void onUpdateSelfCheckInfo(AmpTestInfo);

    /**
     * @brief onChooseBlueEvent 蓝牙选择
     */
    void onChooseBlueEvent(hnnk::DataAppOperator type, QString name);

    /**
     * @brief readEdfDataToDouble 读取静态edf文件数据
     * @param dVecs 数据长度
     * @return
     */
    void  onReadEdfDataToDouble(QVector<hnnk::DataPoint> &dVecs, QVariant &otherData, int ch);

    /**
     * @brief onSearchOver
     */
    void onSearchOver();


private:
    /**
     * @brief realtimeDataSlotChan  实时数据渲染
     */
    void realtimeDataSlotChan(std::vector<double>&, int, int, int);


    void realtimeDataSlotChanEdf(std::vector<double>& tmp, int freq, int ch, int chNum, int pntNum);
    /**
     * @brief dealTestMarking 处理来自markingtester的打标信号
     */
    void dealTestMarking(int,int,int);

    /**
     * @brief checkSelf 发起自检请求
     */
    void checkSelf();

    void dealConnectSuccess();

    /**
     * @brief onTestEpoch 测试epoch数据
     */
    void onTestEpoch();

    void clearScreen();

public:
    ChooseDevice *m_pchooseWindow;          ///设备选择窗口

private:

    bool m_isSmoothing;                     ///是否要限波
    int m_state;                            ///连接状态
    int m_dataProtoclType;                  ///数据协议类型
    int m_markVal;                          ///打标值
    int m_connectSuccessful = 0;            ///判断是否连接成功标志
    double m_rightBound;                    ///显示波形时坐标上界
    int m_lastCh;                           ///上一次的通道号
    /***************************
     * 窗体控件
     * *************************/
    Ui::Waveform *ui;
    QLabel * m_chAndRateInfo;              ///通道数和采样率信息
    QLabel* m_dataLost1;
    QLabel* m_dataLost2;
    QLabel* m_dataLost3;
    QLabel* m_dataTime;
    QLabel* m_pdataGyro;                   ///陀螺仪数据
    QMenu * fileMenu;                      ///文件菜单
    QLabel* m_deviceVoltage;               ///设备电压
    QHBoxLayout m_hLayout;                 ///水平布局控件
    QVBoxLayout m_vLayout;                 ///垂直布局控件
    QListView * m_view;
    QLineEdit * m_edit;

    /**
     * @brief 本地配置信息
     */
    struct LocalConf{
        QString m_deviceName;               ///设备名称
        long m_samp;                        ///采样率
        long m_channels;                    ///通道数
        long m_block;                       ///采样点
        long m_refComputer;                 ///当前计算参数
    };

    LocalConf m_localConf;                  ///读取本地配置文件
    hnnk::GYRODATA m_gyroData;              ///陀螺仪数据
    QPushButton *m_trapFilter;              ///陷波开关
    //InitDataSystemProtocol *m_iniEnv;       ///初始化协议窗口
    MarkingTester *m_pMarkingTester;        ///测试打标窗口
    QMenuBar *m_meneBar;                    ///菜单选择
    hnnk::HDataSystem_interface *m_dataSystemSDK;      ///数据采集SDK实例
};

#endif // WAVEFORM_H
