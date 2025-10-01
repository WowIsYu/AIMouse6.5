#ifndef COLORSWITCHING_H
#define COLORSWITCHING_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QStyle>

class ColorSwitching : public QObject
{
    Q_OBJECT
public:
    ColorSwitching();
    //基于定时器的自动变化方案
    void doFlicker(QLabel *pLabel, int timerInter, int times);
    void doColorSwitching(QLabel *pLabel);
    void stopFlicker();
signals:
    void notifySwitch();
    void notifySwitchStop();
public slots:
    void onTimerOut();
private:
    //QColor m_color;
    QTimer m_timer;     //变绿色定时器
    QTimer m_timerSrc;      //变回灰色定时器
    QLabel *m_pLabel;
    int m_times;
    bool m_firstTime;       //第一次打标，不用闪烁。
};

#endif // COLORSWITCHING_H
