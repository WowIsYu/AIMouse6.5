#ifndef SETUP_H
#define SETUP_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include "HMultiControlSDK.h"
#include "vmousemainwindow.h"
#include "attentionshow.h"
using namespace hnnk;


namespace Ui {
class SetUp;
}

class SetUp : public QWidget
{
    Q_OBJECT
public slots:
    void initSetUp(HMultiControlSDK *MultiObj);
private slots:
    void onGyroData(double x, double y);
    void on_horizontalSlider_valueChanged(int value);

    void on_resetButton_clicked();

    void onBlinkDetectionResult(int val);
    void onAttenDetectionResult(double val);
    void on_beginButton_clicked();

    void on_stopButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void attentionResult(double val);

public:
    explicit SetUp(QWidget *parent = nullptr);
    ~SetUp();
    //多模态综合控制SDK
    HMultiControlSDK *m_multiControl;
    //虚拟光标图标
    VMouseMainWindow *main_vmouse;
    //搜索设备窗口
    // ChooseDevice *m_pchooseWindow;
    //获取最近生成的用户模型文件
    QString getLastModelFile();
    //最近生成的用户模型文件名称
    QString m_modelName;
    AttentionShow *attentionShow;

    QPoint globalPos;
private:
    Ui::SetUp *ui;

};

#endif // SETUP_H
