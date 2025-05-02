#include "snakegame.h"
#include "ui_snakegame.h"

#include <QRandomGenerator> //qsrand头文件

#include <QPainter>
#include <QTimer>
#include <QTime>

#include <QInputDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

SnakeGame:: SnakeGame(QWidget *parent):
    QWidget(parent),
    ui(new Ui::SnakeGame)
{
    ui->setupUi(this);
    //设置初始参数
    qDebug() << "enter game";
    cellNumX = cellNumY = 40;               //设置格子数， 每个格子的宽度
    cellLengthX = cellLengthY = 15;

    rankFile = "score.txt";                 //设置排行榜
    rankDlg = new RankDialog(this, rankFile);

    timer= new QTimer(this);                                    //设置定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    connect(ui->radioEasy, SIGNAL(clicked()), this, SLOT(setHardLevel()));          //连接radio和设置难度水平
    connect(ui->radioMid, SIGNAL(clicked()), this, SLOT(setHardLevel()));
    connect(ui->radioHard, SIGNAL(clicked()), this, SLOT(setHardLevel()));

    resize(100 + 40 + cellNumX * cellLengthX, 20 + cellNumY * cellLengthY);     //设置窗口大小(宽，高)

    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);            //禁止最大化按钮
    setFixedSize(this->width(), this->height());                            //禁止拖动窗口大小

    //申请棋盘存储空间， 动态二位数组 cellNumX * cellNumY
    board = new Role *[cellNumX];                                   //设置行指针， 这里的指针指向每一个行
    for (int i = 0; i < cellNumX; i++)
        board[i] = new Role[cellNumY];                              //设置行指针的列指针， 指向一行的一个具体的数
    initGame();
}

SnakeGame::~SnakeGame() {
    delete ui;
    for (int i = 0; i < cellNumX; i++)
        delete board[i];
    delete board;
}

void SnakeGame::initGame()
{
    foodNum = 0;                        //吃到的总食物数
    ui->lcdNumber->display(foodNum);    //初始化LCD显示
    direct = newDirect = RIGHT;         //蛇当前前进的方向， 下一次前进方向的初始值

    ui->radioMid->setChecked(true);
    ui->btnBegin->setEnabled(true);
    ui->btnPause->setDisabled(true);
    ui->btnRelnit->setDisabled(true);

    for (int i = 0; i < cellNumX - 1; i++)          //设置空白格
        for (int j = 0; j < cellNumY - 1; j++)
            board[i][j] = NOTHING;
    for (int i = 0; i < cellNumX; i++)              //设置墙
    {
        board[i][0] = WALL;
        board[i][cellNumY - 1] = WALL;
        board[0][i] = WALL;
        board[cellNumX - 1][i] = WALL;
    }
    snake.clear();
    snake.enqueue(QPoint(1, cellNumY/2));
    snake.enqueue(QPoint(2, cellNumY/2));
    snake.enqueue(QPoint(3, cellNumY/2));           //蛇头在队列尾
    board[1][cellNumY/2] = SNAKEBODY;
    board[2][cellNumY/2] = SNAKEBODY;
    board[3][cellNumY/2] = SNAKEBODY;
    // colorBody.setRgb(50, 130, 246);
    // colorHead.setRgb(Qt::darkBlue);
    colorBody.setRgb(240, 135,132);
    colorHead.setRgb(235, 51, 36);
    generateFood();
    update();                                       //触发paintEvent
}


void SnakeGame::generateFood()
{
    // 创建一个 QRandomGenerator 实例并设置种子
    QRandomGenerator randomGenerator(QTime::currentTime().msec());

    do
    {
        int x = 1 + randomGenerator.bounded(cellNumX - 1);
        int y = 1 + randomGenerator.bounded(cellNumY - 1);
        if (board[x][y] == NOTHING)
        {
            board[x][y] = FOOD;
            break;
        }
    } while(true);
}

void SnakeGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush brush(Qt::SolidPattern);         //全刷模式
    for (int i= 0; i < cellNumX; i++)
        for (int j = 0; j < cellNumY; j++)
        {
            switch(board[i][j])
            {
            case NOTHING:
                brush.setColor(QColor(211,211,211));    //浅黄色
                break;
            case WALL:
                brush.setColor(QColor(84,84,84));
                break;
            case SNAKEBODY:
                brush.setColor(colorBody);         //蛇身颜色
                //brush.setColor(QColor(50, 130, 246));
                break;
            case SNAKEHEAD:
                brush.setColor(colorHead);               //蛇头颜色
                //brush.setColor(Qt::darkBlue);
                break;
            case FOOD:
                brush.setColor(Qt::blue);
                break;
            }
            painter.setBrush(brush);
            painter.drawRect(100 + 20 + i* cellLengthX, 10 + j * cellLengthY, cellLengthX, cellLengthY);
        }
    ui->lcdNumber->display(foodNum);
}

void SnakeGame::setHardLevel()
{
    if (ui->radioEasy->isChecked())
        hardLevel = 2;
    else if (ui->radioMid->isChecked())
        hardLevel = 4;
    else
        hardLevel = 8;

    timer->setInterval(1000/hardLevel);         //设置时间间隔
}

void SnakeGame::on_btnBegin_clicked()
{
    setHardLevel();
    timer->start(1000/hardLevel);       //设置时间

    ui->btnBegin->setDisabled(true);        //解封按钮
    ui->btnPause->setEnabled(true);
    ui->btnRelnit->setEnabled(true);
}


