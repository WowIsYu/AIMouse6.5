#include "setup.h"
#include "ui_setup.h"

SetUp::SetUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetUp)
{
    ui->setupUi(this);
    //为方便显示陀螺仪坐标结果，设置一个虚拟光标图标
    main_vmouse = new VMouseMainWindow();
    qDebug() << "SetUp: main_vmouse已创建实例";
}

SetUp::~SetUp()
{
    delete ui;
}

void SetUp::initSetUp(HMultiControlSDK *MultiObj)
{
    m_multiControl = MultiObj;      //初始化
    // connect(m_pchooseWindow, SIGNAL(checkSignal(hnnk::DataAppOperator, QString ))       //确认设备的发送信号
    //         , this, SLOT(onChooseBlueEvent(hnnk::DataAppOperator, QString)));

    //返回由当前陀螺仪转化得到的坐标值
    connect(m_multiControl ,&HMultiControlSDK::emitGyroData
          ,this,&SetUp::onGyroData);

    //返回用户当前的眨眼检测结果（result: 1为有眨眼， 0为无）
    connect(m_multiControl, &HMultiControlSDK::notifyBlinkDetectionResult
            , this, &SetUp::onBlinkDetectionResult);
    connect(m_multiControl, &HMultiControlSDK::notifyBlinkDetectionResult
            ,this, &SetUp::onBlinkCheckResult, Qt::UniqueConnection);
    qDebug()<<"MainWidget::on_m_pbBlinkStart_clicked "<<1 << m_modelName;
    QString a = m_multiControl->launchBlinkDetection(1, "local_model_blinkcheck2024_09_07_14_55_33_34.json");
    qDebug() << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << a;
    //返回用户当前的注意力检测结果
    connect(m_multiControl, &HMultiControlSDK::notifyAttenDetectionResult
            , this, &SetUp::onAttenDetectionResult);
    //发送注意力值给attentionShow
    attentionShow = new AttentionShow();
    connect(this, &SetUp::attentionResult
            , attentionShow, &AttentionShow::onReceiveResult);
    m_multiControl->launchCalibration(1, false);
}

//void onSearchDevice();
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
            //main_vmouse->simulateMouseClick(globalPosx, globalPosy);
            if(val != 1)        //炸两次眼
            {
                main_vmouse->simulateMouseClick(globalPosx, globalPosy);     //触发鼠标左键按下事件
            }
        });
    }
    qDebug() << "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" + QString::number(val);
}
void SetUp::onAttenDetectionResult(double val)
{
    double val2=val*100;
    ui->resultLabel->setText(QString::number(val2,'f', 0));
    emit attentionResult(val);
}


void SetUp::on_beginButton_clicked()
{
    QString errMsg;
    //获取最近生成的用户模型名
    m_modelName=getLastModelFile();
    //调用SDK启动算法检测
    if(ui->userModeBtn->isChecked())        //使用用户模型算法
        errMsg=m_multiControl->launchBlinkDetection(1, "local_model_blinkcheck2024_09_07_14_55_33_34.json");
    else if(ui->bigDataBtn->isChecked())    //使用大数据模型算法
        errMsg=m_multiControl->launchBlinkDetection(2);
    else
        errMsg="未指定算法类别";
    m_multiControl->resetLocation();
    ui->feedbackLabel->setText(errMsg);
}


void SetUp::on_stopButton_clicked()
{
    //调用SDK停止算法检测
    m_multiControl->stopBlinkDetection();
    ui->feedbackLabel->setText("算法检测已停止");
}

QString SetUp::getLastModelFile()
{
    QString modelName;
    //读取默认的模型文件目录
    QDir modelDir = m_multiControl->getModelDir();
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
    return modelName;
}

void SetUp::on_pushButton_clicked()
{
    attentionShow->show();
}


void SetUp::on_pushButton_2_clicked()
{
    //QPoint point(25, 30);
    //main_vmouse->simulateMouseClick(point);
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
            qDebug() << "单眨眼";
        }
            //ui->blinktimes->setText(u8"双眨眼");
    }
}

