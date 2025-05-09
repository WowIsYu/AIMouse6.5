#ifndef BLINKCALIBRATION_H
#define BLINKCALIBRATION_H

#include <QWidget>

namespace Ui {
class BlinkCalibration;
}

class BlinkCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit BlinkCalibration(QWidget *parent = nullptr);
    ~BlinkCalibration();
public slots:
    void onCaliTrigger();
    void onCalibrationResult(bool isOk, float score);
    void on_beginCaliButton_clicked();
private:
    Ui::BlinkCalibration *ui;
signals:
    void emitLaunchCali(int blinkInterval);

};

#endif // BLINKCALIBRATION_H
