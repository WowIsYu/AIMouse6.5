#include "views/mazeGame.h"

#include "ui_mazeGame.h"



MazeGame::MazeGame(QWidget* parent): QMainWindow(parent), ui(new Ui::MazeGame)
{
    frameTimer = new QTimer(this);
    clockTimer = new QTimer(this);

    //游戏框架
    gameFramework = new GameFramework();
    // 游戏图形类，比如游戏玩家图片
    gameResources = new GameResources();
    // 成功对话框
    successDialog = new SuccessDialog(this);

    ui->setupUi(this);
    ui->sceneWidget->setGameFramework(gameFramework);
    ui->sceneWidget->setGameResources(gameResources);
}

MazeGame::~MazeGame()
{
    delete ui;
    delete successDialog;
    delete frameTimer;
    delete clockTimer;
    delete gameFramework;
    delete gameResources;
}

void MazeGame::initialize()
{
    connect(frameTimer, &QTimer::timeout, this, [=]
    {
        updateGame();
    });

    connect(clockTimer, &QTimer::timeout, this, [=]
    {
        if (gameFramework->isPlaying())
        {
            elapseTime += 1;
        }
    });

    connect(ui->restartButton, &QPushButton::clicked, this, [=]
    {
        restartGame();
    });

    connect(ui->fogButton, &QPushButton::clicked, this, [=]
    {
        gameFramework->switchFogMode();
    });

    connect(ui->trackButton, &QPushButton::clicked, this, [=]
    {
        ui->sceneWidget->updateWayBlocks();
    });

    connect(ui->btnLow, &QPushButton::clicked, this, [=]
    {
        setLevelChange(Difficulty::Low);
    });

    connect(ui->btnMed, &QPushButton::clicked, this, [=]
    {
        setLevelChange(Difficulty::Medium);
    });

    connect(ui->btnHigh, &QPushButton::clicked, this, [=]
    {
        setLevelChange(Difficulty::High);
    });

    restartGame();

    frameTimer->setInterval(TimerInterval::FRAME);
    frameTimer->start();

    clockTimer->setInterval(TimerInterval::CLOCK);
    clockTimer->start();
}

void MazeGame::updateGame()
{
    if (gameFramework->isPlaying())
    {
        gameFramework->playerMove(directPriority);

        if (gameFramework->isGameover())
        {
            successDialog->setInfo(elapseTime, gameFramework->hasTracked());

            if (successDialog->exec() == 0)
            {
                restartGame();
            }
        }
        ui->timeValueLabel->setNum(elapseTime);
    }
    ui->sceneWidget->update();
}

void MazeGame::restartGame()
{
    gameFramework->restart();
    directPriority.clear();
    elapseTime = 0;
    ui->sceneWidget->clearWayBlocks();
}

void MazeGame::keyPressEvent(QKeyEvent* event)
{
    int pressedKey = event->key();

    if (pressedKey == Qt::Key_W)
    {
        directPriority.append(Directs::UP);
    }
    else if (pressedKey == Qt::Key_S)
    {
        directPriority.append(Directs::DOWN);
    }
    else if (pressedKey == Qt::Key_A)
    {
        directPriority.append(Directs::LEFT);
    }
    else if (pressedKey == Qt::Key_D)
    {
        directPriority.append(Directs::RIGHT);
    }
}

void MazeGame::keyReleaseEvent(QKeyEvent* event)
{
    int pressedKey = event->key();

    if (pressedKey == Qt::Key_W)
    {
        directPriority.removeAll(Directs::UP);
    }
    else if (pressedKey == Qt::Key_S)
    {
        directPriority.removeAll(Directs::DOWN);
    }
    else if (pressedKey == Qt::Key_A)
    {
        directPriority.removeAll(Directs::LEFT);
    }
    else if (pressedKey == Qt::Key_D)
    {
        directPriority.removeAll(Directs::RIGHT);
    }
}

void MazeGame::setLevelChange(Difficulty l) {

    //获取难度对应的设置
    DifficultySettings settings = getSettingsForDifficulty(l);

    //设置根据级别设置scale
    scale = settings.scale;
    gameResources->setScale(scale);
    ui->sceneWidget->setGameResources(gameResources);

    //根据级别设置地图尺寸
    MapProperties::applyDifficulty(settings);
    gameFramework->setMapSize(MapProperties::ROWS, MapProperties::COLS);

    //根据级别设置速度
    gameFramework->setPlayerSpeed(scale);

    restartGame();
}
