#include "datawidget.h"
#include "qvalueaxis.h"
#include "ui_datawidget.h"

#include <QDateTime>
#include <QRandomGenerator>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include "qcustomcalendarwidget.h"

DataWidget::DataWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataWidget)
{
    ui->setupUi(this);


    tableWidget = new DataDetail();

    //初始化
    iniBarChart();

    //获取数据库数据
    loadDataFromDatabase();


    ui->dateEdit->setDate(QDate::currentDate());
    QCustomCalendarWidget* calendarWidget = new QCustomCalendarWidget(this);
    ui->dateEdit->setCalendarPopup(true);  // 日历弹出
    ui->dateEdit->setCalendarWidget(calendarWidget);
    ui->dateEdit->setMinimumDate(QDate::currentDate().addDays(0));  // 0天
    ui->dateEdit->setMaximumDate(QDate::currentDate().addDays(365));  // +365天
    ui->dateEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->dateEdit->setFixedSize(150, 26);
    ui->dateEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    calendarWidget->disconnect(SIGNAL(selectionChanged()));
    calendarWidget->disconnect(SIGNAL(clicked(QDate)));

    connect(calendarWidget, &QCustomCalendarWidget::signalSetCalendarTime, [this](const QDate& data){
        ui->dateEdit->setDate(data);
    });

    emit emitUpdateHnnkData();
}


DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::countData()
{ //数据统计
    QTreeWidgetItem *item;  //节点
    for(int i=COL_AVERAGE -1;i<=COL_AVERAGE -1;i++)
    {
        int cnt60=0;
        int cnt60to80=0;
        int cnt80=0;
        for(int j=0;j<dataModel->rowCount();j++)
        {
            int val=dataModel->item(j,i)->text().toDouble();
            qDebug() << val;
            if (val<60)
                cnt60++;
            else if (val < 80)
                cnt60to80++;
            else
                cnt80++;
        }
        item=ui->treeWidget->topLevelItem(0); //<60
        item->setText(1,QString::number(cnt60));
        item->setTextAlignment(i,Qt::AlignHCenter);

        item=ui->treeWidget->topLevelItem(1); //60-80
        item->setText(1,QString::number(cnt60to80));
        item->setTextAlignment(i,Qt::AlignHCenter);

        item=ui->treeWidget->topLevelItem(2); //>80
        item->setText(1,QString::number(cnt80));
        item->setTextAlignment(i,Qt::AlignHCenter);

    }
}

void DataWidget::iniBarChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Average Attention for Selected Week");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

}

void DataWidget::onHnnkData(QList<HNNKData> data)
{
    this->dataList = data;

    //用来加载文字数据
    loadDataFromDatabase();
    //用来加载图数据
    drawBarChartForWeek(QDate::currentDate(),true);
}

void DataWidget::onDetectStart(bool flag)
{
    this->flagDetect = !flag;

    if (!flag) {
        // 说明开启检测成功
        ui->btn_detect->setText("停止检测");
    }
}

/**
 * 加载数据库数据
 * @brief DataWidget::loadDataFromDatabase
 */
void DataWidget::loadDataFromDatabase()
{

    // 创建新的 QStandardItemModel，用于存储所有列
    dataModel = new QStandardItemModel(this);
    dataModel->setColumnCount(7);
    dataModel->setHorizontalHeaderLabels({
        "Account", "Start Time", "End Time",
        "Average Attention", "Min Attention", "Max Attention", "Median Attention"
    });

    for (const HNNKData &data : dataList) {
        QList<QStandardItem*> items;
        items << new QStandardItem(data.account);
        items << new QStandardItem(data.startTime.toString("yyyy-MM-dd HH:mm:ss"));
        items << new QStandardItem(data.endTime.toString("yyyy-MM-dd HH:mm:ss"));
        items << new QStandardItem(QString::number(data.avgValue));   // 平均值
        items << new QStandardItem(QString::number(data.minValue));
        items << new QStandardItem(QString::number(data.maxValue));
        items << new QStandardItem(QString::number(data.medValue));   // 中值

        for (QStandardItem *item : items)
            item->setTextAlignment(Qt::AlignCenter);
        qDebug() <<"items:" <<items;
        dataModel->appendRow(items);
    }
    tableWidget->setModel(dataModel);

    countData(); // 统计数据
}


