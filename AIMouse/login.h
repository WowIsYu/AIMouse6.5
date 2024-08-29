#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMap>
#include <QVariant>
#include <QString>
#include "HMultiControlSDK.h"
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
signals:
    void notifyLoginResult();

private slots:
    void on_radioButton_regist_clicked();

    void on_radioButton_login_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    // void onEventGraphFinish(QMap<QString, QVariant> result);
    // void onEventRegisterFinish(QMap<QString, QVariant> result);
    // void onEventLoginFinish(QMap<QString, QVariant> result);
private:
    Ui::Login *ui;
    QString m_imgId;
    //std::shared_ptr<hnnk::HBlinkDetection> m_blink;
    hnnk::HMultiControlSDK *m_multiControl;
};

#endif // LOGIN_H
