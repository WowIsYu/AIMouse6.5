#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QRect>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QThread>
#include <qhotkey.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initDatabases();

    initMuitl();

    initLogin();


}

MainWindow::~MainWindow()
{
    // 安全释放资源
    if (waveFormUi) delete waveFormUi;
    if (blinkCaliUi) delete blinkCaliUi;
    if (greedySnakeGameUi) delete greedySnakeGameUi;
    if (attention) delete attention;
    if (setUpUi) delete setUpUi;
    if (btnGroup) delete btnGroup;
    if (main_vmouse) delete main_vmouse;
    if (m_pchooseWindow) delete m_pchooseWindow;

    delete ui;
}

void MainWindow::initDatabases() {
    dbManager = new DatabaseManager(this);
    if (!dbManager->initializeUserDatabase()) {
        qCritical() << "Failed to initialize User database!";
    }
    dbManager = new DatabaseManager(this);
    if (!dbManager->initializeHnnkDatabase()) {
        qCritical() << "Failed to initialize HnnkData database!";
    }

}

void MainWindow::initMuitl() {

    m_multiControl = new HMultiControlWrapper(this);
}

void MainWindow::initLogin() {
    //登录界面
    m_login = new Login();
    qDebug() << "MainWindow:Login 已创建实例";

    connect(m_login, &Login::onLoginClose, []() {
        // qDebug() << "关闭窗口";
        // qApp->quit();
        exit(0);
    });

    // 加载选择记住密码的用户
    loadRemembered();

    // 连接信号和槽
    connect(m_login, &Login::onInsertUser, this,&MainWindow::insertUser);

    //登录相关
    connect(m_login, &Login::emitLogin, this, &MainWindow::onLogin);
    connect(this, &MainWindow::emitLoginResult, m_login, &Login::onLoginResult);

    //注册相关
    connect(m_login, &Login::emitRegister, this, &MainWindow::onRegister);
    connect(this, &MainWindow::emitRegisterResult, m_login, &Login::onRegisterResult);

    //校验码
    connect(m_login, &Login::emitGraphCode, this, &MainWindow::onGraphCode);
    connect(this, &MainWindow::emitGraphCode, m_login, &Login::onGraphCode);
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

    initInstance();
    initConnections();

    initUI();

    //开启线程来开AI
    process = new QProcess(this);

    //开启热键
    QHotkey *hotkey = new QHotkey(QKeySequence(Qt::CTRL + Qt::Key_G), true, this);
    connect(hotkey, &QHotkey::activated, this, [this] () {
        m_multiControl->resetLocation();
        qDebug() << "坐标回正";
    });

    // 开启定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onUpdateBattaryStatus);

    m_login->setStatusBar("界面已加载完毕，欢迎使用！");

    // 延迟 1 秒后隐藏登录窗口并显示主窗口
    QTimer::singleShot(500, this, [this] {
        m_login->hide();
        this->show();
    });


}


