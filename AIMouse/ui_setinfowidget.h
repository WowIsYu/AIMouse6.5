/********************************************************************************
** Form generated from reading UI file 'setinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETINFOWIDGET_H
#define UI_SETINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetInfoWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *pb_Close;
    QLabel *label_oldName;
    QLineEdit *le_oleName;
    QLabel *label_newName;
    QLineEdit *le_newName;
    QPushButton *pb_OK;

    void setupUi(QWidget *SetInfoWidget)
    {
        if (SetInfoWidget->objectName().isEmpty())
            SetInfoWidget->setObjectName("SetInfoWidget");
        SetInfoWidget->resize(342, 421);
        gridLayout = new QGridLayout(SetInfoWidget);
        gridLayout->setObjectName("gridLayout");
        pb_Close = new QPushButton(SetInfoWidget);
        pb_Close->setObjectName("pb_Close");

        gridLayout->addWidget(pb_Close, 0, 1, 1, 1);

        label_oldName = new QLabel(SetInfoWidget);
        label_oldName->setObjectName("label_oldName");

        gridLayout->addWidget(label_oldName, 1, 0, 1, 1);

        le_oleName = new QLineEdit(SetInfoWidget);
        le_oleName->setObjectName("le_oleName");
        le_oleName->setEnabled(false);

        gridLayout->addWidget(le_oleName, 1, 1, 1, 1);

        label_newName = new QLabel(SetInfoWidget);
        label_newName->setObjectName("label_newName");

        gridLayout->addWidget(label_newName, 2, 0, 1, 1);

        le_newName = new QLineEdit(SetInfoWidget);
        le_newName->setObjectName("le_newName");

        gridLayout->addWidget(le_newName, 2, 1, 1, 1);

        pb_OK = new QPushButton(SetInfoWidget);
        pb_OK->setObjectName("pb_OK");

        gridLayout->addWidget(pb_OK, 3, 1, 1, 1);


        retranslateUi(SetInfoWidget);

        QMetaObject::connectSlotsByName(SetInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *SetInfoWidget)
    {
        SetInfoWidget->setWindowTitle(QCoreApplication::translate("SetInfoWidget", "\344\277\256\346\224\271\350\223\235\347\211\231\345\220\215\347\247\260", nullptr));
        pb_Close->setText(QCoreApplication::translate("SetInfoWidget", "close", nullptr));
        label_oldName->setText(QCoreApplication::translate("SetInfoWidget", "\345\216\237\350\223\235\347\211\231\345\220\215", nullptr));
        label_newName->setText(QCoreApplication::translate("SetInfoWidget", "\346\226\260\350\223\235\347\211\231\345\220\215", nullptr));
        pb_OK->setText(QCoreApplication::translate("SetInfoWidget", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetInfoWidget: public Ui_SetInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETINFOWIDGET_H
