#include "setup.h"
#include "ui_setup.h"
#include <QStackedWidget>
#include <QFrame>
#include <QTimer>


SetUp::SetUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetUp)
{
    ui->setupUi(this);

    // 初始化静态库的资源（对应 nagano_res.qrc）
    Q_INIT_RESOURCE(nagano_res); // 注意：名称必须与 .qrc 文件名一致（不带扩展名）


    //发送注意力值给attentionShow

    // 获取第二页（索引为 1）的部件
    // QWidget *secondPage = ui->stackedWidget->widget(1);

    // if (secondPage) {
    //     //frame_information 是 QFrame 的指针，且在第二页中
    //     QFrame *frameInformation = secondPage->findChild<QFrame *>("frame_information");
    //     if (frameInformation) {
    //         // frameInformation->setStyleSheet("background-color: red;");
    //         m_webView = new QWebEngineView(this);
    //         QStackedLayout* layout = new QStackedLayout(ui->frame);
    //         frameInformation->setLayout(layout);
    //         layout->addWidget(m_webView);
    //         // m_webView->load(QUrl("https://www.baidu.com"));

    //         QString filePath = "./person_infromation.html"; // 替换为你的相对路径
    //         m_webView->load(QUrl::fromLocalFile(QDir::current().absoluteFilePath(filePath)));
    //         m_webView->setZoomFactor(0.5); //缩放比例0.5
    //     }
    // }

}

SetUp::~SetUp()
{
    delete ui;
}

void SetUp::on_horizontalSlider_valueChanged(int value)
{
    //坐标灵敏度，默认值为14
    ui->sensitivityLabel->setText(QString("灵敏度：%1").arg(value));
    emit emitSetSensitivity(value);
}

void SetUp::onAttenDetectionResult(double val)
{
    double val2=val*100;
    ui->resultLabel->setText(QString::number(val2,'f', 0));
}


void SetUp::on_beginButton_clicked()
{
    int choice = 0;
    // 调用SDK启动算法检测
    if (ui->userModeBtn->isChecked()) // 使用用户模型算法
        choice = 1;
    else if (ui->bigDataBtn->isChecked()) // 使用大数据模型算法
        choice = 2;

    emit emitStartBlinkDetection(choice);

}

void SetUp::on_stopButton_clicked()
{
    emit emitStopBlinkDetection();
}

void SetUp::on_pushButton_clicked()
{
    emit emitShowAttention();
}
void SetUp::on_btnSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void SetUp::on_btnInfo_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void SetUp::on_btnQuestion_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void SetUp::on_btnAbout_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

