#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>
using namespace hnnk;
Login::Login(hnnk::HMultiControlSDK *multiObj, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Login),m_multiControl(multiObj)
{
    ui->setupUi(this);
    ui->label_graph->installEventFilter(this);

    ui->radioButton_login->setChecked(true);

    //初始化,默认为登录
    ui->radioButton_login->setEnabled(true);
    ui->frame_pwd_2->hide();
    ui->lineEdit_pwd_verify->setVisible(false);
    ui->label_pwd_verify->setVisible(false);
}

Login::~Login()
{
    delete ui;
}

void Login::on_radioButton_regist_clicked()
{
    if(!ui->lineEdit_pwd_verify->isVisible()){
        ui->frame_pwd_2->show();
        ui->lineEdit_pwd_verify->setVisible(true);
        ui->label_pwd_verify->setVisible(true);
    }
}


void Login::on_radioButton_login_clicked()
{
    ui->lineEdit_pwd_verify->setVisible(false);
    ui->label_pwd_verify->setVisible(false);
}

void Login::on_pushButton_clicked()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_pwd->text();
    QString captcha = ui->lineEdit_code->text();
    QString captchaId =m_imgId;
    if(account == ""){
        qDebug()<<"用户名不能为空";
        ui->label_result->setText("用户名不能为空");
        return;
    }
    if(password == ""){
        qDebug()<<"密码不能为空";
        ui->label_result->setText("密码不能为空");
        return;
    }
    if(captcha == ""){
        qDebug()<<"图形码不能为空";
        ui->label_result->setText("图形码不能为空");
        return;
    }
    if(ui->radioButton_login->isChecked()){
        //登录
        //main_vmouse->setStyleSheet("background-color:red");
        qDebug() << "登录页面：登录";
        qDebug()<<" m_imgId "<<m_imgId<<" account "<<ui->lineEdit_account->text()
                 <<" pwd "<<ui->lineEdit_pwd->text()<<" code "<<ui->lineEdit_code->text();

        //调用SDK进行用户登录
        QString m_token;
        m_token = m_multiControl->login(account, password, captcha, captchaId);
        if(m_token.isEmpty()){
            ui->label_result->setText("登录失败");

        }else{
            ui->label_result->setText("登录成功");
            emit notifyLoginResult();
        }

    }else{
        //注册
        //main_vmouse->setStyleSheet("background-color:yellow");
        qDebug() << "登录页面：注册";
        //调用SDK进行用户注册
        QString msgErr;
        msgErr = m_multiControl->registAccounter(account, password, captcha, captchaId);
        if(!msgErr.compare("")){
            ui->label_result->setText("注册成功");
        }else{
            ui->label_result->setText(QString("注册失败: %1").arg(msgErr));
        }
    }
}


void Login::on_pushButton_2_clicked()
{
    exit(0);
}

bool Login::eventFilter(QObject *obj, QEvent *event)
{
    bool isOk = false;
    if(qobject_cast<QLabel*>(obj) == ui->label_graph &&
        event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::LeftButton)
        {
            //调用SDK获取图形验证码
            QPixmap pixMap;
            m_multiControl->getGraphValidateCode(pixMap, m_imgId);
            pixMap = pixMap.scaled(ui->label_graph->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_graph->setPixmap(pixMap);
            isOk = true;
        }

    }
    return isOk;
}
