/********************************************************************************
** Form generated from reading UI file 'choosedevice.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEDEVICE_H
#define UI_CHOOSEDEVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseDevice
{
public:
    QGridLayout *gridLayout;
    QFrame *frame_background;
    QFrame *fram_funaptions;
    QPushButton *m_pbSearch;
    QPushButton *m_pbConnect;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_funView;

    void setupUi(QWidget *ChooseDevice)
    {
        if (ChooseDevice->objectName().isEmpty())
            ChooseDevice->setObjectName("ChooseDevice");
        ChooseDevice->resize(440, 425);
        ChooseDevice->setStyleSheet(QString::fromUtf8("#frame_background{\n"
"border-image:url(:/img/background-gg.jpg);\n"
"}\n"
"\n"
"#fram_funaptions{\n"
"	background-color:rgb(255, 255, 255)\n"
"}\n"
"\n"
"QPushButton{\n"
"    color:#ffffff;\n"
"    border: none;\n"
"    background-color:#8293fd;\n"
"    border-radius: 5px;\n"
"}"));
        gridLayout = new QGridLayout(ChooseDevice);
        gridLayout->setObjectName("gridLayout");
        frame_background = new QFrame(ChooseDevice);
        frame_background->setObjectName("frame_background");
        frame_background->setFrameShape(QFrame::StyledPanel);
        frame_background->setFrameShadow(QFrame::Raised);
        fram_funaptions = new QFrame(frame_background);
        fram_funaptions->setObjectName("fram_funaptions");
        fram_funaptions->setGeometry(QRect(10, 10, 141, 391));
        fram_funaptions->setStyleSheet(QString::fromUtf8(""));
        fram_funaptions->setFrameShape(QFrame::Box);
        fram_funaptions->setFrameShadow(QFrame::Sunken);
        fram_funaptions->setLineWidth(1);
        fram_funaptions->setMidLineWidth(0);
        m_pbSearch = new QPushButton(fram_funaptions);
        m_pbSearch->setObjectName("m_pbSearch");
        m_pbSearch->setGeometry(QRect(20, 100, 80, 51));
        m_pbConnect = new QPushButton(fram_funaptions);
        m_pbConnect->setObjectName("m_pbConnect");
        m_pbConnect->setGeometry(QRect(20, 220, 80, 51));
        layoutWidget = new QWidget(frame_background);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(180, 10, 241, 391));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        frame_funView = new QFrame(layoutWidget);
        frame_funView->setObjectName("frame_funView");
        frame_funView->setFrameShape(QFrame::StyledPanel);
        frame_funView->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame_funView);


        gridLayout->addWidget(frame_background, 0, 0, 1, 1);


        retranslateUi(ChooseDevice);

        QMetaObject::connectSlotsByName(ChooseDevice);
    } // setupUi

    void retranslateUi(QWidget *ChooseDevice)
    {
        ChooseDevice->setWindowTitle(QCoreApplication::translate("ChooseDevice", "\351\200\211\346\213\251\350\256\276\345\244\207", nullptr));
        m_pbSearch->setText(QCoreApplication::translate("ChooseDevice", "\346\220\234\347\264\242\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        m_pbConnect->setText(QCoreApplication::translate("ChooseDevice", "\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseDevice: public Ui_ChooseDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEDEVICE_H
