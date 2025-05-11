#include "waveformwidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QMetaType>
#include <QByteArray>
#include <QToolButton>
//#include <iomanip>
//#include <iostream>
//#include <cstdlib>
//#include <algorithm>
#include <QWidget>
//#include "initdatasystemprotocol.h"
//#include <chrono>
#include "dataset.h"
#include "ui_waveformwidget.h"

using namespace hnnk;
//#pragma execution_character_set("utf-8")        //设置编码格式，防止中文乱码


WaveFormWidget::WaveFormWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WaveFormWidget)
{
    ui->setupUi(this);
    //设置Ui界面
    setUi();

    //构建协议选择窗口
    // m_iniEnv = new InitDataSystemProtocol;
    // m_iniEnv->setModal(true);
    // m_iniEnv->show();
    // connect(m_iniEnv, &InitDataSystemProtocol::button_Clicked, this, &WaveFormWidget::lauchCollector);

    ///构建打标窗口
    m_pMarkingTester = new MarkingTester(this);
    connect(m_pMarkingTester, &MarkingTester::emitManualMarking, this, &WaveFormWidget::onDealManualMarking);//接收手动打标信号

    ///参数配置
    m_localConf.m_deviceName = "";
    m_localConf.m_block = 0;
    m_localConf.m_channels = 0;
    m_localConf.m_refComputer = 0;
    m_localConf.m_samp = 0;
    //EdfSaveTest edf;
    //edf.saveBdf();
    m_timeCur = 0;
    m_lastCh = 0;
}

WaveFormWidget::~WaveFormWidget()
{
    delete m_pMarkingTester;
    m_pMarkingTester = nullptr;
    delete ui;
}

/**
 * 设置UI界面
 * @brief WaveFormWidget::setUi
 */
void WaveFormWidget::setUi() {
    //this->setFixedSize(1500, 800);

    this->showMaximized();


    //setFocusPolicy(Qt::StrongFocus);
    ui->btn_stop_acquisition->setEnabled(false);
    //ui->searchAgainBtn->setVisible(false);

    //显示波形时的滑动条设置
    // connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));  //旷注释
    // connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged2(QCPRange)));
    ui->horizontalScrollBar->setEnabled(false);
    ui->horizontalScrollBar->setVisible(false);

    //显示丢包率的控件
    m_chAndRateInfo = new QLabel(this);
    m_dataLost1 = new QLabel(this);
    m_dataLost2 = new QLabel(this);
    m_dataLost3 = new QLabel(this);
    m_dataTime = new QLabel(this);
    m_pdataGyro = new QLabel(this);
    m_deviceVoltage = new QLabel(this);

    m_hLayout.addWidget(m_chAndRateInfo);
    m_hLayout.addWidget(m_deviceVoltage);
    m_hLayout.addWidget(m_dataLost1);
    m_hLayout.addWidget(m_dataLost2);
    m_hLayout.addWidget(m_dataLost3);
    m_hLayout.addWidget(m_dataTime);
    m_hLayout.addWidget(m_pdataGyro);

#if 1
    //cyf-设置QLabel 在布局中的占比大小
    m_chAndRateInfo->setStyleSheet("QLabel{border:2px solid rgb(128,138,135);}");  //设置分界线的样式
    m_deviceVoltage->setStyleSheet("QLabel{border:2px solid rgb(128,138,135);}");
    m_dataLost1->setStyleSheet("QLabel{border:2px solid rgb(128,138,135);}");
    m_dataLost2->setStyleSheet("QLabel{border:2px solid rgb(128,138,135);}");
    m_dataLost3->setStyleSheet("QLabel{border:2px solid rgb(128,138,135);}");
    m_dataTime->setStyleSheet("QLabel{border:2px solid rgb(128,138,135);}");
    m_pdataGyro->setStyleSheet("QLabel{border:2px solid rgb(128,138,135);}");

    m_hLayout.setStretchFactor(m_chAndRateInfo, 2);
    m_hLayout.setStretchFactor(m_deviceVoltage, 3);
    m_hLayout.setStretchFactor(m_dataLost1, 4);
    m_hLayout.setStretchFactor(m_dataLost2, 4);
    m_hLayout.setStretchFactor(m_dataLost3, 4);
    m_hLayout.setStretchFactor(m_dataTime, 3);
    m_hLayout.setStretchFactor(m_pdataGyro, 7);
    m_hLayout.setSpacing(1);

    //4-08
    ui->verticalLayout->addLayout(&m_hLayout,1);
    ui->verticalLayout->setStretchFactor(&m_hLayout,1);
    ui->verticalLayout->setStretchFactor(ui->horizontalScrollBar,1);
    ui->customPlot->axisRect()->setBackground(QBrush(Qt::white));
    ui->customPlot->xAxis->setRange(0, 8, Qt::AlignLeft);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(180, 180, 180), 1, Qt::PenStyle::DashLine));
    ui->customPlot->yAxis->setRange(-10, 600);
    ui->customPlot->yAxis->setLabel("uV");
    ui->customPlot->yAxis->setLabelColor(Qt::blue);
    ui->customPlot->yAxis->setLabelFont(QFont(("Arial"),12));
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica", 9));
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
    ui->customPlot->addGraph();
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(179, 212, 101));
    ui->customPlot->graph(0)->setName("EEG 1");
    ui->customPlot->graph(0)->setPen(pen);
    ui->customPlot->axisRect()->setRangeZoom( Qt::Vertical);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//
#endif
}


/**
 * 选择数据协议和通信协议
 * @brief WaveFormWidget::lauchCollector
 * @param index1    数据协议类型
 * @param index2    通信协议类型
 */
void WaveFormWidget::lauchCollector(int index1,int index2)
{
    // int dataProVal = index1;
    // int netProVal = index2;
    // m_dataSystemSDK->initEegDataCollectorEnv((DSPROTOCOLTYPE)dataProVal, (DSNETTYPE)netProVal);
    // qDebug()<<"选择的数据协议类型为:"<<dataProVal;
    // qDebug()<<"选择的通信协议类型为:"<<netProVal;
    //QVariant vv("192.168.1.17:4455");
    //m_dataSystem->eventDispatcher(DAO_CONNET, vv);
    //QVariant vv;
    //m_dataSystem->eventDispatcher(DataAppOperator::DAO_SEARCHDEVICE, vv);
}


/**
 * @brief DataSystemCaseWindow::realtimeDataSlotChan 实时数据显示通道
 * @param tmp 当前数据
 * @param freq 采样频率
 * @param chNum 通道数
 * @param pntNum 采样点数
 */
void WaveFormWidget::realtimeDataSlotChan(std::vector<double>& tmp, int freq, int chNum, int pntNum)
{
    if(!freq || !chNum){
        return;
    }

    while(ui->customPlot->graphCount() < chNum){
        ui->customPlot->addGraph();
        int i = ui->customPlot->graphCount() - 1;
        ui->customPlot->graph(i)->setName("EEG " + QString::number(i + 1));
        QPen pen;
        pen.setColor(QColor(m_plotColor[i][0], m_plotColor[i][1], m_plotColor[i][2]));
        ui->customPlot->graph(i)->setPen(pen);
        ui->customPlot->graph(i)->setVisible(true);
        ui->customPlot->graph(i)->setAdaptiveSampling(true);

    }

    for(int i = 0; i < tmp.size(); i += chNum){
        for(int j = 0; j < chNum; j++){
            if(i + j < tmp.size()){
                ui->customPlot->graph(j)->data()->remove(m_lastPointKey + 0.00001, m_timeCur);
                ui->customPlot->graph(j)->addData(m_timeCur, tmp[i + j]);
            }
        }
        m_lastPointKey = m_timeCur;
        m_timeCur += 1.0 / freq;
    }

    if(m_timeCur > m_rangeRight){
        // std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> tpMicro
        //     = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
        // (微秒精度的)时间点 => (微秒精度的)时间戳
        //time_t totalMicroSeconds = tpMicro.time_since_epoch().count();
        //int micro = (totalMicroSeconds / 1000000);

        m_timeCur = 0;
        m_lastPointKey = 0;
        //if(vals.size() > 500)
        //vals.erase(vals.begin(), vals.begin() + 250);
        ui->customPlot->clearItems();     //这个才可以清除标
    }
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);

}

