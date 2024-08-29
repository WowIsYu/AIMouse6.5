#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "waveform.h"
#include "blinkcalibration.h"

//#include "attention.h"
//#include "game.h"
#include "setup.h"
#include <QButtonGroup>

#include <login.h>
#include "HMultiControlSDK.h"
//#include "initdatasystemprotocol.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initMainWindow();

private:
    Ui::MainWindow *ui;
    QButtonGroup *btnGroup;     //管理侧边栏按钮
    Waveform *waveFormUi;
    BlinkCalibration *blinkCaliUi;

    //    std::shared_ptr<HBlinkDetection> m_blinkCheckSDK;
    //多模态综合控制SDK
    HMultiControlSDK *m_multiControl;
    //InitDataSystemProtocol *m_proWin;       //协议选择窗口
    //Attention *attentionUi;
    //Game *gameUi;
    SetUp *setUpUi;

    Login *m_login;             //登录界面

private slots:
    void onLoginSuccess();
signals:
    void emitInitSetUp(HMultiControlSDK *MultiObj);
    void emitInitBlinkCail();
};
#endif // MAINWINDOW_H
