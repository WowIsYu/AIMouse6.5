#include "setup.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_setup.h"

#include <QStackedWidget>
#include <QFrame>
#include <QTimer>


SetUp::SetUp(QWidget *parent, HMultiControlSDK *MultiObj, VMouseMainWindow *main_vmouse)
    : QWidget(parent)
    , m_multiControl(MultiObj)
    , main_vmouse(main_vmouse)
    , ui(new Ui::SetUp)
{
    ui->setupUi(this);

    // 初始化静态库的资源（对应 nagano_res.qrc）
    Q_INIT_RESOURCE(nagano_res); // 注意：名称必须与 .qrc 文件名一致（不带扩展名）

    //返回由当前陀螺仪转化得到的坐标值
    connect(m_multiControl ,&HMultiControlSDK::emitGyroData
            ,this,&SetUp::onGyroData);
    // connect(m_multiControl ,&HMultiControlSDK::emitGyroData
    //         ,main_vmouse,&VMouseMainWindow::simulateMouseMove);

    //返回用户当前的眨眼检测结果（result: 1为有眨眼， 0为无）
    connect(m_multiControl, &HMultiControlSDK::notifyBlinkDetectionResult
            , this, &SetUp::onBlinkDetectionResult);
    connect(m_multiControl, &HMultiControlSDK::notifyBlinkDetectionResult
            ,this, &SetUp::onBlinkCheckResult);
    //返回用户当前的注意力检测结果
    connect(m_multiControl, &HMultiControlSDK::notifyAttenDetectionResult
            , this, &SetUp::onAttenDetectionResult);
    //发送注意力值给attentionShow
    attentionShow = new Nagano();
    connect(this, &SetUp::attentionResult
            , attentionShow, &Nagano::onReceiveResult);
    m_multiControl->launchCalibration(1, false);


    // 获取第二页（索引为 1）的部件
    // QWidget *secondPage = ui->stackedWidget->widget(1);

    // if (secondPage) {
    //     //frame_information 是 QFrame 的指针，且在第二页中
    //     QFrame *frameInformation = secondPage->findChild<QFrame *>("frame_information");
    //     if (frameInformation) {
    //         // frameInformation->setStyleSheet("background-color: red;");
    //         m_webView = new QWebEngineView(this);
    //         QStackedLayout* layout = new QStackedLayout(ui->frame);
    //         frameInformation->setLayout(layout);
    //         layout->addWidget(m_webView);
    //         // m_webView->load(QUrl("https://www.baidu.com"));

    //         QString filePath = "./person_infromation.html"; // 替换为你的相对路径
    //         m_webView->load(QUrl::fromLocalFile(QDir::current().absoluteFilePath(filePath)));
    //         m_webView->setZoomFactor(0.5); //缩放比例0.5
    //     }
    // }

}

SetUp::~SetUp()
{
    // delete m_webView;
    delete attentionShow;
    delete ui;
}

// 添加统计计算方法
void SetUp::calculateAttentionStats()
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

/**
* @brief onChooseBlueEvent 蓝牙选择
*/
// void SetUp::onChooseBlueEvent(hnnk::DataAppOperator type, QString name)
// {
//     m_multiControl->connectDevice(name);
//     qDebug() << "m_multiControlSDK连接成功， 连接的设备名为：" << name;
// }

void SetUp::onGyroData(double x, double y)
{
    globalPosx = x;
    globalPosy = y;
    main_vmouse->move(x,y);

}

void SetUp::on_horizontalSlider_valueChanged(int value)
{
    //坐标灵敏度，默认值为14
    ui->sensitivityLabel->setText(QString("灵敏度：%1").arg(value));
    m_multiControl->setSensitivity(value);
}


void SetUp::on_resetButton_clicked()
{
    m_multiControl->resetLocation();
}

void SetUp::onBlinkDetectionResult(int val)
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
void SetUp::onAttenDetectionResult(double val)
{
    double val2=val*100;
    ui->resultLabel->setText(QString::number(val2,'f', 0));

    if (m_isDetecting) {
        attentionValues.append(val2);
    }

    emit attentionResult(val);
}


void SetUp::on_beginButton_clicked()
{
    QString errMsg;
    // 获取最近生成的用户模型名
    m_modelName = getLastModelFile();

    // 记录开始时间
    startTime = QDateTime::currentDateTime();
    m_detectionTimer.start();

    // 调用SDK启动算法检测
    if (ui->userModeBtn->isChecked()) // 使用用户模型算法
        errMsg = m_multiControl->launchBlinkDetection(1, m_modelName);
    else if (ui->bigDataBtn->isChecked()) // 使用大数据模型算法
        errMsg = m_multiControl->launchBlinkDetection(2);
    else
        errMsg = "未指定算法类别";

    m_multiControl->resetLocation();
    emit sendToStatusBar(errMsg);
    qDebug() << m_modelName << "我是用户模型名";


    m_isDetecting = true;
    attentionValues.clear();
}



void SetUp::on_stopButton_clicked()
{
    // 调用SDK停止算法检测
    m_multiControl->stopBlinkDetection();
    emit sendToStatusBar("算法检测已停止");

    // 记录结束时间
    endTime = QDateTime::currentDateTime();
    m_isDetecting = false;

    if (!attentionValues.isEmpty()) {
        calculateAttentionStats();
        // 插入到数据库
        insertAttentionRecord("user01", startTime, endTime, averageAttention, minAttention, maxAttention, medianAttention);
    }
}

// 插入注意力记录的辅助函数
void SetUp::insertAttentionRecord(const QString &account, const QDateTime &startTime, const QDateTime &endTime,
                                  qreal averageAttention, qreal minAttention, qreal maxAttention, qreal medianAttention)
{
    QSqlQuery query;
    query.prepare("INSERT INTO attention_records (account, start_time, end_time, average_attention, min_attention, max_attention, median_attention) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(account);
    query.addBindValue(startTime.toString(Qt::ISODate));
    query.addBindValue(endTime.toString(Qt::ISODate));
    query.addBindValue(averageAttention);
    query.addBindValue(minAttention);
    query.addBindValue(maxAttention);
    query.addBindValue(medianAttention);

    if (!query.exec()) {
        qDebug() << "Error: failed to insert attention record -" << query.lastError();
    }
    emit updateDatabase();
}


QString SetUp::getLastModelFile()
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

void SetUp::on_pushButton_clicked()
{
    attentionShow->show();
}

void SetUp::onBlinkCheckResult(int val)
{
    if(val > 0){
        qDebug()<<"onBlinkCheckResult "<<val;
        //m_colorSwithing.doColorSwitching(ui->label_blink);
        if(1 == val)
        {
            qDebug() << "单眨眼";
        }
            //ui->blinktimes->setText(u8"单眨眼");
        else
        {
            qDebug() << "双眨眼";
        }
            //ui->blinktimes->setText(u8"双眨眼");
    }
}


void SetUp::on_btnSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void SetUp::on_btnInfo_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void SetUp::on_btnQuestion_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void SetUp::on_btnAbout_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

