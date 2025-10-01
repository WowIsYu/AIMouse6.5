/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QFrame *frame_background;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *horizontalSpacer_16;
    QFrame *frame_img;
    QFrame *frame_login;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_Login;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_account;
    QHBoxLayout *horizontalLayout;
    QLabel *label_account;
    QLineEdit *lineEdit_account;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame_pwd;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_pwd;
    QLineEdit *lineEdit_pwd;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QFrame *frame_pwd_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_pwd_verify;
    QLineEdit *lineEdit_pwd_verify;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_3;
    QFrame *frame_code;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_code;
    QLineEdit *lineEdit_code;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_graph;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_9;
    QRadioButton *radioButton_regist;
    QSpacerItem *horizontalSpacer_10;
    QRadioButton *radioButton_login;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_18;
    QFrame *frame_result;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_result;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(887, 590);
        Login->setAutoFillBackground(false);
        Login->setStyleSheet(QString::fromUtf8("/**\n"
"    \350\257\245\351\241\265\351\235\242\344\270\272\346\265\205\347\264\253\350\211\262\347\232\256\350\202\244\n"
"\n"
"\n"
"\346\216\247\344\273\266\345\220\215\345\211\215\345\212\240\344\270\252#\344\273\243\350\241\250\346\214\207\345\256\232\346\237\220\344\270\252\346\216\247\344\273\266\357\274\233\n"
"border-image\350\241\250\347\244\272\345\241\253\345\205\205\346\225\264\344\270\252\350\203\214\346\231\257\357\274\233\n"
"background-image\350\241\250\347\244\272\350\256\276\347\275\256\350\203\214\346\231\257\357\274\214\344\275\206\344\270\215\345\241\253\345\205\205;\n"
"border\350\241\250\347\244\272\350\276\271\346\241\206\345\244\247\345\260\217;\n"
"border-radius\350\241\250\347\244\272\350\276\271\346\241\206\345\234\206\350\247\222\345\244\247\345\260\217;\n"
"color\350\241\250\347\244\272\345\255\227\344\275\223\351\242\234\350\211\262\357\274\233background-position\350\241\250\347\244\272\345\233\276\347\211\207\344\275\215\347\275\256;\n"
"background-repeat\350\241\250\347\244\272"
                        "\345\233\276\347\211\207\346\230\257\345\220\246\351\207\215\345\244\215\346\230\276\347\244\272\n"
"*/\n"
"#frame_background{\n"
"border-image:url(:/img/background-gg.jpg);\n"
"}\n"
"\n"
"#frame_login{\n"
"    background-color:#ffffff\n"
"}\n"
"\n"
"#frame_img{\n"
"    background-image:url(:/img/cxk.png);\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"#frame_account,#frame_pwd,#frame_pwd_2{\n"
"    border: 1px solid #696969;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"\n"
"\n"
"QLineEdit{\n"
"    border: none;\n"
"}\n"
"\n"
"\n"
"\n"
"#pushButton{\n"
"    color:#ffffff;\n"
"    border: none;\n"
"    background-color:#8293fd;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"#pushButton:hover{\n"
"    color:#ffffff;\n"
"    border: none;\n"
"    background-color:#4861fb;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"#pushButton:pressed{\n"
"    color:#ffffff;\n"
"    border: none;\n"
"    background-color:#8293fd;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"#label_login\n"
"{\n"
"    color:#7185ff;\n"
"\n"
"}\n"
"#label_account\n"
"{\n"
""
                        "    border-image:url(:/img/user_name.png);\n"
"}\n"
"\n"
"#label_pwd\n"
"{\n"
"    border-image:url(:/img/pwd.png);\n"
"\n"
"}\n"
""));
        frame_background = new QFrame(Login);
        frame_background->setObjectName("frame_background");
        frame_background->setGeometry(QRect(6, 6, 869, 592));
        frame_background->setFrameShape(QFrame::StyledPanel);
        frame_background->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_background);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalSpacer_7 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 0, 1, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_16, 1, 0, 1, 1);

        frame_img = new QFrame(frame_background);
        frame_img->setObjectName("frame_img");
        frame_img->setMinimumSize(QSize(400, 500));
        frame_img->setMaximumSize(QSize(400, 500));
        frame_img->setStyleSheet(QString::fromUtf8(""));
        frame_img->setFrameShape(QFrame::StyledPanel);
        frame_img->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(frame_img, 1, 1, 1, 2);

        frame_login = new QFrame(frame_background);
        frame_login->setObjectName("frame_login");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_login->sizePolicy().hasHeightForWidth());
        frame_login->setSizePolicy(sizePolicy);
        frame_login->setMinimumSize(QSize(400, 500));
        frame_login->setMaximumSize(QSize(400, 500));
        frame_login->setStyleSheet(QString::fromUtf8(""));
        frame_login->setFrameShape(QFrame::StyledPanel);
        frame_login->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_login);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        label_Login = new QLabel(frame_login);
        label_Login->setObjectName("label_Login");
        sizePolicy.setHeightForWidth(label_Login->sizePolicy().hasHeightForWidth());
        label_Login->setSizePolicy(sizePolicy);
        label_Login->setMinimumSize(QSize(100, 40));
        label_Login->setMaximumSize(QSize(100, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\347\220\245\347\217\200")});
        font.setPointSize(20);
        label_Login->setFont(font);
        label_Login->setLayoutDirection(Qt::LeftToRight);
        label_Login->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_Login);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(17, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        frame_account = new QFrame(frame_login);
        frame_account->setObjectName("frame_account");
        frame_account->setFrameShape(QFrame::StyledPanel);
        frame_account->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_account);
        horizontalLayout->setObjectName("horizontalLayout");
        label_account = new QLabel(frame_account);
        label_account->setObjectName("label_account");
        sizePolicy.setHeightForWidth(label_account->sizePolicy().hasHeightForWidth());
        label_account->setSizePolicy(sizePolicy);
        label_account->setMinimumSize(QSize(40, 40));
        label_account->setMaximumSize(QSize(40, 40));
        label_account->setTextFormat(Qt::AutoText);

        horizontalLayout->addWidget(label_account);

        lineEdit_account = new QLineEdit(frame_account);
        lineEdit_account->setObjectName("lineEdit_account");
        sizePolicy.setHeightForWidth(lineEdit_account->sizePolicy().hasHeightForWidth());
        lineEdit_account->setSizePolicy(sizePolicy);
        lineEdit_account->setMinimumSize(QSize(200, 30));
        lineEdit_account->setMaximumSize(QSize(200, 30));
        lineEdit_account->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	backGround-color:rgb(255, 255, 255)\n"
"}"));

        horizontalLayout->addWidget(lineEdit_account);


        horizontalLayout_2->addWidget(frame_account);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(17, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        frame_pwd = new QFrame(frame_login);
        frame_pwd->setObjectName("frame_pwd");
        frame_pwd->setFrameShape(QFrame::StyledPanel);
        frame_pwd->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_pwd);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_pwd = new QLabel(frame_pwd);
        label_pwd->setObjectName("label_pwd");
        sizePolicy.setHeightForWidth(label_pwd->sizePolicy().hasHeightForWidth());
        label_pwd->setSizePolicy(sizePolicy);
        label_pwd->setMinimumSize(QSize(40, 40));
        label_pwd->setMaximumSize(QSize(40, 40));

        horizontalLayout_3->addWidget(label_pwd);

        lineEdit_pwd = new QLineEdit(frame_pwd);
        lineEdit_pwd->setObjectName("lineEdit_pwd");
        sizePolicy.setHeightForWidth(lineEdit_pwd->sizePolicy().hasHeightForWidth());
        lineEdit_pwd->setSizePolicy(sizePolicy);
        lineEdit_pwd->setMinimumSize(QSize(200, 30));
        lineEdit_pwd->setMaximumSize(QSize(200, 30));
        lineEdit_pwd->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	backGround-color:rgb(255, 255, 255)\n"
