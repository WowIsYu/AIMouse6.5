/********************************************************************************
** Form generated from reading UI file 'blinkcalibration.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLINKCALIBRATION_H
#define UI_BLINKCALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BlinkCalibration
{
public:
    QGridLayout *gridLayout;
    QFrame *frame_background;
    QPushButton *beginCaliButton;
    QFrame *frame_blink;
    QHBoxLayout *horizontalLayout;
    QLabel *graphcodeLabel_2;
    QLineEdit *blinkIntervalLineEdit;
    QLabel *caliIcon;
    QFrame *frame_result;
    QGridLayout *gridLayout_2;
    QLabel *caliResultLabel;
    QFrame *frame_feedback;
    QGridLayout *gridLayout_3;
    QLabel *feedbackLabel;
    QLabel *labelTip;
    QLabel *labelTest;

    void setupUi(QWidget *BlinkCalibration)
    {
        if (BlinkCalibration->objectName().isEmpty())
            BlinkCalibration->setObjectName("BlinkCalibration");
        BlinkCalibration->resize(713, 507);
        BlinkCalibration->setStyleSheet(QString::fromUtf8("#frame_result,#frame_blink,#frame_feedback{\n"
"    border: 1px solid #696969;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"#frame_background{\n"
"	background-color:rgb(216, 220, 255)\n"
"}\n"
"\n"
"QPushButton{\n"
"    color:#ffffff;\n"
"    border: none;\n"
"    background-color:#8293fd;\n"
"    border-radius: 5px;\n"
"}"));
        gridLayout = new QGridLayout(BlinkCalibration);
        gridLayout->setObjectName("gridLayout");
        frame_background = new QFrame(BlinkCalibration);
        frame_background->setObjectName("frame_background");
        frame_background->setFrameShape(QFrame::StyledPanel);
        frame_background->setFrameShadow(QFrame::Raised);
        beginCaliButton = new QPushButton(frame_background);
        beginCaliButton->setObjectName("beginCaliButton");
        beginCaliButton->setGeometry(QRect(290, 370, 121, 41));
        frame_blink = new QFrame(frame_background);
        frame_blink->setObjectName("frame_blink");
        frame_blink->setGeometry(QRect(10, 10, 281, 71));
        frame_blink->setFrameShape(QFrame::StyledPanel);
        frame_blink->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_blink);
        horizontalLayout->setObjectName("horizontalLayout");
        graphcodeLabel_2 = new QLabel(frame_blink);
        graphcodeLabel_2->setObjectName("graphcodeLabel_2");
        QFont font;
        font.setPointSize(14);
        graphcodeLabel_2->setFont(font);

        horizontalLayout->addWidget(graphcodeLabel_2);

        blinkIntervalLineEdit = new QLineEdit(frame_blink);
        blinkIntervalLineEdit->setObjectName("blinkIntervalLineEdit");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(blinkIntervalLineEdit->sizePolicy().hasHeightForWidth());
        blinkIntervalLineEdit->setSizePolicy(sizePolicy);
        blinkIntervalLineEdit->setMinimumSize(QSize(140, 30));
        blinkIntervalLineEdit->setMaximumSize(QSize(140, 30));

        horizontalLayout->addWidget(blinkIntervalLineEdit);

        caliIcon = new QLabel(frame_background);
        caliIcon->setObjectName("caliIcon");
        caliIcon->setGeometry(QRect(260, 130, 180, 200));
        sizePolicy.setHeightForWidth(caliIcon->sizePolicy().hasHeightForWidth());
        caliIcon->setSizePolicy(sizePolicy);
        caliIcon->setMinimumSize(QSize(180, 200));
        caliIcon->setMaximumSize(QSize(180, 200));
        frame_result = new QFrame(frame_background);
        frame_result->setObjectName("frame_result");
        frame_result->setGeometry(QRect(470, 10, 211, 81));
        frame_result->setFrameShape(QFrame::StyledPanel);
        frame_result->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_result);
        gridLayout_2->setObjectName("gridLayout_2");
        caliResultLabel = new QLabel(frame_result);
        caliResultLabel->setObjectName("caliResultLabel");
        QFont font1;
        font1.setPointSize(20);
        caliResultLabel->setFont(font1);
        caliResultLabel->setScaledContents(false);
        caliResultLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(caliResultLabel, 0, 0, 1, 1);

        frame_feedback = new QFrame(frame_background);
        frame_feedback->setObjectName("frame_feedback");
        frame_feedback->setGeometry(QRect(30, 450, 631, 31));
        frame_feedback->setFrameShape(QFrame::StyledPanel);
        frame_feedback->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_feedback);
        gridLayout_3->setObjectName("gridLayout_3");
        feedbackLabel = new QLabel(frame_feedback);
        feedbackLabel->setObjectName("feedbackLabel");
        feedbackLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(feedbackLabel, 0, 0, 1, 1);

        labelTip = new QLabel(frame_background);
        labelTip->setObjectName("labelTip");
        labelTip->setGeometry(QRect(270, 100, 161, 31));
        labelTip->setAlignment(Qt::AlignCenter);
        labelTest = new QLabel(frame_background);
        labelTest->setObjectName("labelTest");
        labelTest->setGeometry(QRect(30, 180, 91, 111));

        gridLayout->addWidget(frame_background, 0, 0, 1, 1);


        retranslateUi(BlinkCalibration);

        QMetaObject::connectSlotsByName(BlinkCalibration);
    } // setupUi

    void retranslateUi(QWidget *BlinkCalibration)
    {
        BlinkCalibration->setWindowTitle(QCoreApplication::translate("BlinkCalibration", "Form", nullptr));
        beginCaliButton->setText(QCoreApplication::translate("BlinkCalibration", "\345\274\200\345\247\213\346\240\241\345\207\206", nullptr));
        graphcodeLabel_2->setText(QCoreApplication::translate("BlinkCalibration", "\347\234\250\347\234\274\351\227\264\351\232\224\346\227\266\351\227\264", nullptr));
        blinkIntervalLineEdit->setText(QCoreApplication::translate("BlinkCalibration", "2", nullptr));
        caliIcon->setText(QString());
        caliResultLabel->setText(QCoreApplication::translate("BlinkCalibration", "\346\240\241\345\207\206\345\210\206\346\225\260", nullptr));
        feedbackLabel->setText(QCoreApplication::translate("BlinkCalibration", "\346\217\220\347\244\272", nullptr));
        labelTip->setText(QCoreApplication::translate("BlinkCalibration", "\350\267\237\347\235\200\344\270\200\350\265\267\347\234\250\347\234\274\347\235\233", nullptr));
        labelTest->setText(QCoreApplication::translate("BlinkCalibration", "123", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BlinkCalibration: public Ui_BlinkCalibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLINKCALIBRATION_H