void MainWindow::initConnections() {

    connect(this, &MainWindow::emitHnnkData, attention, &Attention::onHnnkData);
    connect(attention, &Attention::emitUpdateHnnkData, this, &MainWindow::onHnnkData);

    connect(m_pchooseWindow, &ChooseDevice::refreshList, this, &MainWindow::onSearchDeviceList);
    connect(m_pchooseWindow, SIGNAL(checkSignal(hnnk::DataAppOperator, QString )), this, SLOT(onChooseBlueEvent(hnnk::DataAppOperator, QString)));
    connect(m_multiControl, &HMultiControlWrapper::notifyDeviceNameUpdate, m_pchooseWindow, &ChooseDevice::onUpdateDeviceNameList);

    connect(m_multiControl, &HMultiControlWrapper::emitSearchNetDeviceOver, this, &MainWindow::onSearchOver);
    connect(m_pchooseWindow, &ChooseDevice::checkSignal, m_multiControl, &HMultiControlWrapper::connectDevice);
    connect(m_multiControl, &HMultiControlWrapper::emitMsgBox, this, &MainWindow::onMsg);
    connect(m_multiControl ,&HMultiControlWrapper::emitGyroData, this, &MainWindow::onGyroData);
    connect(m_multiControl, &HMultiControlWrapper::notifyBlinkDetectionResult, this, &MainWindow::onBlinkDetectionResult);
    connect(m_multiControl, &HMultiControlWrapper::notifyBlinkDetectionResult,this, &MainWindow::onBlinkCheckResult);
    connect(m_multiControl, &HMultiControlWrapper::notifyConnectState, [this]() {on_statusBar("设备已连接");}) ;
    connect(m_multiControl, &HMultiControlWrapper::notifyAttenDetectionResult
            , [this](double val) {
                if (m_isDetecting) {
                    attentionValues.append(val);
                }
                attentionShow->onReceiveResult(val);
     });

    connect(m_multiControl, &HMultiControlWrapper::notifyAttenDetectionResult, setUpUi, &SetUp::onAttenDetectionResult);
    connect(setUpUi, &SetUp::emitSetSensitivity, m_multiControl, &HMultiControlWrapper::setSensitivity);
    connect(setUpUi, &SetUp::emitStopBlinkDetection, this, &MainWindow::onStopBlinkDetection);
    connect(setUpUi, &SetUp::emitStartBlinkDetection, this, &MainWindow::onStartBlinkDetection);
    connect(setUpUi, &SetUp::emitShowAttention, this, &MainWindow::onShowAttention);

    connect(m_multiControl,&HMultiControlWrapper::notifyCaliTrigger, blinkCaliUi, &BlinkCalibration::onCaliTrigger);
    connect(m_multiControl, &HMultiControlWrapper::notifyCalibrationResult, blinkCaliUi, &BlinkCalibration::onCalibrationResult);
    connect(m_multiControl, &HMultiControlWrapper::notifyCalibrationResult, [this]() {on_statusBar("校准结束");});
    connect(blinkCaliUi, &BlinkCalibration::emitLaunchCali, this, &MainWindow::onLaunchCali);
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

void MainWindow::initInstance() {
    m_multiControl->initEegDataCollectorEnv((DSPROTOCOLTYPE)1, (DSNETTYPE)1);

    //工具类
    m_pchooseWindow = new ChooseDevice();
    main_vmouse = new VMouseMainWindow();

    // Ui界面
    waveFormUi = new Waveform(this, m_multiControl->m_dataSystem);
    blinkCaliUi = new BlinkCalibration(this);
    setUpUi = new SetUp(this);
    greedySnakeGameUi = new GreedySnakeGame(this);
    attention = new Attention(this);

    //注意力显示界面
    attentionShow = new Nagano(this);
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

void MainWindow::loadRemembered() {
    // 查找所有 savePassword=true 的用户，这里只取第一个
    auto users = dbManager->getAllUsers();
    for (const auto &u : std::as_const(users)) {
        qDebug() << u.addTime;
        if (u.savePassword) {
            // ui->editAccount->setText(u.account);
            // ui->editPassword->setText(u.password);
            // ui->chkRemember->setChecked(true);
            m_login->onLoadRemembered(u.account, u.account);
            break;
        }
    }

}

// 登录成功
void MainWindow::insertUser(QString acct, QString pwd, bool isChecked)
{

    // if (!dbManager->userExists(acct)) {
    //     QMessageBox::warning(this, "登录失败", "账号不存在");
    //     return;
    // }

    User newUser;
    newUser.account       = acct;
    newUser.password      = pwd;
    // newUser.nickname      = ui->editRegNickname->text();
    qint64 id = dbManager->insertUser(newUser);

    // 1）根据复选框更新记住密码标志
    bool wantRemember = isChecked;
    if (!dbManager->updateSavePassword(acct, wantRemember)) {
        qWarning() << "更新记住密码失败：" << dbManager->lastError().text();
    }
    this->account = acct;
    qDebug() << "account name:" << account;
    onLoginSuccess();
}

void MainWindow::insertHnnkData(const QString &account, const QDateTime &startTime, const QDateTime &endTime,
                                qreal averageAttention, qreal minAttention, qreal maxAttention, qreal medianAttention)
{
    HNNKData data;
    data.mid = 1;
    data.account = account;
    data.startTime = startTime;
    data.endTime = endTime;
    data.medValue = medianAttention;
    data.minValue = minAttention;
    data.maxValue = maxAttention;
    data.avgValue = averageAttention;
    data.event = "Start detect Attention value.";

    qint64 id = dbManager->insertHnnkData(data);
    if (id < 0) {
        QMessageBox::critical(this, "添加失败", dbManager->lastError().text());
    } else {
        QMessageBox::information(this, "添加成功", QString("您的数据ID：%1").arg(id));
        // 可自动跳转到登录页，并填写账号
    }
}


void MainWindow::onHnnkData() {
    QList<HNNKData> data = dbManager->getHnnkDataByAccount(account);
    emit emitHnnkData(data);
}

void MainWindow::onLogin(const QString accountName, const QString pwd,
                         const QString chaptcha, const QString imagId)
{
    qDebug() << "----------------------------------------------";
    QString m_token = m_multiControl->login(accountName, pwd, chaptcha, imagId);
    qDebug() << "----------------------------------------------";
    emit emitLoginResult(m_token);
}


void MainWindow::onRegister(const QString accountName, const QString pwd,
                         const QString chaptcha, const QString imagId)
{
    qDebug() << "----------------------------------------------";
    QString msgErr = m_multiControl->registAccounter(accountName, pwd, chaptcha, imagId);
    qDebug() << "----------------------------------------------";
    emit emitLoginResult(msgErr);
}

void MainWindow::onGraphCode()
{
    QPixmap pixMap;
    QString m_imgId;
    qDebug() << "----------------------------------------------";
    m_multiControl->getGraphValidateCode(pixMap, m_imgId);
    qDebug() << "----------------------------------------------";
    emit emitGraphCode(pixMap, m_imgId);
}
/**
 * 查找设备
 * @brief MainWindow::onSearchDeviceList
 */
void MainWindow::onSearchDeviceList()
{
    m_multiControl->searchDeviceList();
}

void MainWindow::onSearchOver()
{
    m_pchooseWindow->searchOver();
}

void MainWindow::onLaunchCali(int blinkInterval)
{
    QString errMsg = m_multiControl->launchCalibration(blinkInterval, false);

    on_statusBar(errMsg);
}

void MainWindow::onStartBlinkDetection(int choice)
{
    QString errMsg;
    // 获取最近生成的用户模型名
    m_modelName = getLastModelFile();

    // 记录开始时间
    startTime = QDateTime::currentDateTime();
    m_detectionTimer.start();

    // 调用SDK启动算法检测
    if (choice == 1) // 使用用户模型算法
        errMsg = m_multiControl->launchBlinkDetection(1, m_modelName);
    else if (choice == 2) // 使用大数据模型算法
        errMsg = m_multiControl->launchBlinkDetection(2);
    else
        errMsg = "未指定算法类别";

    on_statusBar(errMsg);

    m_isDetecting = true;
    attentionValues.clear();

}

void MainWindow::onStopBlinkDetection()
{
    // 调用SDK停止算法检测
    m_multiControl->stopBlinkDetection();
    on_statusBar("算法检测已停止");
    // 记录结束时间
    endTime = QDateTime::currentDateTime();
    m_isDetecting = false;

    if (!attentionValues.isEmpty()) {
        calculateAttentionStats();
        // 插入到数据库
        insertHnnkData(account, startTime, endTime, averageAttention, minAttention, maxAttention, medianAttention);
        drawBar();
    }
}

void MainWindow::onMsg(int type, QString msg)
{
    if(1 == type){
        m_pchooseWindow->setBluetoothEnable(false);
    }
    QMessageBox box;
    box.setText(msg);
    box.setDefaultButton(QMessageBox::Cancel);
    QTimer::singleShot(3000, &box, SLOT(accept()));
    box.exec();
    //m_pchooseWindow->setFlashText("刷新");
}


void MainWindow::onBlinkDetectionResult(int val)
{
    if(val > 0){
        qDebug()<<"onBlinkCheckResult "<<val;
        if(1 == val) qDebug() << "单眨眼";
        else qDebug() << "双眨眼";
    }
}

void MainWindow::onBlinkCheckResult(int val)
{
    if(val > 0){
        //main_vmouse->setStyleSheet("background-color:yellow");
        main_vmouse->setBgColor(Qt::yellow);
        QTimer::singleShot(500, this, [=](){
            //main_vmouse->setStyleSheet("background-color:red");
            main_vmouse->setBgColor(Qt::red);
            main_vmouse->simulateMouseClick(globalPosx, globalPosy);
            if(val != 1)        //眨两次眼
            {
                main_vmouse->simulateMouseClick(globalPosx, globalPosy);     //触发鼠标左键按下事件
            }
        });
    }
}

QString MainWindow::getLastModelFile()
{
    QString modelName;
    //读取默认的模型文件目录
    QDir modelDir = m_multiControl->getModelDir();
    qDebug() << modelDir;
    //读取默认最近的模型文件名
    modelDir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
    QList<QFileInfo> fileInfos = modelDir.entryInfoList(QDir::AllEntries, QDir::Time);
    if(fileInfos.size() > 2){
        for(auto it : fileInfos){
            if(it.isFile()){
                modelName = it.fileName();       //找到最近生成的文件
                break;
            }
        }
    }
    qDebug() << modelName;
    return modelName;
}

void MainWindow::calculateAttentionStats()
{
    Q_ASSERT(!attentionValues.isEmpty());

    // 使用STL算法计算
    auto [minIt, maxIt] = std::minmax_element(attentionValues.begin(), attentionValues.end());
    minAttention = *minIt;
    maxAttention = *maxIt;

    averageAttention = std::accumulate(attentionValues.begin(), attentionValues.end(), 0.0) /
                       attentionValues.size();

    // 计算中值
    std::sort(attentionValues.begin(), attentionValues.end());
    size_t size = attentionValues.size();
    medianAttention = (size % 2 == 0) ?
                          (attentionValues[size/2 - 1] + attentionValues[size/2]) / 2.0 :
                          attentionValues[size/2];
}


void MainWindow::onGyroData(double x, double y)
{
    globalPosx = x;
    globalPosy = y;
    main_vmouse->move(x,y);
}


void MainWindow::onUpdateBattaryStatus()
{
    int battary = m_multiControl->m_dataSystem->getParameter().m_battaryStatus;
    qDebug() << "battary" << battary;
    ui->barBattary->setValue(battary);
}


void MainWindow::onShowAttention()
{
    attentionShow->show();
}

void MainWindow::on_btnConnectDevice_clicked()
{
    m_pchooseWindow->showTopwindow();
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
