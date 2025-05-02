#ifndef __VIEWS_MAZEGAME_H__
#define __VIEWS_MAZEGAME_H__

#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QKeyEvent>

#include "cores/framework.h"
#include "utils/resources.h"
#include "views/dialogs/successdialog.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
class MazeGame;  // 修改UI命名空间中的类名
}

QT_END_NAMESPACE

class MazeGame : public QMainWindow  // 修改类名
{
    Q_OBJECT

private:
    Ui::MazeGame* ui;  // 修改UI指针类型
    int scale = 2;

private:
    GameFramework* gameFramework;
    GameResources* gameResources;

private:
    SuccessDialog* successDialog;

private:
    QTimer* frameTimer;
    QTimer* clockTimer;

private:
    QList<int> directPriority;

private:
    int elapseTime;

private:
    void updateGame();
    void restartGame();
    void setLevelChange(Difficulty level);

private:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

public:
    MazeGame(QWidget* parent = nullptr);  // 修改构造函数
    ~MazeGame();                          // 修改析构函数

public:
    void initialize();
};
#endif
