/********************************************************************************
** Form generated from reading UI file 'initdatasystemprotocol.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITDATASYSTEMPROTOCOL_H
#define UI_INITDATASYSTEMPROTOCOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitDataSystemProtocol
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *InitDataSystemProtocol)
    {
        if (InitDataSystemProtocol->objectName().isEmpty())
            InitDataSystemProtocol->setObjectName("InitDataSystemProtocol");
        InitDataSystemProtocol->resize(399, 187);
        gridLayoutWidget = new QWidget(InitDataSystemProtocol);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 10, 381, 171));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(gridLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");
        QFont font;
        font.setPointSize(8);
        lineEdit_2->setFont(font);
        lineEdit_2->setText(QString::fromUtf8("\351\200\232\344\277\241\345\215\217\350\256\256\347\261\273\345\236\213"));
        lineEdit_2->setFrame(false);

        gridLayout->addWidget(lineEdit_2, 0, 1, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName("comboBox");

        gridLayout->addWidget(comboBox, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget);
        comboBox_2->setObjectName("comboBox_2");

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setEnabled(true);
        lineEdit->setFont(font);
        lineEdit->setText(QString::fromUtf8("\346\225\260\346\215\256\345\215\217\350\256\256\347\261\273\345\236\213"));
        lineEdit->setFrame(false);

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(gridLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);


        retranslateUi(InitDataSystemProtocol);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, InitDataSystemProtocol, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, InitDataSystemProtocol, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(InitDataSystemProtocol);
    } // setupUi

    void retranslateUi(QDialog *InitDataSystemProtocol)
    {
        InitDataSystemProtocol->setWindowTitle(QCoreApplication::translate("InitDataSystemProtocol", "\351\200\211\346\213\251\345\215\217\350\256\256", nullptr));
        lineEdit->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class InitDataSystemProtocol: public Ui_InitDataSystemProtocol {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITDATASYSTEMPROTOCOL_H
