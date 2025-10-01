#include "setinfowidget.h"
#include "ui_setinfowidget.h"

#include <QDebug>

#pragma execution_character_set("utf-8")


SetInfoWidget::SetInfoWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::SetInfoWidget)
{
    ui->setupUi(this);
    ui->le_newName->installEventFilter(this);
    this->setWindowTitle("修改蓝牙名称");

    m_deviceName = "";
    connect(ui->pb_OK, SIGNAL(clicked()), this, SLOT(onModifyDeviceName()));

}

SetInfoWidget::~SetInfoWidget()
{
    delete ui;
}

void SetInfoWidget::onReadParametes(QString curDeviceName)
{
    qDebug()<<"SetInfoWidget::readParametes devicename "<<curDeviceName ;
    if(curDeviceName.isEmpty()){
        if(ui->le_oleName->text().isEmpty()){
            ui->le_oleName->setText("名称为空");
        }
    }else{
        ui->le_oleName->setText(curDeviceName);
    }

}


void SetInfoWidget::onModifyDeviceName()
{

    QString name = ui->le_newName->text();
    if(name.length() > 15){
        //名称太长.重新命名
        return;
    }
    m_deviceName = ("TD05_") ;
    //QString allName("BLE");
    m_deviceName.append(name);
    emit notifyDeviceName(m_deviceName);
    qDebug()<<"SetInfoWidget::onModifyDeviceName "<<m_deviceName;

}



void SetInfoWidget::on_pb_Close_clicked()
{
    this->hide();
}

QString SetInfoWidget::getNewDeviceName()
{
    return m_deviceName;
}
