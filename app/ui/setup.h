#ifndef SETUP_H
#define SETUP_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QWebEngineView>
namespace Ui {
class SetUp;
}

class SetUp : public QWidget
{
    Q_OBJECT

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_beginButton_clicked(); // 启动检测
    void on_stopButton_clicked();   // 停止检测
    void on_pushButton_clicked();
    void on_btnSet_clicked();
    void on_btnInfo_clicked();
    void on_btnQuestion_clicked();
    void on_btnAbout_clicked();

public slots:
    void onAttenDetectionResult(double val);

signals:
    void emitSetSensitivity(int value);
    void emitStopBlinkDetection();
    void emitStartBlinkDetection(int choice);
    void emitShowAttention();

public:
    explicit SetUp(QWidget *parent = nullptr);
    ~SetUp();

    void calculateAttentionStats();

private:
    Ui::SetUp *ui;                               // UI指针
    QWebEngineView *m_webView;                   // 网页视图

};

#endif // SETUP_H
