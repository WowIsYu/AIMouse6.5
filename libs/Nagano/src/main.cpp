#include "widget.h"

#include <QApplication>
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QSystemTrayIcon sysTray(QIcon(":/logo.png"), &w);

    QMenu menu;
    auto showAct= new QAction("显示", &sysTray);
    auto exitAct = new QAction("退出", &sysTray);

    QObject::connect(showAct, &QAction::triggered, [&]() {
        w.setVisible(true);
    });
    QObject::connect(exitAct, &QAction::triggered, [&](){
        QApplication::quit();
    });

    menu.addAction(showAct);
    menu.addAction(exitAct);

    sysTray.setContextMenu(&menu);

    sysTray.show();
    w.show();
    return a.exec();
}
