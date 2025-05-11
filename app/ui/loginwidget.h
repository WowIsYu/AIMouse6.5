#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QMouseEvent>


namespace Ui {
class LoginWidget;
}


class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    bool eventFilter(QObject *obj, QEvent *event);
    void insertUser();

    virtual void paintEvent(QPaintEvent *event) override; //重绘,
    //需添加头文件 <QMouseEvent>

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    void setStatusBar(QString information);

    void initUI();

    void showError(const QString &message);
signals:
    void notifyLoginResult();
    void onLoginClose();
    void onInsertUser(QString acct, QString pwd, bool isChecked);
    void emitLogin(const QString accountName, const QString pwd,
                   const QString graphCode, const QString imagId);
    void emitRegister(const QString accountName, const QString pwd,
                      const QString graphCode, const QString imagId);
    void emitGraphCode();
public slots:
    void onLoadRemembered(QString account, QString password);
    void onLoginResult(QString m_token);
    void onRegisterResult(QString m_err);
    void onGraphCode(QPixmap pixMap, QString m_imgId);


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
    Ui::LoginWidget *ui;
    QString m_imgId;
    bool m_leftMousePressed;
    QPoint m_StartPoint;
};

#endif // LOGINWIDGET_H
