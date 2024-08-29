/********************************************************************************
** Form generated from reading UI file 'blinkdetection.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLINKDETECTION_H
#define UI_BLINKDETECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BlinkDetection
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *m_tabCalib;
    QFrame *frame_calibmain;
    QFrame *line;
    QPushButton *m_pbstart;
    QFrame *frame_calib_top;
    QLineEdit *lineEdit_calib;
    QLabel *label_calibtime;
    QRadioButton *rb_localCalibration;
    QRadioButton *rb_onLineCalibration;
    QFrame *frame_calibmidle;
    QLabel *label_calibcolour;
    QLabel *label_calibscor;
    QWidget *m_tabBlink;
    QFrame *frame_blink;
    QLabel *label_blink;
    QFrame *line_blink;
    QPushButton *m_pbBlinkStart;
    QPushButton *m_pbBlinkStop;
    QLineEdit *lineEdit_modelname;
    QRadioButton *rb_usermode;
    QRadioButton *rb_commonmode;
    QLabel *blinktimes;

    void setupUi(QWidget *BlinkDetection)
    {
        if (BlinkDetection->objectName().isEmpty())
            BlinkDetection->setObjectName("BlinkDetection");
        BlinkDetection->resize(795, 566);
        gridLayout = new QGridLayout(BlinkDetection);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(BlinkDetection);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setTabBarAutoHide(false);
        m_tabCalib = new QWidget();
        m_tabCalib->setObjectName("m_tabCalib");
        frame_calibmain = new QFrame(m_tabCalib);
        frame_calibmain->setObjectName("frame_calibmain");
        frame_calibmain->setGeometry(QRect(260, 10, 251, 371));
        frame_calibmain->setFrameShape(QFrame::Box);
        frame_calibmain->setFrameShadow(QFrame::Raised);
        line = new QFrame(frame_calibmain);
        line->setObjectName("line");
        line->setGeometry(QRect(10, 300, 221, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        m_pbstart = new QPushButton(frame_calibmain);
        m_pbstart->setObjectName("m_pbstart");
        m_pbstart->setGeometry(QRect(80, 330, 80, 24));
        frame_calib_top = new QFrame(frame_calibmain);
        frame_calib_top->setObjectName("frame_calib_top");
        frame_calib_top->setGeometry(QRect(0, 0, 251, 71));
        frame_calib_top->setFrameShape(QFrame::NoFrame);
        frame_calib_top->setFrameShadow(QFrame::Raised);
        lineEdit_calib = new QLineEdit(frame_calib_top);
        lineEdit_calib->setObjectName("lineEdit_calib");
        lineEdit_calib->setGeometry(QRect(110, 10, 113, 23));
        label_calibtime = new QLabel(frame_calib_top);
        label_calibtime->setObjectName("label_calibtime");
        label_calibtime->setGeometry(QRect(10, 10, 91, 16));
        rb_localCalibration = new QRadioButton(frame_calib_top);
        rb_localCalibration->setObjectName("rb_localCalibration");
        rb_localCalibration->setGeometry(QRect(10, 40, 97, 22));
        rb_onLineCalibration = new QRadioButton(frame_calib_top);
        rb_onLineCalibration->setObjectName("rb_onLineCalibration");
        rb_onLineCalibration->setGeometry(QRect(140, 40, 97, 22));
        frame_calibmidle = new QFrame(frame_calibmain);
        frame_calibmidle->setObjectName("frame_calibmidle");
        frame_calibmidle->setGeometry(QRect(0, 90, 251, 151));
        frame_calibmidle->setFrameShape(QFrame::NoFrame);
        frame_calibmidle->setFrameShadow(QFrame::Raised);
        label_calibcolour = new QLabel(frame_calibmidle);
        label_calibcolour->setObjectName("label_calibcolour");
        label_calibcolour->setGeometry(QRect(50, 30, 141, 91));
        label_calibcolour->setAlignment(Qt::AlignCenter);
        label_calibscor = new QLabel(frame_calibmain);
        label_calibscor->setObjectName("label_calibscor");
        label_calibscor->setGeometry(QRect(70, 250, 71, 41));
        label_calibscor->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(m_tabCalib, QString());
        m_tabBlink = new QWidget();
        m_tabBlink->setObjectName("m_tabBlink");
        frame_blink = new QFrame(m_tabBlink);
        frame_blink->setObjectName("frame_blink");
        frame_blink->setGeometry(QRect(250, 20, 281, 331));
        frame_blink->setFrameShape(QFrame::Box);
        frame_blink->setFrameShadow(QFrame::Raised);
        label_blink = new QLabel(frame_blink);
        label_blink->setObjectName("label_blink");
        label_blink->setGeometry(QRect(80, 90, 111, 81));
        label_blink->setAlignment(Qt::AlignCenter);
        line_blink = new QFrame(frame_blink);
        line_blink->setObjectName("line_blink");
        line_blink->setGeometry(QRect(10, 220, 261, 16));
        line_blink->setFrameShape(QFrame::HLine);
        line_blink->setFrameShadow(QFrame::Sunken);
        m_pbBlinkStart = new QPushButton(frame_blink);
        m_pbBlinkStart->setObjectName("m_pbBlinkStart");
        m_pbBlinkStart->setGeometry(QRect(30, 270, 80, 24));
        m_pbBlinkStop = new QPushButton(frame_blink);
        m_pbBlinkStop->setObjectName("m_pbBlinkStop");
        m_pbBlinkStop->setGeometry(QRect(160, 270, 80, 24));
        lineEdit_modelname = new QLineEdit(frame_blink);
        lineEdit_modelname->setObjectName("lineEdit_modelname");
        lineEdit_modelname->setGeometry(QRect(10, 10, 261, 23));
        rb_usermode = new QRadioButton(frame_blink);
        rb_usermode->setObjectName("rb_usermode");
        rb_usermode->setGeometry(QRect(30, 40, 97, 22));
        rb_commonmode = new QRadioButton(frame_blink);
        rb_commonmode->setObjectName("rb_commonmode");
        rb_commonmode->setGeometry(QRect(160, 40, 97, 22));
        blinktimes = new QLabel(frame_blink);
        blinktimes->setObjectName("blinktimes");
        blinktimes->setGeometry(QRect(90, 185, 101, 31));
        blinktimes->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(m_tabBlink, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(BlinkDetection);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(BlinkDetection);
    } // setupUi

    void retranslateUi(QWidget *BlinkDetection)
    {
        BlinkDetection->setWindowTitle(QCoreApplication::translate("BlinkDetection", "\347\234\250\347\234\274\346\243\200\346\265\213", nullptr));
        m_pbstart->setText(QCoreApplication::translate("BlinkDetection", "\345\274\200\345\247\213", nullptr));
        label_calibtime->setText(QCoreApplication::translate("BlinkDetection", "\347\234\250\347\234\274\351\227\264\351\232\224\346\227\266\351\227\264\357\274\232s", nullptr));
        rb_localCalibration->setText(QCoreApplication::translate("BlinkDetection", "\346\234\254\345\234\260\350\276\203\345\207\206", nullptr));
        rb_onLineCalibration->setText(QCoreApplication::translate("BlinkDetection", "\345\234\250\347\272\277\350\276\203\345\207\206", nullptr));
        label_calibcolour->setText(QCoreApplication::translate("BlinkDetection", "\347\273\277\350\211\262\346\230\257\347\234\250\347\234\274", nullptr));
        label_calibscor->setText(QCoreApplication::translate("BlinkDetection", "\345\210\206\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(m_tabCalib), QCoreApplication::translate("BlinkDetection", "calibration", nullptr));
        label_blink->setText(QCoreApplication::translate("BlinkDetection", "\347\273\277\350\211\262\346\230\257\347\234\250\347\234\274", nullptr));
        m_pbBlinkStart->setText(QCoreApplication::translate("BlinkDetection", "\345\274\200\345\247\213", nullptr));
        m_pbBlinkStop->setText(QCoreApplication::translate("BlinkDetection", "\347\273\223\346\235\237", nullptr));
        rb_usermode->setText(QCoreApplication::translate("BlinkDetection", "\347\224\250\346\210\267\346\250\241\345\236\213", nullptr));
        rb_commonmode->setText(QCoreApplication::translate("BlinkDetection", "\345\244\247\346\225\260\346\215\256\346\250\241\345\236\213", nullptr));
        blinktimes->setText(QCoreApplication::translate("BlinkDetection", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(m_tabBlink), QCoreApplication::translate("BlinkDetection", "blinkcheck", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BlinkDetection: public Ui_BlinkDetection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLINKDETECTION_H