void SnakeGame::on_btnPause_toggled(bool checked)
{
    if (checked)
    {
        timer->blockSignals(true);
        ui->btnPause->setText("继续");
    }
    else
    {
        timer->blockSignals(false);
        ui->btnPause->setText("暂停");
    }
}


void SnakeGame::on_btnRelnit_clicked()
{
    timer->stop();
    initGame();
}


void SnakeGame::on_btnRank_clicked()
{
    if (rankDlg == nullptr)
        rankDlg = new RankDialog(this, rankFile);

    QIcon subIcon(":/img/phb.ico");
    rankDlg->setWindowIcon(subIcon);
    rankDlg->rankAndShow();
}

void SnakeGame::timeout()
{
    QPoint delPoint;                    //蛇身上要删除的点
    QPoint snakeHead = snake.last();    //蛇头
    int newCellX = snakeHead.x();
    int newCellY = snakeHead.y();
    switch(direct)                      //更新当前方向， 如果更新的方向是自己身体的方向， 则不改变方向
    {
    case UP:
        if (newDirect != DOWN)
            direct = newDirect;
        break;
    case DOWN:
        if (newDirect != UP)
            direct = newDirect;
        break;
    case LEFT:
        if (newDirect != RIGHT)
            direct = newDirect;
        break;
    case RIGHT:
        if (newDirect != LEFT)
            direct = newDirect;
        break;
    }

    switch(direct)          //设置新蛇头的坐标
    {

    case UP:
        newCellY -= 1;
        break;
    case DOWN:
        newCellY += 1;
        break;
    case LEFT:
        newCellX -= 1;
        break;
    case RIGHT:
        newCellX += 1;
        break;
    }

    switch(board[newCellX][newCellY])
    {
    case WALL:                                  //如果撞墙等，结束游戏
    case SNAKEHEAD:
    case SNAKEBODY:
        gameOver();
        break;
    case NOTHING:                               //如果没有，则设置蛇，删除蛇尾， 添加蛇头，（这两部就是移动了一格，不吃food）
        snake.enqueue(QPoint(newCellX, newCellY));
        delPoint = snake.dequeue();
        board[snakeHead.x()][snakeHead.y()] = SNAKEBODY;
        board[newCellX][newCellY] = SNAKEHEAD;
        board[delPoint.x()][delPoint.y()] = NOTHING;
        break;
    case FOOD:                                  //吃了food就不需要删除蛇尾
        snake.enqueue(QPoint(newCellX, newCellY));
        board[snakeHead.x()][snakeHead.y()] = SNAKEBODY;
        board[newCellX][newCellY] = SNAKEHEAD;
        foodNum+= footNumber;
        generateFood();
        break;
    }
    update();
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Down:
        newDirect = DOWN;
        break;
    case Qt::Key_Up:
        newDirect = UP;
        break;
    case Qt::Key_Left:
        newDirect = LEFT;
        break;
    case Qt::Key_Right:
        newDirect = RIGHT;
        break;
    }
}

void SnakeGame::gameOver()
{
    timer->stop();
    QString playerName = QInputDialog::getText(this, "游戏结束", "请输入玩家姓名：");
    if (!playerName.isEmpty())
    {
        QFile file(rankFile);
        if (!file.exists())
        {
            file.open(QIODevice::ReadWrite|QIODevice::Text);
            QTextStream stream(&file);
            stream << " " << playerName << " " << foodNum;
            file.close();
        }
        else if ( !file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
        {
            QMessageBox::information(this, "提示", "排行版文件打开失败");
        }
        else
        {
            QTextStream stream(&file);
            stream << " " << playerName << " " << foodNum;
            file.close();
        }
    }
    initGame();
}

void SnakeGame::onGyroData(double x, double y)
{
    // 获取当前屏幕
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // 计算中心点
    double centerX = screenWidth / 2.0;
    double centerY = screenHeight / 2.0;

    QLabel *centerLabel = new QLabel(this);

    centerLabel->setText("+");
    centerLabel->setAlignment(Qt::AlignCenter);

    // 设置标签大小
    centerLabel->setFixedSize(20, 20);  // 例如大小为20x20的正方形

    // 将控件移动到窗口的中心
    centerLabel->move(centerX, centerY);
    centerLabel->show();

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
            newDirect = RIGHT;
        } else if (dx < -thresholdX) {
            newDirect = LEFT;
        }
    }
    // 如果Y方向偏移更大，则判断Y方向
    else {
        if (dy > thresholdY) {
            newDirect = DOWN;
        } else if (dy < -thresholdY) {
            newDirect = UP;
        }
    }

    qDebug() << "New Direction:" << newDirect;
}

/**
 * 获取注意力值并做相应处理
 * @brief SnakeGame::onAttenDetectionResult
 * @param val
 */
void SnakeGame::onAttenDetectionResult(double val) {
    ui->label_2->setText(QString::number(val));
    double val1 = val * 100;
    if (val1 <= 30) {
        colorBody.setRgb(255, 254, 145);
        colorHead.setRgb(255, 253, 85);
        footNumber = 1;
    } else if (val1 <= 60) {
        colorBody.setRgb(15, 251, 253);
        colorHead.setRgb(50, 130, 246);
        footNumber = 2;
    } else {
        colorBody.setRgb(240, 135,132);
        colorHead.setRgb(235, 51, 36);
        footNumber = 4;
    }
}


