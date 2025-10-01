/********************************************************************************
** Form generated from reading UI file 'waveform.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAVEFORM_H
#define UI_WAVEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Waveform
{
public:
    QAction *action_Open;
    QAction *action_Add_Event;
    QAction *action_Start_Acquisition;
    QAction *action_Stop_Acquisition;
    QAction *action_Start_Record;
    QAction *action_bluetooth;
    QGridLayout *gridLayout;
    QToolBar *toolBar;
    QFrame *frame;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QLabel *connectstate;
    QScrollBar *horizontalScrollBar_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QCustomPlot *customPlot;
    QScrollBar *horizontalScrollBar;

    void setupUi(QWidget *Waveform)
    {
        if (Waveform->objectName().isEmpty())
            Waveform->setObjectName("Waveform");
        Waveform->resize(781, 552);
        Waveform->setStyleSheet(QString::fromUtf8(""));
        action_Open = new QAction(Waveform);
        action_Open->setObjectName("action_Open");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/icons8-opened-folder-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon);
        action_Open->setMenuRole(QAction::TextHeuristicRole);
        action_Add_Event = new QAction(Waveform);
        action_Add_Event->setObjectName("action_Add_Event");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/icons8-finish-flag-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Add_Event->setIcon(icon1);
        action_Add_Event->setMenuRole(QAction::TextHeuristicRole);
        action_Start_Acquisition = new QAction(Waveform);
        action_Start_Acquisition->setObjectName("action_Start_Acquisition");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/icons8-play-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Start_Acquisition->setIcon(icon2);
        action_Start_Acquisition->setMenuRole(QAction::TextHeuristicRole);
        action_Stop_Acquisition = new QAction(Waveform);
        action_Stop_Acquisition->setObjectName("action_Stop_Acquisition");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/icons8-stop-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Stop_Acquisition->setIcon(icon3);
        action_Stop_Acquisition->setMenuRole(QAction::TextHeuristicRole);
        action_Start_Record = new QAction(Waveform);
        action_Start_Record->setObjectName("action_Start_Record");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/icons8-record-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Start_Record->setIcon(icon4);
        action_Start_Record->setMenuRole(QAction::TextHeuristicRole);
        action_bluetooth = new QAction(Waveform);
        action_bluetooth->setObjectName("action_bluetooth");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/ic_usb_bluetooth.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_bluetooth->setIcon(icon5);
        action_bluetooth->setMenuRole(QAction::TextHeuristicRole);
        gridLayout = new QGridLayout(Waveform);
        gridLayout->setObjectName("gridLayout");
        toolBar = new QToolBar(Waveform);
        toolBar->setObjectName("toolBar");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy);
        toolBar->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background-color: rgb(228, 228, 228);  /* \350\256\276\347\275\256\350\203\214\346\231\257\350\211\262\344\270\272\347\201\260\350\211\262 */\n"
"}"));
        toolBar->setOrientation(Qt::Horizontal);
        toolBar->setIconSize(QSize(25, 25));
        toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

        gridLayout->addWidget(toolBar, 0, 0, 1, 1);

        frame = new QFrame(Waveform);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget_2 = new QWidget(frame);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 440, 771, 51));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        connectstate = new QLabel(layoutWidget_2);
        connectstate->setObjectName("connectstate");

        verticalLayout->addWidget(connectstate);

        horizontalScrollBar_2 = new QScrollBar(layoutWidget_2);
        horizontalScrollBar_2->setObjectName("horizontalScrollBar_2");
        horizontalScrollBar_2->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalScrollBar_2);

        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 10, 761, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        customPlot = new QCustomPlot(frame);
        customPlot->setObjectName("customPlot");
        customPlot->setEnabled(true);
        customPlot->setGeometry(QRect(0, 40, 761, 391));
        horizontalScrollBar = new QScrollBar(customPlot);
        horizontalScrollBar->setObjectName("horizontalScrollBar");
        horizontalScrollBar->setGeometry(QRect(0, 420, 791, 16));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(frame, 1, 0, 1, 1);


        toolBar->addAction(action_Open);
        toolBar->addAction(action_Add_Event);
        toolBar->addAction(action_Start_Acquisition);
        toolBar->addAction(action_Stop_Acquisition);
        toolBar->addAction(action_Start_Record);
        toolBar->addAction(action_bluetooth);

        retranslateUi(Waveform);

        QMetaObject::connectSlotsByName(Waveform);
    } // setupUi

    void retranslateUi(QWidget *Waveform)
    {
        Waveform->setWindowTitle(QCoreApplication::translate("Waveform", "\346\263\242\345\275\242\347\225\214\351\235\242", nullptr));
        action_Open->setText(QCoreApplication::translate("Waveform", "open", nullptr));
#if QT_CONFIG(tooltip)
        action_Open->setToolTip(QCoreApplication::translate("Waveform", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_Open->setShortcut(QCoreApplication::translate("Waveform", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Add_Event->setText(QCoreApplication::translate("Waveform", "add_event", nullptr));
#if QT_CONFIG(tooltip)
        action_Add_Event->setToolTip(QCoreApplication::translate("Waveform", "\347\202\271\346\255\244\346\265\213\350\257\225\346\211\223\346\240\207", nullptr));
#endif // QT_CONFIG(tooltip)
        action_Start_Acquisition->setText(QCoreApplication::translate("Waveform", "start_Acquisition", nullptr));
#if QT_CONFIG(tooltip)
        action_Start_Acquisition->setToolTip(QCoreApplication::translate("Waveform", "\345\274\200\345\247\213", nullptr));
#endif // QT_CONFIG(tooltip)
        action_Stop_Acquisition->setText(QCoreApplication::translate("Waveform", "stop_Acquisition", nullptr));
#if QT_CONFIG(tooltip)
        action_Stop_Acquisition->setToolTip(QCoreApplication::translate("Waveform", "\345\201\234\346\255\242", nullptr));
#endif // QT_CONFIG(tooltip)
        action_Start_Record->setText(QCoreApplication::translate("Waveform", "start_Record", nullptr));
#if QT_CONFIG(tooltip)
        action_Start_Record->setToolTip(QCoreApplication::translate("Waveform", "\347\202\271\346\255\244\350\256\260\345\275\225\346\263\242\345\275\242", nullptr));
#endif // QT_CONFIG(tooltip)
        action_bluetooth->setText(QCoreApplication::translate("Waveform", "_bluetooth", nullptr));
#if QT_CONFIG(tooltip)
        action_bluetooth->setToolTip(QCoreApplication::translate("Waveform", "\345\210\267\346\226\260\350\256\276\345\244\207", nullptr));
#endif // QT_CONFIG(tooltip)
        connectstate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Waveform: public Ui_Waveform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVEFORM_H
