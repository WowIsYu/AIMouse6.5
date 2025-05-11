#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QButtonGroup>
#include <QElapsedTimer>
#include <QPoint>
#include <QString>

#include "hmulticontrolwrapper.h"
#include "vmousemainwindow.h"
#include "choosedevice.h"
#include "databasemanager.h"

#include "Nagano.h"
#include "datawidget.h"
#include "waveformwidget.h"
#include "blinkcaliwidget.h"
#include "gamewidget.h"
#include "setupwidget.h"
#include "loginwidget.h"

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

    ChooseDevice *m_pchooseWindow = nullptr;                 // 设备选择窗口
    HMultiControlWrapper *m_multiControl = nullptr;              // 多模态综合控制SDK
    VMouseMainWindow *main_vmouse = nullptr;                 // 虚拟光标图标

    virtual void paintEvent(QPaintEvent *event) override;    // 重绘
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

    void initComponents();
    void initSDK();
    void initUI();
    void initConnections();
    void onLoginSuccess();
    void calculateAttentionStats();
    void loadRemembered();
    void initDatabases();
    void initMuitl();
    void initLogin();
    void initInstance();

public slots:
    void insertUser(QString account, QString pwd, bool isChecked);
    void insertHnnkData(const QString &account, const QDateTime &startTime, const QDateTime &endTime,
                        qreal averageAttention, qreal minAttention, qreal maxAttention, qreal medianAttention);
    void onHnnkData();
    void onLogin(const QString accountName, const QString pwd,
                 const QString chaptcha, const QString imagId);
    void onRegister(const QString accountName, const QString pwd,
                    const QString chaptcha, const QString imagId);
    void onGraphCode();
    void onSearchOver();
    void onLaunchCali(int blinkInterval);
    void onStartBlinkDetection(int choice);
    void onStopBlinkDetection();
    void onShowAttention();

    /**
     * @brief onReciveEegData 接收脑电数据
     * @param eegVec  脑电数据
     */
    void onReciveEegData(QVector<hnnk::EegDataChan> eegVec);

private:
    Ui::MainWindow *ui;
    QButtonGroup *btnGroup;                       // 管理侧边栏按钮
    WaveFormWidget *waveFormWidget;
    BlinkCaliWidget *blinkCaliWidget;
    GameWidget *gameWidget;
    DataWidget *dataWidget;
    SetUpWidget *setUpWidget;
    LoginWidget *loginWidget;                               // 登录界面
    bool m_leftMousePressed;
    QPoint m_StartPoint;
    QString account = "";

    QProcess *process = nullptr;
    User userInfo;

    QPoint globalPos;                             // 鼠标全局位置
    double globalPosx;                            // 鼠标全局x坐标
    double globalPosy;                            // 鼠标全局y坐标

    QString m_modelName;                          // 最近生成的用户模型文件名称
    QDateTime startTime;                          // 注意力检测的开始时间
    QDateTime endTime;                            // 注意力检测的结束时间
    double averageAttention = 0;
    double minAttention = 0;
    double maxAttention = 0;
    double medianAttention = 0;
    QVector<double> attentionValues;              // 存储注意力值

    bool m_isDetecting = false;
    QElapsedTimer m_detectionTimer;

    QString getLastModelFile();                   // 获取最近生成的用户模型文件名

    Nagano *attentionShow;                        // 注意力显示窗口

    QTimer *timer;
    BasicParameter parameter;

private slots:
    void on_statusBar(QString message);
    void drawBar();
    void on_btnAI_clicked();
    void on_btnConnectDevice_clicked();
    void onMsg(int type, QString msg);
    void onGyroData(double x, double y);
    void onBlinkDetectionResult(int val);
    void onBlinkCheckResult(int);

    void on_btnSet_clicked();

signals:
    void emitInitSetUp(hnnk::HMultiControlSDK *MultiObj);
    void emitInitBlinkCail();
    void emitHnnkData(QList<HNNKData>);
    void emitLoginResult(QString);
    void emitRegisterResult(QString);
    void emitGraphCode(QPixmap pixMap, QString m_imgId);
    void emitEegData(QVector<hnnk::EegDataChan> eogVec);
    void emitParameter(hnnk::BasicParameter para);
};

#endif // MAINWINDOW_H