void WaveFormWidget::realtimeDataSlotChanEdf(std::vector<double>& tmp, int freq, int ch, int chNum, int pntNum)
{
    if(!freq || !chNum){
        return;
    }

    if(m_lastCh != ch){
        //std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> tpMicro
        //    = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
        // (微秒精度的)时间点 => (微秒精度的)时间戳
        //time_t totalMicroSeconds = tpMicro.time_since_epoch().count();
        //int micro = (totalMicroSeconds / 1000000);

        m_timeCur = 0;
        m_lastPointKey = 0;
        m_lastCh = ch;

        //ui->customPlot->clearItems();     //这个才可以清除标
    }
    while(ui->customPlot->graphCount() < chNum){
        ui->customPlot->addGraph();
        int i = ui->customPlot->graphCount() - 1;
        ui->customPlot->graph(i)->setName("EEG " + QString::number(i + 1));
        QPen pen;
        pen.setColor(QColor(m_plotColor[i][0], m_plotColor[i][1], m_plotColor[i][2]));
        ui->customPlot->graph(i)->setPen(pen);
        ui->customPlot->graph(i)->setVisible(true);
        ui->customPlot->graph(i)->setAdaptiveSampling(true);

    }

    for(int i = 0; i < tmp.size(); i++){
        ui->customPlot->graph(ch)->data()->remove(m_lastPointKey + 0.00001, m_timeCur);
        ui->customPlot->graph(ch)->addData(m_timeCur, tmp[i]);
        m_lastPointKey = m_timeCur;
        m_timeCur += 1.0 / freq;
    }


    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);

}

void WaveFormWidget::setupPlotEdfChan(QCustomPlot *customPlot)
{
    QString path = QFileDialog::getOpenFileName(
        this,
        "打开",
        "../",
        "*.bdf");
    if(path.isEmpty()==true){
        qDebug()<<"path.isEmpty() == true  ";
        //QFileDialog::destroy();
        return;
    }
    clearScreen();
    QVariant vv(path);
    m_timeCur = 0;
    m_lastPointKey = 0;

    emit emitEventDispatcher(DataAppOperator::DAO_READEDF, vv);
}

void WaveFormWidget::onReadEdfDataToDouble(QVector<hnnk::DataPoint> &dVecs, QVariant &vv, int ch)
{
    //QString ff;
    //先转成vector<double>
    std::vector<double> vals;
    for(auto it : dVecs){
        vals.push_back(it.yAxis);
        //ff.append(QString::number(it.yAxis) + ",");
    }
    //qDebug() <<" edf val " << ff;
    hnnk::BasicParameter param = vv.value<hnnk::BasicParameter>();
    for(int ch = 0; ch < param.m_channals; ++ch){
        //ui->customPlot->removeGraph(ch);
    }

    //int chs = param.m_channals > 5 ? 5 : param.m_channals;

    qDebug() << " param.m_samRate " << ch;
    realtimeDataSlotChanEdf(vals, param.m_samRate, ch, param.m_channals - 1, param.m_blockFre);
    vals.clear();
}

void WaveFormWidget::plotEvent(double key, int evtNumber)   //绘制标
{
    QCPItemText *textLabel = new QCPItemText(ui->customPlot);
    textLabel->position->setType(QCPItemPosition::ptPlotCoords);        //ptAxisRectRatio决定了下面setCoords用比例的方式设置坐标
    textLabel->position->setCoords(key, 10);        // place position at center/top of axis rect
    textLabel->setText(QString::number(evtNumber));
    textLabel->setFont(QFont(font().family(), 16));         // make font a bit larger
    textLabel->setColor(Qt::red);
}


// void WaveFormWidget::dealConnectSuccess()
// {
//     //ui->statusBar->showMessage(QString("已连接"));
//     m_pchooseWindow->close();
// }

/**
 * @brief WaveFormWidget::onDealManualMarking  手动打标
 * @param evtNum 打标号
 */
void WaveFormWidget::onDealManualMarking(int evtNum)
{
    ///如果此时在自动打标，则停止自动打标的定时器
    m_markVal = evtNum; 	///设置打标号
    qDebug()<<"手动打标";
    QVariant data(m_markVal);
    emit emitEventDispatcher(DAO_MARK, data);
}


void WaveFormWidget::onReciveEegData(QVector<EegDataChan> eegVec)
{
    qDebug() << "onReciveEgeDate--------------------------------";
    std::vector<double> eegData;
    for(auto &it : eegVec){
        eegData.insert(eegData.end(), it.data.begin(), it.data.end());
        if(it.eventFirst)
            plotEvent(m_lastPointKey, it.eventFirst);
    }
    realtimeDataSlotChan(eegData, parameter.m_samRate, parameter.m_channals, parameter.m_blockFre);
}


void WaveFormWidget::onDeviceChannelAndSampRate(int channels, int srate)
{
    m_chAndRateInfo->setText(QString("chs :%1 rate : %2").arg(QString::number(channels), QString::number(srate)));

    m_localConf.m_block = parameter.m_blockFre;
    m_localConf.m_channels = parameter.m_channals;
    m_localConf.m_samp = parameter.m_samRate;
    if(m_localConf.m_channels > 0){
        emit emitSetEpochInfo(m_localConf.m_channels, 1, 1000);//一、二代头环，最后的参数是给陀螺仪通道用的
        qDebug()<<" onDeviceChannelAndSampRate setEpochInfo";
    }
}


