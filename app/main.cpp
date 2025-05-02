#include "ui/mainwindow.h"
#include <QApplication>
#include <QSystemTrayIcon>
int main(int argc, char *argv[])
{
    // QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;

    QSystemTrayIcon sysTray(QIcon(":/img/sharp_logo.png"), &w);

    QMenu menu;
    auto showAct= new QAction("show", &sysTray);
    auto exitAct = new QAction("exit", &sysTray);

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

    w.initMainWindow();
    return a.exec();
}
