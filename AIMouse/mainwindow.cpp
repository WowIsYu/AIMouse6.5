#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    waveFormUi = new Waveform(this);          //分别给五个界面创造实例
    qDebug() << "MainWindow:waveFormUi 已创建实例";
    blinkCaliUi = new BlinkCalibration(this);
    qDebug() << "MainWindow:blinkCaliUi 已创建实例";
    // attentionUi = new Attention(this);
    // gameUi = new Game(this);
    setUpUi = new SetUp(this);
    qDebug() << "setUp:blinkCaliUi 已创建实例";

    btnGroup = new QButtonGroup(this);
    ui->stackedWidget->addWidget(waveFormUi);       //将五个界面添加到ui的stacked中
    ui->stackedWidget->addWidget(blinkCaliUi);//waveFromUi界面的index为0, 后面依次递增
    // ui->stackedWidget->addWidget(attentionUi);
    // ui->stackedWidget->addWidget(gameUi);
    ui->stackedWidget->addWidget(setUpUi);

    btnGroup->addButton(ui->btnWaveform, 0);         //将五个按钮都添加到btnGroup中，便于管理
    btnGroup->addButton(ui->btnBlink, 1);
    // btnGroup->addButton(ui->btnAttention, 2);
    // btnGroup->addButton(ui->btnGame, 3);
    btnGroup->addButton(ui->btnSet, 2);

    connect(btnGroup, &QButtonGroup::idClicked          //将按钮和width界面用信号槽连接，以达到变换界面
            , ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    btnGroup->button(0)->setChecked(true);              //设置默认选中的页面
    ui->stackedWidget->setCurrentIndex(0);


    m_multiControl = blinkCaliUi->m_multiControl;
    qDebug() << "blinkCail的multiControl传给mainWindow_m_multiControl实例化";
    //setUpUi->m_pchooseWindow = waveFormUi->m_pchooseWindow;
    //qDebug() << "waveFormUi->m_pchooseWindow传给setUpUi_choose实例化";
    blinkCaliUi->m_pchooseWindow = waveFormUi->m_pchooseWindow;
    qDebug() << "waveFormUi->m_pchooseWindow传给setUpUi_choose实例化";



    m_login = new Login(m_multiControl);
    //登录界面
    qDebug() << "login 中的m_multiControl实例化";
    connect(m_login, &Login::notifyLoginResult
            , this, &MainWindow::onLoginSuccess);



    //构建协议选择窗口
    //m_proWin = new InitDataSystemProtocol();
    //connect(m_proWin, &InitDataSystemProtocol::notifyClicked
    //        , blinkDetectionUi, &BlinkDetection::onRefreshList);
    //m_proWin->setModal(true);
    //connect(m_proWin, &InitDataSystemProtocol::button_Clicked
    //       , waveFormUi, &Waveform::lauchCollector);
    //登录成功后发送初始化信息给setUpUi
    connect(this, &MainWindow::emitInitSetUp
            , setUpUi, &SetUp::initSetUp);
    connect(this, &MainWindow::emitInitBlinkCail
            , blinkCaliUi, &BlinkCalibration::initBlinkCali);

}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    m_login->hide();
    this->show();
    //提供协议选择窗口
    //m_proWin->show();
    emit emitInitSetUp(m_multiControl);
    qDebug() << "MainWindow的m_multiControl 传给 SetUoUi";
    emit emitInitBlinkCail();
}
