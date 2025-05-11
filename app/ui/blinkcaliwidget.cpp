#include "blinkcaliwidget.h"
#include "ui_blinkcaliwidget.h"
#include "QTimer"
#include <QMessageBox>

BlinkCaliWidget::BlinkCaliWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlinkCaliWidget)
{
    ui->setupUi(this);

    // 假设ui->caliIcon是一个QLabel
    QPixmap pixmap(":/img/robot1.png");
    // 获取Label的尺寸
    QSize size = ui->caliIcon->size();
    // 使用Qt的保持比例缩放模式来调整图片大小
    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 将调整后的图片设置到Label上
    ui->caliIcon->setPixmap(pixmap);

}

BlinkCaliWidget::~BlinkCaliWidget()
{
    delete ui;
}

//校准触发信号
void BlinkCaliWidget::onCaliTrigger()
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

void BlinkCaliWidget::onCalibrationResult(bool isOk, float score)
{
    if(isOk){
        this->ui->caliResultLabel->setText(QString::number(score,'f', 2));
    }else{
        this->ui->caliResultLabel->setText(QString::number(0));
    }
}

void BlinkCaliWidget::on_beginCaliButton_clicked()
{
    QString errMsg;
    //调用SDK启动校准
    int blinkInterval=ui->blinkIntervalSlider->value();
    if(blinkInterval >=1 &&blinkInterval <= 5)
    {
        emit emitLaunchCali(blinkInterval);
    }
    else {
        QMessageBox::information(this, "calibrator", u8"请正确填写眨眼间隔时间，1~5",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}
