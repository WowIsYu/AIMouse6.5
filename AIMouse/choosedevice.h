#ifndef CHOOSEDEVICE_H
#define CHOOSEDEVICE_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QButtonGroup>
#include <QVBoxLayout>
#include "HMultiControlSDK/include/dataset.h"
#include <QTableWidget>
#include <QLabel>
#include <QTextEdit>

typedef struct{
    int id;
    QString SerialPortName;     ///串口名称
} MyDeviceInfo;

namespace Ui {
class ChooseDevice;
}

class ChooseDevice : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseDevice(QWidget *parent = nullptr);
    ~ChooseDevice();
    void showTopwindow();

    /**
     * @brief clear  清空列表
     */
    void clear();

    /**
     * @brief updateDeviceNameList  更新设备名称列表。该接口会
     * @param devs  设备名
     * @param historyName   上一次使用的设备名
     */
    void updateDeviceNameList(QString name);

    /**
     * @brief getLastDeviceName 获取最近一次的设备名
     * @return   设备名
     */
    QString getLastDeviceName();

    /**
     * @brief searchOver    查询结束
     */
    void searchOver();
    void connectUpdate(hnnk::CONNECTUPDATE conVal);
    void setBluetoothEnable(bool flag);
    void setFlashText(QString name);
    void tabChanged(int tabIndex);
    void deviceChannels(int chs, int rate);
protected:
    void closeEvent(QCloseEvent *event);
    void setTableWidgetViwe(QStringList nameList);
public slots:

    /**
     * @brief sendCheckSignal 发送确认信号
     */
    //void sendCheckSignal();

    //void radioClick();

signals:
    /**
     * @brief checkSignal 确认信号
     * @param name  蓝牙名称
     */
    void checkSignal(hnnk::DataAppOperator, QString name);

    /**
     * @brief refreshList 刷新列表
     */
    void refreshList();

private slots:
    /**
     * @brief on_flushButton_clicked 主界面的搜索蓝牙按钮被点击
     */
    //void on_flushButton_clicked();


    void on_m_pbSearch_clicked();

    void on_m_pbConnect_clicked();

private:
    bool m_isBluetoothEnable;
    int m_flagWho;
    Ui::ChooseDevice *ui;
    QString m_latestName;       ///最新选中的设备名
    QVBoxLayout m_Vylout;       ///垂直布局控件
    //QList<MyDeviceInfo> m_serialport = {{1,"串口1"},{2,"串口2"},{3,"串口3"},{4,"串口4"},{5,"串口5"}};

    QTableWidget *m_deviceList;     //类表格
    QTextEdit *m_textEdit;
    QStringList m_names;            //设备名称
    QLabel *m_conText;          //显示是否连接成功
    int m_lastTabIndex;
    bool m_isCon;               //判断是否连接成功
};

#endif // CHOOSEDEVICE_H
