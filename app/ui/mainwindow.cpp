#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QRect>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QThread>
// #include <qhotkey.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process = new QProcess(this);
    // QHotkey *hotkey = new QHotkey(QKeySequence(Qt::CTRL + Qt::Key_G), true, this);
    // connect(hotkey, &QHotkey::activated, this, [this] () {
    //     m_multiControl->resetLocation();
    //     qDebug() << "坐标回正";
    // });

    // 打开数据库连接
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("attention_data.db");
    if (!db.open()) {
        qDebug() << "Error: unable to open database";
        return;
    }

    //SDK初始化
    m_multiControl = new HMultiControlSDK(parent);
    qDebug() << "m_multiControl 已创建单例";
    //设置License
    m_multiControl->setLicense("c180dec8f4d94af6be5860436ca26003");
    qDebug() << "m_multiControl 已设置License授权码";
    //启动数据采集模块
    m_multiControl->lauchCollector(DATA_FIRSTGENERAL, hnnk::NET_COM);     //选择协议
    qDebug() << "m_multiControl 已初始化数据采集模块";
    //登录界面
    m_login = new Login(m_multiControl);
    qDebug() << "MainWindow:Login 已创建实例";

    connect(m_login, &Login::onLoginClose, []() {
        // qDebug() << "关闭窗口";
        // qApp->quit();
        exit(0);
    });

    // 连接信号和槽
    connect(m_login, &Login::notifyLoginResult, this, &MainWindow::onLoginSuccess);


}

MainWindow::~MainWindow()
{
    db.close();

    // 安全释放资源
    if (waveFormUi) delete waveFormUi;
    if (blinkCaliUi) delete blinkCaliUi;
    if (greedySnakeGameUi) delete greedySnakeGameUi;
    if (attention) delete attention;
    if (setUpUi) delete setUpUi;
    if (btnGroup) delete btnGroup;
    // if (main_vmouse) delete main_vmouse;
    // if (m_pchooseWindow) delete m_pchooseWindow;

    delete ui;
}


void MainWindow::initConnections() {

    connect(m_pchooseWindow, &ChooseDevice::checkSignal, [this](hnnk::DataAppOperator dataOperator, const QString& name){
        m_multiControl->connectDevice(name);
    });

    // 获取各个控件的信息
    connect(blinkCaliUi, &BlinkCalibration::sendToStatusBar, this, &MainWindow::on_statusBar);
    connect(setUpUi, &SetUp::sendToStatusBar, this, &MainWindow::on_statusBar);
    connect(this, &MainWindow::emitChangeDevice_waveform, waveFormUi, &Waveform::onChooseBlueEvent);
    connect(setUpUi, &SetUp::updateDatabase, this, &MainWindow::drawBar);

}

void MainWindow::initUI() {

    setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明化
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏最大最小化等按键

    btnGroup = new QButtonGroup(this);
    ui->stackedWidget->addWidget(waveFormUi);       //将五个界面添加到ui的stacked中
    ui->stackedWidget->addWidget(blinkCaliUi);//waveFromUi界面的index为0, 后面依次递增
    ui->stackedWidget->addWidget(greedySnakeGameUi);
    ui->stackedWidget->addWidget(setUpUi);
    ui->stackedWidget->addWidget(attention);
    // ui->stackedWidget->addWidget();

    btnGroup->addButton(ui->btnWaveform, 0);         //将五个按钮都添加到btnGroup中，便于管理
    btnGroup->addButton(ui->btnBlink, 1);
    btnGroup->addButton(ui->btnGame, 2);
    btnGroup->addButton(ui->btnSet, 3);
    btnGroup->addButton(ui->btnAttention, 4);
    // btnGroup->addButton(ui->btnAI, 5);

    connect(btnGroup, &QButtonGroup::idClicked          //将按钮和width界面用信号槽连接，以达到变换界面
            , ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    btnGroup->button(0)->setChecked(true);              //设置默认选中的页面
    ui->stackedWidget->setCurrentIndex(0);

    QPixmap pixmap(":/img/close.png");
    QIcon ButtonIcon(pixmap.scaled(ui->btn_close->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 按钮大小适应
    ui->btn_close->setIcon(ButtonIcon);
    ui->btn_close->setIconSize(ui->btn_close->size()); // 设置图标大小为按钮大小
    connect(ui->btn_close, &QPushButton::clicked, [this]() {
        this->setVisible(false);
    });

    // ui->btn_min->setFixedSize(20, 20);
    QPixmap pixmapMin(":/img/min.png");
    QIcon ButtonIconMin(pixmapMin.scaled(ui->btn_min->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 按钮大小适应
    ui->btn_min->setIcon(ButtonIconMin);
    ui->btn_min->setIconSize(ui->btn_min->size()); // 设置图标大小为按钮大小

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

// 简化鼠标事件处理
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_leftMousePressed = true;
        m_StartPoint = event->globalPos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_leftMousePressed) {
        QPoint delta = event->globalPos() - m_StartPoint;
        move(pos() + delta);
        m_StartPoint = event->globalPos();
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_leftMousePressed = false;//释放鼠标，标志位置为假
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    // if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_G) {
    //     m_multiControl->resetLocation();
    //     qDebug() << "坐标回正";
    // }
}

/**
 * 入口
 * @brief MainWindow::initMainWindow
 */
void MainWindow::initMainWindow()
{
    //进入页面时显示登录界面
    m_login->setWindowModality(Qt::ApplicationModal);
    m_login->setWindowFlags(m_login->windowFlags() | Qt::WindowStaysOnTopHint);
    m_login->show();
    m_login->raise();
    this->hide();
}

void MainWindow::onLoginSuccess()
{
    qDebug() << "登录成功";

    m_login->setStatusBar("正在加载页面，请稍后");
    QCoreApplication::processEvents(); // 处理事件
    // 实例化
    // m_dataSystemSDK = new hnnk::HDataSystem_interface();
    m_multiControl->m_dataSystem->initEegDataCollectorEnv((DSPROTOCOLTYPE)1, (DSNETTYPE)1);

    //工具类
    m_pchooseWindow = new ChooseDevice();
    main_vmouse = new VMouseMainWindow();

    // Ui界面
    waveFormUi = new Waveform(this, m_multiControl->m_dataSystem, m_pchooseWindow);
    blinkCaliUi = new BlinkCalibration(this, m_multiControl);
    setUpUi = new SetUp(this, m_multiControl, main_vmouse);
    greedySnakeGameUi = new GreedySnakeGame(this, m_multiControl);
    attention = new Attention(this);

    initConnections();
    initUI();

    m_login->setStatusBar("界面已加载完毕，欢迎使用！");

    // 延迟 1 秒后隐藏登录窗口并显示主窗口
    QTimer::singleShot(500, this, [this] {
        m_login->hide();
        this->show();
    });

}

void MainWindow::on_statusBar(QString message) {
    ui->statusBar->showMessage(message, 5000);
}

void MainWindow::drawBar()
{
    attention->loadDataFromDatabase();
    attention->drawBarChartForWeek(QDate::currentDate(), true);

}


void MainWindow::on_btnAI_clicked()
{
    // 启动可执行文件
    QString program = "AI.xyz_v1.2.0/AIxyz.exe";
    qDebug() << "Current directory: " << QDir::current().absolutePath();

    // 将工作目录设为mario文件夹
    process->setWorkingDirectory("AI.xyz_v1.2.0");

    process->start(program);

}

