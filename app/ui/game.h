#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "HMultiControlSDK.h"
#include "qprocess.h"
using namespace hnnk;

namespace Ui {
class GreedySnakeGame;
}

class GreedySnakeGame : public QWidget
{
    Q_OBJECT

public:
    explicit GreedySnakeGame(QWidget *parent = nullptr, HMultiControlSDK *m_multiControl = nullptr);
    ~GreedySnakeGame();
    //多模态综合控制SDK
    HMultiControlSDK *m_multiControl = nullptr;

    // 创建 QProcess 对象, 用于打开VS黑暗迷宫
    QProcess *process = nullptr;
    QProcess *p_mario = nullptr;
    QTimer *timer = nullptr;

    // 获取attention的值
    int attention = 0;
    double x = 0;
    double y = 0;
    bool blinked = false;
    double monthAttention = 0;

    bool isLeft = false;
    bool isUp = false;


public slots:

    void onAttenDetectionResult(double val);
    void onGyroData(double x, double y);
    void onBlinked(int blinkValue);
    void onMonthAttention(double attentionValue);
    void onDirection(double x, double y);

private slots:
    void on_btn_GreedySnakeGame_clicked();

    void on_btn_BlackPuzzle_clicked();

    void on_btn_mario_clicked();

private:
    Ui::GreedySnakeGame *ui;
};

#endif // GAME_H
