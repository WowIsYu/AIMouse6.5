#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "attention.h"
#include "QString"
#include "waveform.h"
#include "blinkcalibration.h"
#include "game.h"
#include "setup.h"
#include "login.h"
#include "QPoint"

#include <QButtonGroup>
#include "HMultiControlSDK.h"
#include "hdatasystem_interface.h"
#include "dataset.h"
#include "choosedevice.h"
//#include "initdatasystemprotocol.h"
#include <QMouseEvent>
#include "qsqldatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initMainWindow();

    ChooseDevice *m_pchooseWindow = nullptr;          ///设备选择窗口
    ///数据采集SDK
    // hnnk::HDataSystem_interface *m_dataSystemSDK = nullptr;
    //多模态综合控制SDK
    HMultiControlSDK *m_multiControl = nullptr;
    //虚拟光标图标
    VMouseMainWindow *main_vmouse = nullptr;

    virtual void paintEvent(QPaintEvent *event) override; //重绘,
    //需添加头文件 <QMouseEvent>

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

    void initComponents();
    void initSDK();
    void initUI();
    void initConnections();



private:
    Ui::MainWindow *ui;
    QButtonGroup *btnGroup;     //管理侧边栏按钮
    Waveform *waveFormUi;
    BlinkCalibration *blinkCaliUi;
    //InitDataSystemProtocol *m_proWin;       //协议选择窗口
    GreedySnakeGame *greedySnakeGameUi;
    Attention *attention;
    SetUp *setUpUi;
    Login *m_login;             //登录界面
    bool m_leftMousePressed;
    QPoint m_StartPoint;

    QSqlDatabase db;

     QProcess *process = nullptr;


private slots:
    void onLoginSuccess();
    void on_statusBar(QString message);
    void drawBar();
    void on_btnAI_clicked();

signals:
    void emitInitSetUp(hnnk::HMultiControlSDK *MultiObj);
    void emitInitBlinkCail();
    void emitChangeDevice_waveform(hnnk::DataAppOperator, QString);
    void emitChangeDevice_blinkcail(hnnk::DataAppOperator, QString);
};
#endif // MAINWINDOW_H
