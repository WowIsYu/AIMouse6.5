#include "initdatasystemprotocol.h"
#include "ui_initdatasystemprotocol.h"
#include <QMessageBox>

InitDataSystemProtocol::InitDataSystemProtocol(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitDataSystemProtocol)
{
    ui->setupUi(this);
    this->setWindowTitle("选择协议");
    ui->comboBox->addItem("PROT_FIRSTGENERAL");
    ui->comboBox->addItem("PROT_SECONDGENERAL");
    ui->comboBox->addItem("PROT_NEUROSCAN");
    ui->comboBox->setCurrentIndex(0);

    ui->comboBox_2->addItem("NET_COM");
    ui->comboBox_2->addItem("NET_SYSBLUE");
    ui->comboBox_2->addItem("NET_TCP");
    ui->comboBox_2->setCurrentIndex(0);
}

InitDataSystemProtocol::~InitDataSystemProtocol()
{
    delete ui;

}

void  InitDataSystemProtocol::init_Argv()
{
    int arg1 = this->ui->comboBox->currentIndex();
    int arg2 = this->ui->comboBox_2->currentIndex();
    qDebug()<<" arg1 "<<arg1<<" arg12 "<<arg2;
    if(arg1 > 3 || arg2 > 3){
        int ret = QMessageBox::information(this, u8"警告",
                                           u8"未正确选择初始化参数，将影响使用!", QMessageBox::StandardButtons(QMessageBox::Ok));

        if(ret == QMessageBox::Ok){
            this->show();
        }
    }else{
        emit button_Clicked(arg1 + 1, arg2 + 1);
        emit notifyClicked((hnnk::DSNETTYPE)(arg2 + 1), (hnnk::DSPROTOCOLTYPE)(arg1 + 1));
    }

}

void InitDataSystemProtocol::on_buttonBox_accepted()
{
    init_Argv();
}
