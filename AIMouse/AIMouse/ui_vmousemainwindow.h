/********************************************************************************
** Form generated from reading UI file 'vmousemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VMOUSEMAINWINDOW_H
#define UI_VMOUSEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VMouseMainWindow
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *VMouseMainWindow)
    {
        if (VMouseMainWindow->objectName().isEmpty())
            VMouseMainWindow->setObjectName("VMouseMainWindow");
        VMouseMainWindow->resize(30, 28);
        centralwidget = new QWidget(VMouseMainWindow);
        centralwidget->setObjectName("centralwidget");
        VMouseMainWindow->setCentralWidget(centralwidget);

        retranslateUi(VMouseMainWindow);

        QMetaObject::connectSlotsByName(VMouseMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VMouseMainWindow)
    {
        VMouseMainWindow->setWindowTitle(QCoreApplication::translate("VMouseMainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VMouseMainWindow: public Ui_VMouseMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VMOUSEMAINWINDOW_H
