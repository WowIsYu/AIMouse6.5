#ifndef SETUP_H
#define SETUP_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include "HMultiControlSDK.h"
#include "qelapsedtimer.h"
#include "vmousemainwindow.h"
#include "Nagano.h"

#include <QWebEngineView>
using namespace hnnk;

namespace Ui {
class SetUp;
}

class SetUp : public QWidget
{
    Q_OBJECT

private slots:
    void onGyroData(double x, double y);
    void on_horizontalSlider_valueChanged(int value);
    void on_resetButton_clicked();
    void onBlinkDetectionResult(int val);
    void onAttenDetectionResult(double val);
    void on_beginButton_clicked(); // 启动检测
    void on_stopButton_clicked();   // 停止检测
    void on_pushButton_clicked();
    void onBlinkCheckResult(int);
    void on_btnSet_clicked();
    void on_btnInfo_clicked();
    void on_btnQuestion_clicked();
    void on_btnAbout_clicked();

signals:
    void attentionResult(double val);
    void sendToStatusBar(QString message);
    void updateDatabase();

public:
    explicit SetUp(QWidget *parent = nullptr, HMultiControlSDK *MultiObj = nullptr, VMouseMainWindow *main_vmouse = nullptr);
    void insertAttentionRecord(const QString &account, const QDateTime &startTime, const QDateTime &endTime,
                               qreal averageAttention, qreal minAttention, qreal maxAttention, qreal medianAttention);
    ~SetUp();

    void calculateAttentionStats();

private:
    HMultiControlSDK *m_multiControl = nullptr; // 多模态综合控制SDK
    VMouseMainWindow *main_vmouse = nullptr;    // 虚拟光标图标      
    Nagano *attentionShow;                // 注意力显示窗口

    QString getLastModelFile();                  // 获取最近生成的用户模型文件名
    QString m_modelName;                         // 最近生成的用户模型文件名称
    QPoint globalPos;                            // 鼠标全局位置
    double globalPosx;                           // 鼠标全局x坐标
    double globalPosy;                           // 鼠标全局y坐标

    // 需要存入的数据库值
    QDateTime startTime;                         // 注意力检测的开始时间
    QDateTime endTime;                           // 注意力检测的结束时间
    double averageAttention = 0;
    double minAttention = 0;
    double maxAttention = 0;
    double medianAttention = 0;
    QVector<double> attentionValues; // 存储注意力值


private:
    Ui::SetUp *ui;                               // UI指针
    QWebEngineView *m_webView;                   // 网页视图

    bool m_isDetecting = false;
    QElapsedTimer m_detectionTimer;
};

#endif // SETUP_H
