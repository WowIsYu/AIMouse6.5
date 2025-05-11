#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QWebEngineView>
namespace Ui {
class SetUpWidget;
}

class SetUpWidget : public QWidget
{
    Q_OBJECT

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_btnSet_clicked();
    void on_btnInfo_clicked();
    void on_btnQuestion_clicked();
    void on_btnAbout_clicked();

signals:
    void emitSetSensitivity(int value);

public:
    explicit SetUpWidget(QWidget *parent = nullptr);
    ~SetUpWidget();

private:
    Ui::SetUpWidget *ui;                               // UI指针
    QWebEngineView *m_webView;                   // 网页视图

};

#endif // SETUPWIDGET_H
