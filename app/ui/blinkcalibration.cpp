#include "blinkcalibration.h"
#include "ui_blinkcalibration.h"
#include "QTimer"
#include <QMessageBox>

BlinkCalibration::BlinkCalibration(QWidget *parent,HMultiControlSDK *m_multiControl) :
    QWidget(parent),
    ui(new Ui::BlinkCalibration)
{
    ui->setupUi(this);

    this->m_multiControl = m_multiControl;
    //眨眼校准触发信号
    connect(m_multiControl, &HMultiControlSDK::notifyCaliTrigger
            , this, &BlinkCalibration::onCaliTrigger);
    //返回用户当前眨眼结果分数（isOk, score）(校准是否成功， 校准结果分数)
    connect(m_multiControl, &HMultiControlSDK::notifyCalibrationResult
            , this, &BlinkCalibration::onCalibrationResult);
    connect(m_multiControl, &HMultiControlSDK::notifyConnectState, this
            , &BlinkCalibration::onConnectChange) ;
    // 假设ui->caliIcon是一个QLabel
    QPixmap pixmap(":/img/robot1.png");
    // 获取Label的尺寸
    QSize size = ui->caliIcon->size();
    // 使用Qt的保持比例缩放模式来调整图片大小
    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 将调整后的图片设置到Label上
    ui->caliIcon->setPixmap(pixmap);

    connect(m_multiControl, &HMultiControlSDK::notifyBlinkDetectionResult, this, &BlinkCalibration::onBlinkCheckResult);

}

BlinkCalibration::~BlinkCalibration()
{
    delete ui;
}

//校准触发信号
void BlinkCalibration::onCaliTrigger()
{
    // 假设ui->caliIcon是一个QLabel
    QPixmap pixmap(":/img/robot1.png");
    QPixmap pixmap2(":/img/robot2.png");
    // 获取Label的尺寸
    QSize size = ui->caliIcon->size();
    // 使用Qt的保持比例缩放模式来调整图片大小
    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pixmap2 = pixmap2.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->caliIcon->setPixmap(pixmap2);
    QTimer::singleShot(200, this, [=](){
        ui->caliIcon->setPixmap(pixmap);
    });
}

void BlinkCalibration::onCalibrationResult(bool isOk, float score)
{
    if(isOk){
        this->ui->caliResultLabel->setText(QString::number(score,'f', 2));
    }else{
        this->ui->caliResultLabel->setText(QString::number(0));
    }
    //ui->feedbackLabel->setText("校准结束");
    emit sendToStatusBar("校准结束");
}

void BlinkCalibration::on_beginCaliButton_clicked()
{
    QString errMsg;
    //调用SDK启动校准
    int blinkInterval=ui->blinkIntervalSlider->value();
    if(blinkInterval >=1 &&blinkInterval <= 5)
    {
        errMsg = m_multiControl->launchCalibration(blinkInterval, false);
        //ui->feedbackLabel->setText(errMsg);
        emit sendToStatusBar(errMsg);
    }
    else {
        QMessageBox::information(this, "calibrator", u8"请正确填写眨眼间隔时间，1~5",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void BlinkCalibration::onConnectChange(int state)
{
    if(state == 0)
    {
        //ui->feedbackLabel->setText("设备未连接");
        emit sendToStatusBar("blinkCail:设备未连接");
    }
    else
    {
        //ui->feedbackLabel->setText("设备已连接");
        emit sendToStatusBar("blinkCail:设备已连接");
    }
}

void BlinkCalibration::onBlinkCheckResult(int val)
{
    if(val > 0){
        qDebug()<<"onBlinkCheckResult "<<val;
        //m_colorSwithing.doColorSwitching(ui->label_blink);
        // if(1 == val)
        //     //ui->labelTest->setText(u8"单眨眼");
        // else
        //     //ui->labelTest->setText(u8"双眨眼");
    }
}
