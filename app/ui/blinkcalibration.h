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
    explicit BlinkCalibration(QWidget *parent = nullptr, HMultiControlSDK *m_multiControl = nullptr);
    ~BlinkCalibration();
private slots:
    void onCaliTrigger();
    void onCalibrationResult(bool isOk, float score);
    void on_beginCaliButton_clicked();

public slots:
    void onConnectChange(int state);
    //眨眼检测结果
    void onBlinkCheckResult(int);
private:
    Ui::BlinkCalibration *ui;
signals:
    void sendToStatusBar(QString message);
public:
    //多模态综合控制SDK
    HMultiControlSDK *m_multiControl = nullptr;

};

#endif // BLINKCALIBRATION_H
