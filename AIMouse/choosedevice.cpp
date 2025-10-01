#include "choosedevice.h"
#include "ui_choosedevice.h"

#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QDebug>
#include <QCloseEvent>
#include <QHeaderView>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


ChooseDevice::ChooseDevice(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChooseDevice)
{
    ui->setupUi(this);
    this->setWindowTitle("选择串口/蓝牙");
    m_latestName = "";      //上一次选中的串口名
    m_flagWho = 1;

    //connect(ui->checkBtn, &QPushButton::clicked, this, &ChooseDevice::sendCheckSignal);
    //connect(ui->flushButton, &QPushButton::clicked, this, &ChooseDevice::on_flushButton_clicked);
    //点击单选选项
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(windowFlags() &~ Qt::WindowMinimizeButtonHint
                         &~ Qt::WindowMaximizeButtonHint &~ Qt::WindowTitleHint
                         );
    //ui->scrollArea->widget()->setLayout(&m_Vylout);
    m_isBluetoothEnable = true;

    m_deviceList = new QTableWidget(this);
    m_deviceList->setGeometry(ui->frame_funView->frameRect());
    m_deviceList->hide();
    //m_deviceList->show();
    m_conText = new QLabel();

    m_isCon = false;
}

ChooseDevice::~ChooseDevice()
{
    clear();
    delete ui;
}

void ChooseDevice::clear()
{
    if(!m_Vylout.isEmpty()){
        while (!m_Vylout.isEmpty()){
            delete m_Vylout.takeAt(0);
        }
    }
}

QString ChooseDevice::getLastDeviceName()
{
    return m_latestName;
}

//获取查询到的设备名称信息
void ChooseDevice::updateDeviceNameList(QString name)
{
    if(!m_names.contains(name)){
        m_names.push_back(name);
    }
    // QRadioButton *rb = new QRadioButton(QString("%1").arg(deviceName));
    // rb->setMinimumSize(QSize(50, 60));
    // connect(rb, &QRadioButton::clicked
    //         , this, &ChooseDevice::radioClick);
    // m_Vylout.addWidget(rb);
}

// void ChooseDevice::radioClick()
// {
//     int i = m_Vylout.count();
//     QLayoutItem* item = nullptr;

//     while ((item = m_Vylout.itemAt(--i)) != nullptr ){
//         QRadioButton* rad = (QRadioButton*)item->widget();
//         if(rad->isChecked()){
//             m_latestName = rad->text();
//             ui->checkBtn->setEnabled(true);
//             qDebug() << "ChooseSerialPort::radioClick BBBB  "<<m_latestName;
//         }
//     }
// }


void ChooseDevice::showTopwindow()
{
    qDebug() << "ChooseSerialPort::showTopwindow";
    qDebug()<<"设备选择顶层显示" << this->isHidden()<< this->isVisible();
    this->show();
    update();
}

void ChooseDevice::closeEvent(QCloseEvent *event)
{
    //忽略这个事件，当前窗口不会关闭
    qDebug() << "ChooseSerialPort::closeEvent(QCloseEvent *event)";
    event->ignore();
    this->hide();
}

void ChooseDevice::searchOver()
{
    qDebug() << "SearchOver!";
    //ui->flushButton->setText("刷新");
    if(!m_names.isEmpty()){
        for(auto it : qAsConst(m_names)){
            qDebug()<<" name "<<it;
        }
        setTableWidgetViwe(m_names);
    }
    m_names.clear();
}

void ChooseDevice::connectUpdate(hnnk::CONNECTUPDATE conVal)
{
    m_deviceList->hide();
    m_conText->show();
    ui->verticalLayout_2->removeWidget(m_deviceList);
    ui->verticalLayout_2->addWidget(m_conText);
    QString text;
    if(conVal){
        text = u8"连接成功";
        m_isCon = true;
    }else{
        text = u8"连接失败";
        m_isCon = false;
    }
    m_conText->setText(text);
}


void ChooseDevice::setBluetoothEnable(bool flag)
{
    m_isBluetoothEnable = flag;
}

// void ChooseDevice::setFlashText(QString name)
// {
//     ui->flushButton->setText(name);
// }


void ChooseDevice::on_m_pbSearch_clicked()
{
    m_names.clear();
    m_deviceList->clearContents();

    ui->verticalLayout_2->removeWidget(m_conText);
    m_conText->hide();

    setTableWidgetViwe(m_names);
    emit refreshList();
}


void ChooseDevice::on_m_pbConnect_clicked()
{
    int row = m_deviceList->rowCount();
    int col = m_deviceList->columnCount();
    qDebug() << m_deviceList->rowCount() << m_deviceList->columnCount();
    QString name = "";
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            QTableWidgetItem *it = m_deviceList->item(r, c);
            if(it->isSelected()){
                name = m_deviceList->item(r, 1)->text();
                qDebug() << name;
            }
        }

    }
    for(int r = 0; r < row; r++){
        m_deviceList->removeRow(r);
    }

    m_deviceList->clear();
    //通知读取通道数和采样率
    // connect(m_blinkCheckSDK.get(), &HBlinkDetection::notifyChsAndSampRate
    //         , this, &BlinkDetection::onDeviceChannels);
    // m_blinkCheckSDK->connectDevice(name);
    //发送连接设备名，使两个实例连接
    emit checkSignal(hnnk::DataAppOperator::DAO_CONNET, name);
    qDebug()<<" ChooseDevice::sendCheckSignal "<<name;
    this->hide();

}

void ChooseDevice::setTableWidgetViwe(QStringList nameList)
{
    ui->verticalLayout_2->removeWidget(m_conText);
    m_deviceList->setColumnCount(2);
    QStringList strList;
    strList<<u8"序号"<<u8"设备名";
    m_deviceList->setHorizontalHeaderLabels(strList);
    m_deviceList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_deviceList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if(!nameList.isEmpty()){
        m_deviceList->clearContents();
        int row = m_deviceList->rowCount();
        while(0 < row){
            m_deviceList->removeRow(0);
            row = m_deviceList->rowCount();
        }
        int index = 0;
        row = m_deviceList->rowCount();
        for(const auto &it : nameList){

            m_deviceList->insertRow(row);
            QTableWidgetItem *itemIndex = new QTableWidgetItem(QString::number(index));
            m_deviceList->setItem(row, 0, itemIndex);
            QTableWidgetItem *itemName = new QTableWidgetItem(it);
            m_deviceList->setItem(row, 1, itemName);
            //QTableWidgetItem *itemStates = new QTableWidgetItem();
            //m_deviceList->setItem(row, 2, itemStates);
            index++;
        }
    }
    m_deviceList->show();
    ui->verticalLayout_2->addWidget(m_deviceList);
}


void ChooseDevice::tabChanged(int tabIndex)
{
    if(!tabIndex){
        m_deviceList->show();
        ui->verticalLayout_2->addWidget(m_deviceList);
    }else{
        m_deviceList->hide();
    }
}

void ChooseDevice::deviceChannels(int chs, int rate)
{
    m_conText->clear();
    m_conText->setText(QString("chs: %1, rate: %2").arg(chs).arg(rate));
}
