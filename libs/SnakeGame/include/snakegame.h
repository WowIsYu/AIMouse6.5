#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>

#include <QTimer>
#include <QQueue>
#include <QKeyEvent>
#include <QFile>
#include <QList>

#include "rankdialog.h"


namespace Ui {
class SnakeGame;
}

class SnakeGame : public QWidget
{
    Q_OBJECT

public:
    explicit SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

protected:
    void paintEvent(QPaintEvent *);             //绘图事件
    void keyPressEvent(QKeyEvent *event);       //键盘按动事件
private slots:


    void on_btnBegin_clicked();

    void on_btnPause_toggled(bool checked);

    void on_btnRelnit_clicked();

    void on_btnRank_clicked();

    void setHardLevel();                        //设置难度水平

    void timeout();                             //超时

public slots:
    void onGyroData(double x, double y);
    void onAttenDetectionResult(double val);
private:
    Ui::SnakeGame *ui;
    void generateFood();                    //产生食物
    void initGame();                        //初始化界面
    void gameOver();                        //结束游戏
    enum Role                               //可选的棋盘格状态
    {
        NOTHING,SNAKEBODY,SNAKEHEAD,WALL,FOOD           //空白格， 蛇身， 蛇头， 墙， 食物
    };
    enum Direction
    {
        UP, DOWN, LEFT, RIGHT                           //上下左右移动
    };
    Role **board;                                       //用于存储整个棋盘
    QQueue<QPoint>snake;                                //用点坐标队列表示蛇身
    int cellNumX, cellNumY;                             //棋盘x, y方向上的格子数
    int cellLengthX, cellLengthY;                       //一个格子的长和宽
    Direction direct, newDirect;                        //当前蛇前进的方向， 即将要前进的方向

    int hardLevel = 2;                                  //当前难度水平
    QTimer *timer;                                      //定时器
    int foodNum = 0;                                    //总吃到的食物数

    QString rankFile;                                   //排行榜文件
    RankDialog *rankDlg;                              //排行版窗口

    QColor colorBody;                               //蛇身体颜色
    QColor colorHead;

    int footNumber = 1;         //吃foot后增加的身高
};

#endif // SNAKEGAME_H
