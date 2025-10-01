#ifndef SETINFOWIDGET_H
#define SETINFOWIDGET_H

#include <QWidget>

namespace Ui {
class SetInfoWidget;
}


class SetInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetInfoWidget(QWidget *parent = nullptr);
    ~SetInfoWidget();
    QString getNewDeviceName();
signals:
    void notifyDeviceName(QString name);

public slots:
    /**
     * @brief onReadParametes 读取参数
     * @param curDeviceName  当前设备名称
     */
    void onReadParametes(QString curDeviceName);
    void onModifyDeviceName();

private slots:
    void on_pb_Close_clicked();

private:
    Ui::SetInfoWidget *ui;
    QString m_deviceName;     ///设备名称

};

#endif // SETINFOWIDGET_H
