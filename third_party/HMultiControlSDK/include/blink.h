#ifndef BLINK_H
#define BLINK_H

#include "blink/blink_global.h"
#include <QVector>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
class BLINK_EXPORT Blink
{
public:
    Blink();
     void blink_pre(QVector<double> signalWave,int &jump,int &count,int &on_1or_2and3,int &m_nResult,int stop_one,int stop_two);
     void blink_one(QVector<double> signalWave,double netclasoutput,double &valueMax1,double &valueMin1,int &m_nResult,int &count,int &EogRemove,int &jump,int &on_1or_2and3);
};

#endif // BLINK_H
