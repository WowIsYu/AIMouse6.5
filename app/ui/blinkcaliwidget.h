#ifndef BLINKCALIWIDGET_H
#define BLINKCALIWIDGET_H

#include <QWidget>

namespace Ui {
class BlinkCaliWidget;
}

class BlinkCaliWidget: public QWidget
{
    Q_OBJECT

public:
    explicit BlinkCaliWidget(QWidget *parent = nullptr);
    ~BlinkCaliWidget();
public slots:
    void onCaliTrigger();
    void onCalibrationResult(bool isOk, float score);
    void on_beginCaliButton_clicked();
private:
    Ui::BlinkCaliWidget *ui;
signals:
    void emitLaunchCali(int blinkInterval);

};

#endif // BLINKCALIWIDGET_H
