#include <QApplication>

#include "views/MazeGame.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MazeGame window;

    window.initialize();
    window.show();

    return app.exec();
}
