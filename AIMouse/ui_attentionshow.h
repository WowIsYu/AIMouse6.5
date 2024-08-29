/********************************************************************************
** Form generated from reading UI file 'attentionshow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTENTIONSHOW_H
#define UI_ATTENTIONSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AttentionShow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLCDNumber *lcdNumber;

    void setupUi(QMainWindow *AttentionShow)
    {
        if (AttentionShow->objectName().isEmpty())
            AttentionShow->setObjectName("AttentionShow");
        AttentionShow->resize(198, 59);
        centralwidget = new QWidget(AttentionShow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\347\220\245\347\217\200")});
        font.setPointSize(16);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setDigitCount(5);

        gridLayout->addWidget(lcdNumber, 0, 1, 1, 1);

        AttentionShow->setCentralWidget(centralwidget);

        retranslateUi(AttentionShow);

        QMetaObject::connectSlotsByName(AttentionShow);
    } // setupUi

    void retranslateUi(QMainWindow *AttentionShow)
    {
        AttentionShow->setWindowTitle(QCoreApplication::translate("AttentionShow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("AttentionShow", "\346\263\250\346\204\217\345\212\233\345\200\274\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AttentionShow: public Ui_AttentionShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTENTIONSHOW_H