void WaveFormWidget::onPopMsgBox(int type, QString msg)
{
    QString title;
    /*switch(type){
    case SPO_SELECTINFO:

        break;
    case SPO_LAUCH:{
        title = "请求脑电数据";
        QMessageBox msgBox(QMessageBox::Critical, title, msg, QMessageBox::Ok, this);
        break;
    }
    default:{

        break;
    }

    }*/

}

void WaveFormWidget::onAddtionData(QVector<GYRODATA> gyroDatas,QVector<unsigned char>channoff, double battery)
{
    QString gyroStr = QString("陀螺仪数据:r:%1,y:%2,p:%3").
                      arg(QString::number((double)gyroDatas[0].x_angle,'f',2), -6, '0').
                      arg(QString::number((double)gyroDatas[0].y_angle,'f',2), -6, '0').
                      arg(QString::number((double)gyroDatas[0].z_angle,'f',2), -6, '0');

    m_pdataGyro->setText(gyroStr);
    //m_deviceVoltage->setText(QString("电压: %1 V").arg(QString::number(battery,'g', 3), -4,'0'));
}

void WaveFormWidget::onUpdateSelfCheckInfo(AmpTestInfo ampInfo)
{
    ///TODO 更新通道号及采样频率信息显示在界面
    qDebug()<<" amp status "<<ampInfo.m_ampStatus;
    qDebug()<<" battary status "<<ampInfo.m_battaryStatus;
    qDebug()<<" gyr status "<<ampInfo.m_gyrStatus;
    qDebug()<<" blue status "<<ampInfo.m_blueStatus;
}

//修改蓝牙名称
void WaveFormWidget::onModifyDeviceName(QString name)
{
    m_localConf.m_deviceName = name;
    QByteArray dname = m_localConf.m_deviceName.toLocal8Bit();
    QVariant deviceName(dname);

    emit emitEventDispatcher(DataAppOperator::DAO_MODIFYBLENAME, deviceName);
}

void WaveFormWidget::onTestEpoch()
{
    // hnnk::Epoch *epochObj = m_dataSystemSDK->getOneEpoch(true);
    // if(nullptr != epochObj){
    //     qDebug()<<" epoch event val "<<epochObj->event;
    //     for(int index = 0; index < epochObj->pointindex; index++){
    //         qDebug()<<" epoch data val "<<epochObj->data[index];
    //     }
    //     delete epochObj;
    // }
}

void WaveFormWidget::onConnectUpdate(CONNECTUPDATE con)
{
    m_connectSuccessful = con;
    if(CU_UNCON == con){
        //ui->connectstate->setText("设备已断开连接");
    }
    qDebug()<<"current connected state "<<con;
}

void WaveFormWidget::onChooseBlueEvent(hnnk::DataAppOperator type, QString name)
{
   //  qDebug()<<" WaveFormWidget::onChooseBlueEvent "<<name;
   //  QVariant vv(name);

   // m_dataSystemSDK->eventDispatcher(type, vv);
   //  if(type==DAO_CONNET){
   //    m_dataSystemSDK->eventDispatcher(DataAppOperator::DAO_READEEGDATA, QVariant(QVariant::Int));
   //    qDebug() << "WaveFormWidget:m_dataSystemSDK 已连接设备：" << vv;
   //  }


    //dealConnectSuccess();
}

void WaveFormWidget::clearScreen()
{
    //清除掉原来的
    /*int plottableCount = ui->customPlot->plottableCount();
    if (plottableCount != 0)
        ui->customPlot->clearPlottables();
    ui->customPlot->clearItems();

    ui->action_Start_Acquisition->setIcon(QIcon(":/image/images/icons8-pause-button-64.png"));
    ui->action_Start_Acquisition->setEnabled(false);
    ui->action_Stop_Acquisition->setEnabled(true);
    ui->horizontalScrollBar->setEnabled(false);  //只有读波形时滑动条才使用

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica", 9));
    ui->customPlot->xAxis->setRange(0, 8, Qt::AlignLeft);
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);

    ui->customPlot->axisRect()->setRangeZoom( Qt::Vertical);
    ui->customPlot->axisRect()->setRangeDrag( Qt::Vertical);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//
    //重新设置时间轴显示相关的变量
    m_lastPointKey = 0;
    m_rangeRight = 8;
    m_timeCur = 0;*/
    //清除掉原来的
    int plottableCount = ui->customPlot->plottableCount();
    if (plottableCount != 0)
        ui->customPlot->clearPlottables();
    ui->customPlot->clearItems();

    ui->btn_start_acquisition->setIcon(QIcon(":/image/images/icons8-pause-button-64.png"));
    ui->btn_start_acquisition->setEnabled(false);
    ui->btn_stop_acquisition->setEnabled(true);
    ui->horizontalScrollBar->setEnabled(false);  //只有读波形时滑动条才使用*/

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica", 9));
    ui->customPlot->xAxis->setRange(0, 8, Qt::AlignLeft);
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
    //ui->customPlot->addGraph();
    /*QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(179, 212, 101));
    ui->customPlot->graph(0)->setName("EEG 1");
    ui->customPlot->graph(0)->setPen(pen);

    ui->customPlot->axisRect()->setRangeZoom( Qt::Vertical);
    ui->customPlot->axisRect()->setRangeDrag( Qt::Vertical);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);*/

    //重新设置时间轴显示相关的变量
    m_lastPointKey = 0;
    m_rangeRight = 8;
    m_timeCur = 0;
}

