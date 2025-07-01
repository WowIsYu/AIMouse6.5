#include "setupwidget.h"
#include "ui_setupwidget.h"
#include <QStackedWidget>
#include <QFrame>
#include <QTimer>


SetUpWidget::SetUpWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetUpWidget)
{
    ui->setupUi(this);

    // 初始化静态库的资源（对应 nagano_res.qrc）
    Q_INIT_RESOURCE(nagano_res); // 注意：名称必须与 .qrc 文件名一致（不带扩展名）


}

SetUpWidget::~SetUpWidget()
{
    delete ui;
}

void SetUpWidget::on_horizontalSlider_valueChanged(int value)
{
    //坐标灵敏度，默认值为14
    ui->sensitivityLabel->setText(QString("灵敏度：%1").arg(value));
    emit emitSetSensitivity(value);
}

void SetUpWidget::on_btnSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void SetUpWidget::on_btnInfo_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void SetUpWidget::on_btnQuestion_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void SetUpWidget::on_btnAbout_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

