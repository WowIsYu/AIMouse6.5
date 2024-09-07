#ifndef BLINKCALIBRATION_H
#define BLINKCALIBRATION_H

#include <QWidget>
#include "HMultiControlSDK.h"
#include "choosedevice.h"

using namespace hnnk;

namespace Ui {
class BlinkCalibration;
}

class BlinkCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit BlinkCalibration(QWidget *parent = nullptr);
    ~BlinkCalibration();
private slots:
    void onCaliTrigger();
    void onCalibrationResult(bool isOk, float score);
    void on_beginCaliButton_clicked();

public slots:
    void onChooseBlueEvent(hnnk::DataAppOperator type, QString name);
    void initBlinkCali();
    void onConnectChange(int state);
    //眨眼检测结果
    void onBlinkCheckResult(int);
private:
    Ui::BlinkCalibration *ui;
public:
    //多模态综合控制SDK
    HMultiControlSDK *m_multiControl;
    //搜索设备窗口
    ChooseDevice *m_pchooseWindow;

};

#endif // BLINKCALIBRATION_H