"}"));
        lineEdit_pwd->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(lineEdit_pwd);


        horizontalLayout_6->addWidget(frame_pwd);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_6, 4, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        frame_pwd_2 = new QFrame(frame_login);
        frame_pwd_2->setObjectName("frame_pwd_2");
        frame_pwd_2->setFrameShape(QFrame::StyledPanel);
        frame_pwd_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_pwd_2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_pwd_verify = new QLabel(frame_pwd_2);
        label_pwd_verify->setObjectName("label_pwd_verify");
        sizePolicy.setHeightForWidth(label_pwd_verify->sizePolicy().hasHeightForWidth());
        label_pwd_verify->setSizePolicy(sizePolicy);
        label_pwd_verify->setMinimumSize(QSize(60, 40));
        label_pwd_verify->setMaximumSize(QSize(60, 40));

        horizontalLayout_4->addWidget(label_pwd_verify);

        lineEdit_pwd_verify = new QLineEdit(frame_pwd_2);
        lineEdit_pwd_verify->setObjectName("lineEdit_pwd_verify");
        sizePolicy.setHeightForWidth(lineEdit_pwd_verify->sizePolicy().hasHeightForWidth());
        lineEdit_pwd_verify->setSizePolicy(sizePolicy);
        lineEdit_pwd_verify->setMinimumSize(QSize(180, 30));
        lineEdit_pwd_verify->setMaximumSize(QSize(180, 30));
        lineEdit_pwd_verify->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	backGround-color:rgb(255, 255, 255)\n"
