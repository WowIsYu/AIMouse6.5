#include "blinkcalibration.h"
#include "ui_blinkcalibration.h"
#include "QTimer"
#include <QMessageBox>

BlinkCalibration::BlinkCalibration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlinkCalibration)
{
    ui->setupUi(this);
    //SDK初始化
    m_multiControl = new HMultiControlSDK();
    qDebug() << "BlinkCalibration:m_multiControl 已创建实例";
    //设置License
    m_multiControl->setLicense("c180dec8f4d94af6be5860436ca26003");
    qDebug() << "BlinkCalibration:m_multiControl 已设置License授权码";
    //启动数据采集模块
    m_multiControl->lauchCollector(DATA_FIRSTGENERAL, NET_SYSBLUE);     //选择协议
    qDebug() << "BlinkCalibration:m_multiControl 已初始化数据采集模块";


    //眨眼校准触发信号
    connect(m_multiControl, &HMultiControlSDK::notifyCaliTrigger
            , this, &BlinkCalibration::onCaliTrigger);
    //返回用户当前眨眼结果分数（isOk, score）(校准是否成功， 校准结果分数)
    connect(m_multiControl, &HMultiControlSDK::notifyCalibrationResult
            , this, &BlinkCalibration::onCalibrationResult);

    ui->caliIcon->setPixmap(QPixmap(":/img/cxk2.png"));
}

BlinkCalibration::~BlinkCalibration()
{
    delete ui;
}

//校准触发信号
void BlinkCalibration::onCaliTrigger()
{
    //ui->caliIcon->setStyleSheet("background-color:red");
    ui->caliIcon->setPixmap(QPixmap(":/img/cxk2.png"));
    QTimer::singleShot(200, this, [=](){
        //ui->caliIcon->setStyleSheet("");
        ui->caliIcon->setPixmap(QPixmap(":/img/cxk1.png"));
    });
}

void BlinkCalibration::onCalibrationResult(bool isOk, float score)
{
    if(isOk){
        this->ui->caliResultLabel->setText(QString::number(score,'f', 2));
    }else{
        this->ui->caliResultLabel->setText(QString::number(0));
    }
    ui->feedbackLabel->setText("校准结束");
}

void BlinkCalibration::on_beginCaliButton_clicked()
{
    QString errMsg;
    //调用SDK启动校准
    int blinkInterval=ui->blinkIntervalLineEdit->text().toInt();
    if(blinkInterval >=1 &&blinkInterval <= 5)
    {
        errMsg = m_multiControl->launchCalibration(blinkInterval, false);
        ui->feedbackLabel->setText(errMsg);
    }
    else {
        QMessageBox::information(this, "calibrator", u8"请正确填写眨眼间隔时间，1~5",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void BlinkCalibration::initBlinkCali()
{
    connect(m_pchooseWindow, &ChooseDevice::checkSignal       //确认设备的发送信号
            , this, &BlinkCalibration::onChooseBlueEvent);
}


//void onSearchDevice();
/**
* @brief onChooseBlueEvent 蓝牙选择
 */
void BlinkCalibration::onChooseBlueEvent(hnnk::DataAppOperator type, QString name)
{
    m_multiControl->connectDevice(name);
    qDebug() << "BlinkCalibration:m_multiControl 已连接设备" << name;
}


