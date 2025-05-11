#include "gamewidget.h"
#include "ui/ui_gamewidget.h"
#include "ui_gamewidget.h"
#include "snakegame.h"
#include <QDir>
#include <QByteArray>
#include "views/mazeGame.h"
GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    ,
    ui(new Ui::GameWidget)
{

    // 初始化静态库的资源（对应 nagano_res.qrc）
    Q_INIT_RESOURCE(maze_res); // 注意：名称必须与 .qrc 文件名一致（不带扩展名）

    ui->setupUi(this);
    process = new QProcess(this);
    p_mario = new QProcess(this);
    timer = new QTimer(this);
}

GameWidget::~GameWidget()
{
    process->close();
    p_mario->close();
    delete ui;
}

void GameWidget::on_btn_GreedySnakeGame_clicked()
{
    qDebug() << "GreedySnakeGame";
    SnakeGame *w = new SnakeGame();
    QIcon subIcon(":/img/snake.ico");
    w->setWindowIcon(subIcon);

    //返回由当前陀螺仪转化得到的坐标值
    // connect(m_multiControl ,&HMultiControlSDK::emitGyroData
    //         ,w,&SnakeGame::onGyroData);
    // //返回用户当前的注意力检测结果
    // connect(m_multiControl, &HMultiControlSDK::notifyAttenDetectionResult
    //         , w, &SnakeGame::onAttenDetectionResult);

    w->show();
    w->setAttribute(Qt::WA_DeleteOnClose);  // 窗口关闭时自动删除
}

void GameWidget::on_btn_BlackPuzzle_clicked()
{
    qDebug() << "GreedySnakeGame";
    MazeGame *w = new MazeGame();
    // QIcon subIcon(":/img/snake.ico");
    // w->setWindowIcon(subIcon);
    w->initialize();

    w->show();
    w->setAttribute(Qt::WA_DeleteOnClose);  // 窗口关闭时自动删除
}



void GameWidget::onAttenDetectionResult(double val) {
    // 复制给 attention，便于传送注意力值给 process
    attention = static_cast<int>(val * 100);
    qDebug() << "Updated attention" << attention;
}

void GameWidget::onGyroData(double x, double y)
{
    this->x = x;
    this->y = y;
    qDebug() << "Updated GyroData" << x << y;
}

void GameWidget::onBlinked(int blinkValue)
{
    this->blinked = blinkValue > 0 ? true : false;
    qDebug() << "Updated blinked:" << blinked;
}

void GameWidget::onMonthAttention(double attentionValue)
{
    this->monthAttention = attentionValue;
    qDebug() << "Updated monthAttention";
}


void GameWidget::onDirection(double x, double y)
{
    // 获取当前屏幕
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // 计算中心点
    double centerX = screenWidth / 2.0;
    double centerY = screenHeight / 2.0;

    // QLabel *centerLabel = new QLabel(this);

    // centerLabel->setText("+");
    // centerLabel->setAlignment(Qt::AlignCenter);

    // // 设置标签大小
    // centerLabel->setFixedSize(20, 20);  // 例如大小为20x20的正方形

    // // 将控件移动到窗口的中心
    // centerLabel->move(centerX, centerY);
    // centerLabel->show();

    qDebug() << "中心点：" << centerX << centerY;
    qDebug() << x << y;

    double dx = x - centerX;  // X方向上的偏移量
    double dy = y - centerY;  // Y方向上的偏移量

    // 调整阈值：可以根据屏幕分辨率动态调整
    double thresholdX = 0.1;   // 比如设为屏幕宽度的5%
    double thresholdY = 0.1;  // 设为屏幕高度的5%

    // 优先判断X方向
    if (std::abs(dx) > std::abs(dy)) {
        if (dx > thresholdX) {
            // newDirect = RIGHT;
            isLeft = false;
        } else if (dx < -thresholdX) {
            // newDirect = LEFT;
            isLeft = true;
        }
    }
    // 如果Y方向偏移更大，则判断Y方向
    else {
        if (dy > thresholdY) {
            // newDirect = DOWN;
            isUp = false;
        } else if (dy < -thresholdY) {
            // newDirect = UP;
            isUp = true;
        }
    }

}



void GameWidget::on_btn_mario_clicked()
{

    // 启动可执行文件
    QString program = "ExtraApp/mario/mario_level_1.exe";
    qDebug() << "Current directory: " << QDir::current().absolutePath();

    // 将工作目录设为mario文件夹
    p_mario->setWorkingDirectory("mario");

    p_mario->start(program);

    // if (!p_mario->waitForStarted()) {
    //     qDebug() << "Failed to start process:" << p_mario->errorString();
    // }

    qDebug() << "p_mario started successful.";

}

