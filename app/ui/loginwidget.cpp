#include "loginwidget.h"
// #include "qcryptographichash.h"
#include "qpainter.h"
#include "qstyleoption.h"
#include "qtimer.h"
#include "ui_loginwidget.h"
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
LoginWidget::LoginWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    initUI();
}


LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
//需添加头文件 <QPainter>和 <QStyleOption>


void LoginWidget::mousePressEvent(QMouseEvent *event)
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


void LoginWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_leftMousePressed = false;//释放鼠标，标志位置为假
}

void LoginWidget::setStatusBar(QString information)
{
    ui->label_result->setText(information);
}

void LoginWidget::initUI()
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

void LoginWidget::showError(const QString &message)
{
    ui->label_result->setText("<font color='red'>" + message + "</font>");
    QTimer::singleShot(3000, this, [this]() {
        ui->label_result->clear();
    });
}

void LoginWidget::onLoadRemembered(QString account, QString password)
{
    // 设置解码后的数据到界面上
    ui->lineEdit_account->setText(account);
    ui->lineEdit_pwd->setText(password);
    ui->checkBox_token->setChecked(true);
}

void LoginWidget::onLoginResult(QString m_token)
{
    if(m_token.isEmpty()){
        ui->label_result->setText("登录失败");
    }else{
        ui->label_result->setText("登录成功, 正在加载界面");
        insertUser();
    }
}

void LoginWidget::onRegisterResult(QString msgErr)
{
    if(!msgErr.compare("")){
        ui->label_result->setText("注册成功");
    }else{
        ui->label_result->setText(QString("注册失败: %1").arg(msgErr));
    }
}

void LoginWidget::onGraphCode(QPixmap pixMap, QString imgId)
{
    qDebug() <<"hahahaha" << pixMap << "666" << imgId;
    pixMap = pixMap.scaled(ui->label_graph->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_graph->setPixmap(pixMap);
    this->m_imgId = imgId;
}


void LoginWidget::mouseMoveEvent(QMouseEvent *event)
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

void LoginWidget::on_radioButton_regist_clicked()
{
    if(!ui->lineEdit_pwd_verify->isVisible()){
        ui->frame_pwd_2->setVisible(true);
        ui->lineEdit_pwd_verify->setVisible(true);
        ui->label_pwd_verify->setVisible(true);
    }
}


void LoginWidget::on_radioButton_login_clicked()
{
    ui->lineEdit_pwd_verify->setVisible(false);
    ui->frame_pwd_2->setVisible(false);
    ui->label_pwd_verify->setVisible(false);
}

void LoginWidget::on_pushButton_clicked()
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

    emit onInsertUser(account, password, ui->checkBox_token->isChecked());
    // if(ui->radioButton_login->isChecked()){
    //     emit emitLogin(account, password, captcha, captchaId);
    // }else{
    //     emit emitRegister(account, password, captcha, captchaId);
    // }
}


void LoginWidget::on_pushButton_2_clicked()
{
    exit(0);
}

bool LoginWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(qobject_cast<QLabel*>(obj) == ui->label_graph &&
        event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::LeftButton)
        {
            emit emitGraphCode();
        }

    }
    return QWidget::eventFilter(obj, event);
}

void LoginWidget::on_checkBox_token_clicked(bool checked)
{
    if (checked) {
        qDebug() << "Checkbox is now checked.";

    } else {
        qDebug() << "Checkbox is now unchecked.";
    }
}

// 插入用户
void LoginWidget::insertUser() {
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_pwd->text();

    // 将account和password转换为QByteArray并进行Base64编码
    // QByteArray accountBase64 = account.toUtf8().toBase64();
    // QByteArray passwordBase64 = password.toUtf8().toBase64();

    // QSqlQuery query;
    // query.prepare("INSERT OR REPLACE INTO users (account, password) VALUES (?, ?)");
    // query.addBindValue(QString(accountBase64)); // 插入Base64编码的账户
    // query.addBindValue(QString(passwordBase64)); // 插入Base64编码的密码

    // if (!query.exec()) {
    //     qDebug() << "Error: failed to insert/update user data -" << query.lastError();
    // }
    emit onInsertUser(account, password, ui->checkBox_token->isChecked());
}


void LoginWidget::on_btn_close_clicked()
{
    emit onLoginClose();
}