void WaveFormWidget::on_btn_trapFilter_clicked()
{
    if(!ui->btn_trapFilter->text().compare("滤波器已开")){
        ui->btn_trapFilter->setText("滤波器已关");
    }else{
        ui->btn_trapFilter->setText("滤波器已开");

        if(parameter.m_channals <= 0){
            //限波功能不能正确完成
            QMessageBox ms;
            ms.setText("限波功能不能正确完成, 通道号为0");
            ms.show();
        }else{
            QVariant vv;
            emit emitEventDispatcher(DAO_FILTER, vv);
        }

    }
}


void WaveFormWidget::on_btn_open_clicked()
{
    setupPlotEdfChan(ui->customPlot);
}


/**
 * 触发弹出打标窗口
 * @brief WaveFormWidget::on_btn_add_event_clicked
 */
void WaveFormWidget::on_btn_add_event_clicked()
{
    m_pMarkingTester->show();  //ps显示打标测试窗口
}

/**
 * 开始读取脑电数据
 * @brief WaveFormWidget::on_btn_start_acquisition_clicked
 */
void WaveFormWidget::on_btn_start_acquisition_clicked()
{
    if(m_connectSuccessful){
        clearScreen();
        emit emitEventDispatcher(DataAppOperator::DAO_READEEGDATA, QVariant(QVariant::Int));
    }else{
        QMessageBox box;
        box.setText("bluetooth not connected");
        box.setDefaultButton(QMessageBox::Cancel);
        QTimer::singleShot(2000, &box, SLOT(accept()));
        box.exec();
    }
}

/**
 * 记录edf文件
 * @brief WaveFormWidget::on_btn_start_record_clicked
 */
void WaveFormWidget::on_btn_start_record_clicked()
{
    m_edfWritePath = QFileDialog::getSaveFileName(
        this,
        "另存为",
        "../",
        "*.bdf");

    qDebug()<<"WaveWindow::on_action_Record_triggered path="<< m_edfWritePath;
    if(m_edfWritePath.isEmpty() == true){
        qDebug() << "is empty";
        return;
    }
    m_state = STATE_RECORD;
    QVariant dataAdhesive(m_edfWritePath);

    emit emitEventDispatcher(DataAppOperator::DAO_SAVEEDF, dataAdhesive);
}

/**
 * 停止脑电数据
 * @brief WaveFormWidget::on_btn_stop_acquisition_clicked
 */
void WaveFormWidget::on_btn_stop_acquisition_clicked()
{
    if(m_state == STATE_RECORD){
        //显示保存的edf路径
        ///ui->statusBar->clearMessage();
        //ui->statusBar->showMessage(QString::fromLocal8Bit(u8"已保存至") + QString(m_edfWritePath));  //显示保存成功与否
        //ui->statusBar->showMessage(u8"已保存至" + QString(m_edfWritePath));  //显示保存成功与否
        m_state = STATE_NOT_RECORD;     //回到默认的无记录状态
    }

    ui->btn_start_record->setEnabled(true);
    ui->btn_stop_acquisition->setEnabled(false);
    ui->btn_start_acquisition->setEnabled(true);
    ui->btn_start_acquisition->setIcon(QIcon(":/image/images/icons8-play-64.png"));
    emit emitEventDispatcher(DataAppOperator::DAO_ENDREADEEGDATA, QVariant(QVariant::Int));
    emit emitEventDispatcher(DataAppOperator::DAO_ENDSAVE, QVariant(QVariant::Int));
}

void WaveFormWidget::onReciveParameter(BasicParameter parameter)
{
    this->parameter = parameter;
}
