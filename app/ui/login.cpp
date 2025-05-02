#include "login.h"
#include "qcryptographichash.h"
#include "qpainter.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "qstyleoption.h"
#include "qtimer.h"
#include "ui_login.h"
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
using namespace hnnk;
Login::Login(hnnk::HMultiControlSDK *multiObj, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Login), m_multiControl(multiObj)
{
    ui->setupUi(this);
    initUI();

    initDatabase();

    detectToken(); // 调用检测令牌
}


Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
//需添加头文件 <QPainter>和 <QStyleOption>


void Login::mousePressEvent(QMouseEvent *event)
{
    // 只能是鼠标左键移动和改变大小
    if (event->button() == Qt::LeftButton) // 处于左键状态
    {
        // 获取鼠标在窗口中的位置
        QPoint posInWindow = event->pos();

        // 检查鼠标是否在窗口内部
        if (posInWindow.x() >= 0 && posInWindow.x() < this->width() &&
            posInWindow.y() >= 0 && posInWindow.y() < this->height())
        {
            m_leftMousePressed = true;  // 标志位置为真
            // 按下时鼠标左键时，窗口在屏幕中的坐标
            m_StartPoint = event->globalPos();
        }
    }
}


void Login::mouseReleaseEvent(QMouseEvent *event)
{
    m_leftMousePressed = false;//释放鼠标，标志位置为假
}

void Login::setStatusBar(QString information)
{
    ui->label_result->setText(information);
}

void Login::initUI()
{
    ui->label_graph->installEventFilter(this);

    ui->radioButton_login->setChecked(true);

    // 初始化,默认为登录
    ui->radioButton_login->setEnabled(true);
    ui->frame_pwd_2->hide();
    ui->lineEdit_pwd_verify->setVisible(false);
    ui->label_pwd_verify->setVisible(false);

    setAttribute(Qt::WA_TranslucentBackground); // 设置窗口透明化
    this->setWindowFlags(Qt::FramelessWindowHint); // 隐藏最大最小化等按键
}

void Login::initDatabase()
{
    QSqlQuery query;
    // Create users table
    QString createUsersTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            account TEXT,
            password TEXT
        )
    )";

    if (!query.exec(createUsersTable)) {
        qDebug() << "Error: failed to create users table -" << query.lastError();
    }
}

void Login::showError(const QString &message)
{
    ui->label_result->setText("<font color='red'>" + message + "</font>");
    QTimer::singleShot(3000, this, [this]() {
        ui->label_result->clear();
    });
}


void Login::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口,由于取消了标题栏，因此需要自己实现拖动窗口功能
    if (m_leftMousePressed)
    {
        QPoint curPoint = event->globalPos();   //按住移动时的位置
        QPoint movePoint = curPoint - m_StartPoint; //与初始坐标做差，得位移
        //普通窗口
        QPoint mainWinPos = this->pos();
        //设置窗口的全局坐标
        this->move(mainWinPos.x() + movePoint.x(), mainWinPos.y() + movePoint.y());
        m_StartPoint = curPoint;
    }
}

void Login::on_radioButton_regist_clicked()
{
    if(!ui->lineEdit_pwd_verify->isVisible()){
        ui->frame_pwd_2->setVisible(true);
        ui->lineEdit_pwd_verify->setVisible(true);
        ui->label_pwd_verify->setVisible(true);
    }
}


void Login::on_radioButton_login_clicked()
{
    ui->lineEdit_pwd_verify->setVisible(false);
    ui->frame_pwd_2->setVisible(false);
    ui->label_pwd_verify->setVisible(false);
}

void Login::on_pushButton_clicked()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_pwd->text();
    QString passwordVerify = ui->lineEdit_pwd_verify->text();
    QString captcha = ui->lineEdit_code->text();
    QString captchaId =m_imgId;
    if(account == ""){
        showError("用户名不能为空");
        return;
    }
    if(password == ""){
        showError("密码不能为空");
        return;
    }
    if(captcha == ""){
        showError("图形码不能为空");
        return;
    }

    // 注册时需要验证两次密码是否一致
    if(ui->radioButton_regist->isChecked() && password != passwordVerify) {
        showError("两次输入的密码不一致");
        return;
    }

    if(ui->radioButton_login->isChecked()){
        //登录
        qDebug()<<" m_imgId "<<m_imgId<<" account "<<ui->lineEdit_account->text()
                 <<" pwd "<<ui->lineEdit_pwd->text()<<" code "<<ui->lineEdit_code->text();

        //调用SDK进行用户登录
        QString m_token;
        m_token = m_multiControl->login(account, password, captcha, captchaId);
        if(m_token.isEmpty()){
            ui->label_result->setText("登录失败");

        }else{
            ui->label_result->setText("登录成功, 正在加载界面");
            emit notifyLoginResult();
            if (ui->checkBox_token->isChecked()) {
                createToken();
                qDebug() << "create token";
            }
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

void Login::on_checkBox_token_clicked(bool checked)
{
    if (checked) {
        qDebug() << "Checkbox is now checked.";

    } else {
        qDebug() << "Checkbox is now unchecked.";
    }
}

void Login::createToken() {
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_pwd->text();

    // 将account和password转换为QByteArray并进行Base64编码
    QByteArray accountBase64 = account.toUtf8().toBase64();
    QByteArray passwordBase64 = password.toUtf8().toBase64();

    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO users (account, password) VALUES (?, ?)");
    query.addBindValue(QString(accountBase64)); // 插入Base64编码的账户
    query.addBindValue(QString(passwordBase64)); // 插入Base64编码的密码

    if (!query.exec()) {
        qDebug() << "Error: failed to insert/update user data -" << query.lastError();
    }
}




void Login::detectToken() {

    QSqlQuery query;
    query.prepare("SELECT account, password FROM users LIMIT 1"); // 查询第一个用户
    if (query.exec()) {
        if (query.next()) {
            ui->checkBox_token->setChecked(true);
            ui->lineEdit_account->clear();
            ui->lineEdit_pwd->clear();

            QString account = query.value(0).toString();
            QString password = query.value(1).toString();

            // 将Base64编码的字符串解码回原始数据
            QByteArray accountBase64 = QByteArray::fromBase64(account.toUtf8());
            QByteArray passwordBase64 = QByteArray::fromBase64(password.toUtf8());

            // 设置解码后的数据到界面上
            ui->lineEdit_account->setText(QString::fromUtf8(accountBase64));
            ui->lineEdit_pwd->setText(QString::fromUtf8(passwordBase64));
        } else {
            qDebug() << "No user data found."; // 表中没有数据
        }
    } else {
        qDebug() << "Error: failed to retrieve user data -" << query.lastError();
    }

}




void Login::on_btn_close_clicked()
{
    emit onLoginClose();
}