void DataWidget::drawBarChartForWeek(const QDate &date, bool isVertical)
{
    QChart *chart = ui->chartView->chart();
    chart->removeAllSeries();
    removeAllAxis(chart);

    chart->setTitle(isVertical ? "Barchart 演示" : "Horizontal BarChart 演示");

    QLineSeries *seriesLine = new QLineSeries();
    seriesLine->setName("平均值");
    QPen pen(Qt::red);
    pen.setWidth(2);
    seriesLine->setPen(pen);
    QFont font = seriesLine->pointLabelsFont();
    font.setPointSize(12);
    font.setBold(true);
    seriesLine->setPointLabelsFont(font);
    seriesLine->setPointLabelsVisible(true);
    seriesLine->setPointLabelsFormat(isVertical ? "@yPoint" : "@xPoint");

    // 初始化映射表
    QMap<QDate, QVector<qreal>> attentionDataMap;
    QMap<QDate, qreal> averageSumMap;
    QMap<QDate, int> countMap;


    // 处理数据，筛选指定周的数据
    int targetWeek = date.weekNumber();
    for (const HNNKData &data : dataList) {
        QDate recordDate = data.startTime.date();
        if (recordDate.weekNumber() == targetWeek) {
            attentionDataMap[recordDate] = {data.medValue, data.minValue, data.maxValue};
            averageSumMap[recordDate] += data.avgValue;
            countMap[recordDate] += 1;
        }
    }

    QBarSeries *seriesBar = new QBarSeries();
    seriesBar->setLabelsVisible(true);
    seriesBar->setLabelsFormat("@value");

    QBarSet *minSet = new QBarSet("最小值");
    QBarSet *maxSet = new QBarSet("最大值");
    QBarSet *medianSet = new QBarSet("中值");

    QStringList categories;
    int index = 0;

    for (auto it = attentionDataMap.constBegin(); it != attentionDataMap.constEnd(); ++it, ++index) {
        QDate dateKey = it.key();
        categories << dateKey.toString("yyyy-MM-dd");
        QVector<qreal> values = it.value();

        *minSet << values[1]; // 最小值
        *maxSet << values[2]; // 最大值
        *medianSet << values[0]; // 中值（我们用 medValue 存储的）

        qreal dailyAvg = averageSumMap[dateKey] / countMap[dateKey];
        seriesLine->append(index, dailyAvg);
    }

    seriesBar->append(minSet);
    seriesBar->append(maxSet);
    seriesBar->append(medianSet);

    connect(seriesBar, &QBarSeries::hovered, this, &DataWidget::do_barHovered);
    connect(seriesBar, &QBarSeries::clicked, this, &DataWidget::do_barClicked);

    chart->addSeries(seriesBar);
    chart->addSeries(seriesLine);

    QBarCategoryAxis *axisStud = new QBarCategoryAxis();
    axisStud->append(categories);

    QValueAxis *axisValue = new QValueAxis();
    axisValue->setRange(0, 100);
    axisValue->setTitleText("分数");
    axisValue->setTickCount(6);
    axisValue->setLabelFormat("%.0f");
    axisValue->applyNiceNumbers();

    if (isVertical) {
        chart->addAxis(axisStud, Qt::AlignBottom);
        chart->addAxis(axisValue, Qt::AlignLeft);
    } else {
        chart->addAxis(axisStud, Qt::AlignLeft);
        chart->addAxis(axisValue, Qt::AlignBottom);
    }

    seriesBar->attachAxis(axisStud);
    seriesBar->attachAxis(axisValue);
    seriesLine->attachAxis(axisStud);
    seriesLine->attachAxis(axisValue);

    chart->legend()->setAlignment(Qt::AlignBottom);
}


void DataWidget::removeAllAxis(QChart *chart)
{//删除一个chart的所有坐标轴
    QList<QAbstractAxis *> axisList=chart->axes();  //获取坐标轴列表
    int count=axisList.count();
    for(int i=0; i<count; i++ )
    {
        QAbstractAxis *one=axisList.at(0);
        chart->removeAxis(one);     //从图表中移除坐标轴，
        axisList.removeFirst();     //从列表中移除坐标轴
        delete one;     //删除坐标轴对象，释放内存
    }
}

void DataWidget::on_toolBtn_GenData_clicked()
{
    loadDataFromDatabase();
    drawBarChartForWeek(QDate::currentDate());
}

void DataWidget::on_btnBuildBarChart_clicked()
{
    loadDataFromDatabase();
    drawBarChartForWeek(QDate::currentDate(),true);
}

void DataWidget::do_pieHovered(QPieSlice *slice, bool state)
{
    slice->setExploded(state);
}

void DataWidget::do_barHovered(bool status, int index, QBarSet *barset)
{
    QString str= "hovered barSet="+barset->label();
    if (status)
        str += QString::asprintf(", index=%d, value=%.2f",index, barset->at(index));
    else
        str="";
    // ui->statusbar->showMessage(str);
}

void DataWidget::do_barClicked(int index, QBarSet *barset)
{
    QString str = "clicked barSet=" + barset->label();
    str += QString::asprintf(", index=%d, count=%d", index, barset->count());
    // ui->statusbar->showMessage(str);
}

void DataWidget::on_dateEdit_dateChanged(const QDate &date)
{
    QDate selectedDate = ui->dateEdit->date();
    drawBarChartForWeek(selectedDate);
}


void DataWidget::on_btn_showDetail_clicked()
{
    tableWidget->show();
}

void DataWidget::on_btn_update_clicked()
{
    emit emitUpdateHnnkData();
}

void DataWidget::on_btn_detect_clicked()
{
    if (flagDetect) {
        //checked为true时，标识为开始检测, 所以下次点击为停止检测
        int choice = 0;
        // 调用SDK启动算法检测
        if (ui->btn_user->isChecked()) // 使用用户模型算法
            choice = 1;
        else if (ui->btn_bigmodel->isChecked()) // 使用大数据模型算法
            choice = 2;

        emit emitStartBlinkDetection(choice);
        emit emitShowAttention();

    } else {
        //checked为false时，表示点击时停止检测

        emit emitStopBlinkDetection();
        flagDetect = true;
        ui->btn_detect->setText("开始检测");
    }
}


void DataWidget::on_btn_showDetect_clicked()
{
    emit emitShowAttention();
}