"}"));

        horizontalLayout_4->addWidget(lineEdit_pwd_verify);


        horizontalLayout_7->addWidget(frame_pwd_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_7, 5, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(17, 19, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 6, 0, 1, 1);

        frame_code = new QFrame(frame_login);
        frame_code->setObjectName("frame_code");
        frame_code->setStyleSheet(QString::fromUtf8("#frame_code{\n"
"	color:#ffffff;\n"
"    border: none;\n"
"    background-color:rgb(193, 193, 255);\n"
"    border-radius: 5px;\n"
"}"));
        frame_code->setFrameShape(QFrame::StyledPanel);
        frame_code->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_code);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_code = new QLabel(frame_code);
        label_code->setObjectName("label_code");
        sizePolicy.setHeightForWidth(label_code->sizePolicy().hasHeightForWidth());
        label_code->setSizePolicy(sizePolicy);
        label_code->setMinimumSize(QSize(60, 40));
        label_code->setMaximumSize(QSize(60, 40));

        horizontalLayout_5->addWidget(label_code);

        lineEdit_code = new QLineEdit(frame_code);
        lineEdit_code->setObjectName("lineEdit_code");
        sizePolicy.setHeightForWidth(lineEdit_code->sizePolicy().hasHeightForWidth());
        lineEdit_code->setSizePolicy(sizePolicy);
        lineEdit_code->setMinimumSize(QSize(150, 30));
        lineEdit_code->setMaximumSize(QSize(150, 30));
        lineEdit_code->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	backGround-color:rgb(255, 255, 255)\n"
"}"));

        horizontalLayout_5->addWidget(lineEdit_code);

        horizontalSpacer_12 = new QSpacerItem(49, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);

        label_graph = new QLabel(frame_code);
        label_graph->setObjectName("label_graph");
        sizePolicy.setHeightForWidth(label_graph->sizePolicy().hasHeightForWidth());
        label_graph->setSizePolicy(sizePolicy);
        label_graph->setMinimumSize(QSize(100, 40));
        label_graph->setMaximumSize(QSize(100, 40));
        label_graph->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_graph);


        gridLayout->addWidget(frame_code, 7, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(17, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 8, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_9);

        radioButton_regist = new QRadioButton(frame_login);
        radioButton_regist->setObjectName("radioButton_regist");
        radioButton_regist->setMinimumSize(QSize(80, 40));
        radioButton_regist->setMaximumSize(QSize(80, 40));
        radioButton_regist->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_8->addWidget(radioButton_regist);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);

        radioButton_login = new QRadioButton(frame_login);
        radioButton_login->setObjectName("radioButton_login");
        sizePolicy.setHeightForWidth(radioButton_login->sizePolicy().hasHeightForWidth());
        radioButton_login->setSizePolicy(sizePolicy);
        radioButton_login->setMinimumSize(QSize(80, 40));
        radioButton_login->setMaximumSize(QSize(80, 40));
        radioButton_login->setStyleSheet(QString::fromUtf8(""));
        radioButton_login->setCheckable(true);
        radioButton_login->setChecked(false);

        horizontalLayout_8->addWidget(radioButton_login);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_11);


        gridLayout->addLayout(horizontalLayout_8, 9, 0, 1, 1);

        verticalSpacer = new QSpacerItem(17, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_14);

        pushButton = new QPushButton(frame_login);
        pushButton->setObjectName("pushButton");
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(120, 30));
        pushButton->setMaximumSize(QSize(120, 30));
        pushButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_10->addWidget(pushButton);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_13);

        pushButton_2 = new QPushButton(frame_login);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(120, 30));
        pushButton_2->setMaximumSize(QSize(120, 30));

        horizontalLayout_10->addWidget(pushButton_2);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_15);


        gridLayout->addLayout(horizontalLayout_10, 11, 0, 1, 1);


        gridLayout_2->addWidget(frame_login, 1, 3, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_17, 1, 4, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(379, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_18, 2, 1, 1, 1);

        frame_result = new QFrame(frame_background);
        frame_result->setObjectName("frame_result");
        frame_result->setFrameShape(QFrame::StyledPanel);
        frame_result->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_result);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_result = new QLabel(frame_result);
        label_result->setObjectName("label_result");
        sizePolicy.setHeightForWidth(label_result->sizePolicy().hasHeightForWidth());
        label_result->setSizePolicy(sizePolicy);
        label_result->setMinimumSize(QSize(390, 40));
        label_result->setMaximumSize(QSize(390, 40));
        label_result->setStyleSheet(QString::fromUtf8("#label_result{\n"
"	background-color:rgb(190, 190, 255)\n"
"}"));
        label_result->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_result);


        gridLayout_2->addWidget(frame_result, 2, 2, 1, 2);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        label_Login->setText(QCoreApplication::translate("Login", "LOGIN", nullptr));
        label_account->setText(QString());
        lineEdit_account->setText(QCoreApplication::translate("Login", "abc123", nullptr));
        label_pwd->setText(QString());
        lineEdit_pwd->setText(QCoreApplication::translate("Login", "abc123", nullptr));
        label_pwd_verify->setText(QCoreApplication::translate("Login", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        label_code->setText(QCoreApplication::translate("Login", "\351\252\214 \350\257\201 \347\240\201\357\274\232", nullptr));
        lineEdit_code->setText(QCoreApplication::translate("Login", "1111", nullptr));
        label_graph->setText(QCoreApplication::translate("Login", "graph", nullptr));
        radioButton_regist->setText(QCoreApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
        radioButton_login->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        pushButton->setText(QCoreApplication::translate("Login", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Login", "\345\217\226\346\266\210", nullptr));
        label_result->setText(QCoreApplication::translate("Login", "\346\217\220\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
