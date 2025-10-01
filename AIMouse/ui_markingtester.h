/********************************************************************************
** Form generated from reading UI file 'markingtester.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKINGTESTER_H
#define UI_MARKINGTESTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MarkingTester
{
public:
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboMarkNum;
    QPushButton *manualMarkBtn;

    void setupUi(QDialog *MarkingTester)
    {
        if (MarkingTester->objectName().isEmpty())
            MarkingTester->setObjectName("MarkingTester");
        MarkingTester->resize(443, 177);
        verticalLayout_3 = new QVBoxLayout(MarkingTester);
        verticalLayout_3->setObjectName("verticalLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");

        gridLayout->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(MarkingTester);
        label->setObjectName("label");
        label->setMinimumSize(QSize(20, 20));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        comboMarkNum = new QComboBox(MarkingTester);
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->addItem(QString());
        comboMarkNum->setObjectName("comboMarkNum");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboMarkNum->sizePolicy().hasHeightForWidth());
        comboMarkNum->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        comboMarkNum->setFont(font);

        horizontalLayout->addWidget(comboMarkNum);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        manualMarkBtn = new QPushButton(MarkingTester);
        manualMarkBtn->setObjectName("manualMarkBtn");
        sizePolicy.setHeightForWidth(manualMarkBtn->sizePolicy().hasHeightForWidth());
        manualMarkBtn->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(manualMarkBtn);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout_4->setStretch(0, 1);

        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 3);

        verticalLayout_3->addLayout(gridLayout);


        retranslateUi(MarkingTester);

        QMetaObject::connectSlotsByName(MarkingTester);
    } // setupUi

    void retranslateUi(QDialog *MarkingTester)
    {
        MarkingTester->setWindowTitle(QCoreApplication::translate("MarkingTester", "\346\211\223\346\240\207", nullptr));
        label->setText(QCoreApplication::translate("MarkingTester", "\351\200\211\346\213\251\346\211\223\346\240\207\345\217\267      ", nullptr));
        comboMarkNum->setItemText(0, QCoreApplication::translate("MarkingTester", "1", nullptr));
        comboMarkNum->setItemText(1, QCoreApplication::translate("MarkingTester", "2", nullptr));
        comboMarkNum->setItemText(2, QCoreApplication::translate("MarkingTester", "3", nullptr));
        comboMarkNum->setItemText(3, QCoreApplication::translate("MarkingTester", "4", nullptr));
        comboMarkNum->setItemText(4, QCoreApplication::translate("MarkingTester", "5", nullptr));
        comboMarkNum->setItemText(5, QCoreApplication::translate("MarkingTester", "6", nullptr));
        comboMarkNum->setItemText(6, QCoreApplication::translate("MarkingTester", "7", nullptr));
        comboMarkNum->setItemText(7, QCoreApplication::translate("MarkingTester", "8", nullptr));
        comboMarkNum->setItemText(8, QCoreApplication::translate("MarkingTester", "9", nullptr));
        comboMarkNum->setItemText(9, QCoreApplication::translate("MarkingTester", "10", nullptr));

        manualMarkBtn->setText(QCoreApplication::translate("MarkingTester", "\346\211\213\345\212\250\346\211\223\346\240\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MarkingTester: public Ui_MarkingTester {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKINGTESTER_H
