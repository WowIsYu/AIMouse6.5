/********************************************************************************
** Form generated from reading UI file 'setup.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUP_H
#define UI_SETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetUp
{
public:
    QGridLayout *gridLayout;
    QFrame *frame_background;
    QFrame *frame_gy;
    QSlider *horizontalSlider;
    QLabel *label;
    QPushButton *resetButton;
    QLabel *sensitivityLabel;
    QFrame *frame_attention;
    QLabel *resultLabel;
    QLabel *label2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *userModeBtn;
    QRadioButton *bigDataBtn;
    QPushButton *pushButton;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *beginButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer_3;
    QLabel *feedbackLabel;

    void setupUi(QWidget *SetUp)
    {
        if (SetUp->objectName().isEmpty())
            SetUp->setObjectName("SetUp");
        SetUp->resize(781, 552);
        SetUp->setStyleSheet(QString::fromUtf8("#frame_background{\n"
"border-image:url(:/img/background-gg.jpg);\n"
"}\n"
"\n"
"#frame_gy, #frame_3,#frame_attention{\n"
"    background-color:#ffffff\n"
"}\n"
"\n"
"\n"
"QPushButton{\n"
"    color:#ffffff;\n"
"    border: none;\n"
"    background-color:#8293fd;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"    color:#7185ff;\n"
"\n"
"}"));
        gridLayout = new QGridLayout(SetUp);
        gridLayout->setObjectName("gridLayout");
        frame_background = new QFrame(SetUp);
        frame_background->setObjectName("frame_background");
        frame_background->setFrameShape(QFrame::StyledPanel);
        frame_background->setFrameShadow(QFrame::Raised);
        frame_gy = new QFrame(frame_background);
        frame_gy->setObjectName("frame_gy");
        frame_gy->setGeometry(QRect(400, 30, 331, 301));
        frame_gy->setFrameShape(QFrame::StyledPanel);
        frame_gy->setFrameShadow(QFrame::Raised);
        horizontalSlider = new QSlider(frame_gy);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(10, 80, 171, 31));
        horizontalSlider->setMinimum(6);
        horizontalSlider->setMaximum(20);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setValue(14);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(frame_gy);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 161, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(22);
        label->setFont(font);
        resetButton = new QPushButton(frame_gy);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(10, 150, 150, 30));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(resetButton->sizePolicy().hasHeightForWidth());
        resetButton->setSizePolicy(sizePolicy);
        resetButton->setMinimumSize(QSize(150, 30));
        resetButton->setMaximumSize(QSize(150, 30));
        sensitivityLabel = new QLabel(frame_gy);
        sensitivityLabel->setObjectName("sensitivityLabel");
        sensitivityLabel->setGeometry(QRect(20, 60, 161, 20));
        QFont font1;
        font1.setPointSize(11);
        sensitivityLabel->setFont(font1);
        frame_attention = new QFrame(frame_background);
        frame_attention->setObjectName("frame_attention");
        frame_attention->setGeometry(QRect(20, 30, 361, 301));
        frame_attention->setFrameShape(QFrame::StyledPanel);
        frame_attention->setFrameShadow(QFrame::Raised);
        resultLabel = new QLabel(frame_attention);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setGeometry(QRect(180, 250, 131, 31));
        QFont font2;
        font2.setPointSize(14);
        resultLabel->setFont(font2);
        resultLabel->setScaledContents(false);
        resultLabel->setAlignment(Qt::AlignCenter);
        label2 = new QLabel(frame_attention);
        label2->setObjectName("label2");
        label2->setGeometry(QRect(10, 10, 171, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font3.setPointSize(24);
        label2->setFont(font3);
        label2->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(frame_attention);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 60, 341, 85));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        userModeBtn = new QRadioButton(groupBox);
        userModeBtn->setObjectName("userModeBtn");
        sizePolicy.setHeightForWidth(userModeBtn->sizePolicy().hasHeightForWidth());
        userModeBtn->setSizePolicy(sizePolicy);
        userModeBtn->setMinimumSize(QSize(150, 30));
        userModeBtn->setMaximumSize(QSize(150, 30));

        verticalLayout->addWidget(userModeBtn);

        bigDataBtn = new QRadioButton(groupBox);
        bigDataBtn->setObjectName("bigDataBtn");
        sizePolicy.setHeightForWidth(bigDataBtn->sizePolicy().hasHeightForWidth());
        bigDataBtn->setSizePolicy(sizePolicy);
        bigDataBtn->setMinimumSize(QSize(150, 30));
        bigDataBtn->setMaximumSize(QSize(150, 30));

        verticalLayout->addWidget(bigDataBtn);

        pushButton = new QPushButton(frame_attention);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 250, 101, 31));
        frame_3 = new QFrame(frame_attention);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 170, 341, 51));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        beginButton = new QPushButton(frame_3);
        beginButton->setObjectName("beginButton");
        sizePolicy.setHeightForWidth(beginButton->sizePolicy().hasHeightForWidth());
        beginButton->setSizePolicy(sizePolicy);
        beginButton->setMinimumSize(QSize(100, 30));
        beginButton->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(beginButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        stopButton = new QPushButton(frame_3);
        stopButton->setObjectName("stopButton");
        sizePolicy.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy);
        stopButton->setMinimumSize(QSize(100, 30));
        stopButton->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(stopButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        feedbackLabel = new QLabel(frame_background);
        feedbackLabel->setObjectName("feedbackLabel");
        feedbackLabel->setGeometry(QRect(20, 480, 721, 31));
        feedbackLabel->setFont(font2);
        feedbackLabel->setStyleSheet(QString::fromUtf8("#feedbackLabel{\n"
"	background-color:rgb(255, 255, 255)\n"
"}"));
        feedbackLabel->setScaledContents(false);
        feedbackLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(frame_background, 0, 0, 1, 1);


        retranslateUi(SetUp);

        QMetaObject::connectSlotsByName(SetUp);
    } // setupUi

    void retranslateUi(QWidget *SetUp)
    {
        SetUp->setWindowTitle(QCoreApplication::translate("SetUp", "\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("SetUp", "\351\231\200\350\236\272\344\273\252\350\256\276\347\275\256\357\274\232", nullptr));
        resetButton->setText(QCoreApplication::translate("SetUp", "\345\235\220\346\240\207\345\233\236\346\255\243", nullptr));
        sensitivityLabel->setText(QCoreApplication::translate("SetUp", "\347\201\265\346\225\217\345\272\246\357\274\23214", nullptr));
        resultLabel->setText(QCoreApplication::translate("SetUp", "\346\263\250\346\204\217\345\212\233\345\200\274", nullptr));
        label2->setText(QCoreApplication::translate("SetUp", "\346\263\250\346\204\217\345\212\233\346\243\200\346\265\213:", nullptr));
        groupBox->setTitle(QString());
        userModeBtn->setText(QCoreApplication::translate("SetUp", "\347\224\250\346\210\267\346\250\241\345\236\213", nullptr));
        bigDataBtn->setText(QCoreApplication::translate("SetUp", "\345\244\247\346\225\260\346\215\256\346\250\241\345\236\213", nullptr));
        pushButton->setText(QCoreApplication::translate("SetUp", "\346\230\276\347\244\272\346\263\250\346\204\217\345\212\233\345\200\274\347\252\227\345\217\243", nullptr));
        beginButton->setText(QCoreApplication::translate("SetUp", "\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
        stopButton->setText(QCoreApplication::translate("SetUp", "\345\201\234\346\255\242\346\243\200\346\265\213", nullptr));
        feedbackLabel->setText(QCoreApplication::translate("SetUp", "\346\223\215\344\275\234\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetUp: public Ui_SetUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
