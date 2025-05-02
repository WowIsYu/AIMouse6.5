#include "colorswitching.h"
#include "qdebug.h"
#include <QThread>

ColorSwitching::ColorSwitching()
{
    m_firstTime = false;
}

void ColorSwitching::stopFlicker()
{
    if(m_timer.isActive()){
        m_timer.stop();
    }
}

void ColorSwitching::doFlicker(QLabel *pLabel, int timerInter, int times)
{
    if(m_timer.isActive()){
        m_timer.stop();
    }

    m_times = times;
    m_pLabel = pLabel;
    m_pLabel->setStyleSheet("QLabel{background-color:rgb(0, 255, 255)}");        //灰色
    m_timer.setInterval(timerInter);
    m_timer.start();
    connect(&m_timer, &QTimer::timeout, this, &ColorSwitching::onTimerOut, Qt::UniqueConnection);

}

void ColorSwitching::onTimerOut()
{
    if(m_times-- <= 0){
        m_timer.stop();
        emit notifySwitchStop();
    }else{
        qDebug()<<"ColorSwitching::onTimerOut() "<<m_times;
        m_pLabel->setStyleSheet("QLabel{background-color:rgb(0, 255, 0)}");        //绿色
        m_timerSrc.start(600);      //600毫秒
        connect(&m_timerSrc, &QTimer::timeout, this, [this](){
            this->m_pLabel->setStyleSheet("QLabel{background-color:rgb(0, 255, 255)}");
            this->m_timerSrc.stop();
        });
    }
}


void ColorSwitching::doColorSwitching(QLabel *pLabel)
{
    m_pLabel = pLabel;
    m_pLabel->setStyleSheet("QLabel{background-color:rgb(0, 255, 0)}");
    //m_timerSrc.start(600);      //600毫秒
    connect(&m_timerSrc, &QTimer::timeout, this, [this](){
        this->m_pLabel->setStyleSheet("QLabel{background-color:rgb(0, 255, 255)}");
        this->m_timerSrc.stop();
    });
    m_timerSrc.start(600);      //600毫秒
}
