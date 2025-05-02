#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMap>
#include <QVariant>
#include <QString>
#include "HMultiControlSDK.h"
#include <QMouseEvent>


namespace Ui {
class Login;
}


class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(hnnk::HMultiControlSDK *multiObj, QWidget *parent = nullptr);
    ~Login();
    bool eventFilter(QObject *obj, QEvent *event);
    void createToken();
    void detectToken();


    virtual void paintEvent(QPaintEvent *event) override; //重绘,
    //需添加头文件 <QMouseEvent>

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    void setStatusBar(QString information);

    void initUI();
    void initDatabase();

    void showError(const QString &message);

signals:
    void notifyLoginResult();
    void onLoginClose();

private slots:
    void on_radioButton_regist_clicked();

    void on_radioButton_login_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    // void onEventGraphFinish(QMap<QString, QVariant> result);
    // void onEventRegisterFinish(QMap<QString, QVariant> result);
    // void onEventLoginFinish(QMap<QString, QVariant> result);
    void on_checkBox_token_clicked(bool checked);

    void on_btn_close_clicked();

private:
    Ui::Login *ui;
    QString m_imgId;
    //std::shared_ptr<hnnk::HBlinkDetection> m_blink;
    hnnk::HMultiControlSDK *m_multiControl = nullptr;

    bool m_leftMousePressed;
    QPoint m_StartPoint;
};

#endif // LOGIN_H
