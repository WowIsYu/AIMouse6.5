#include "attention.h"
#include "qvalueaxis.h"
#include "ui_attention.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QRandomGenerator>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QSqlRecord>

// using namespace QtCharts;

Attention::Attention(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Attention)
{
    ui->setupUi(this);
    //创建数据库
    setupDatabase();
    // 生成随机值
    // generateRandomData();

    //获取数据库数据
    loadDataFromDatabase();

    //初始化
    iniBarChart();

    drawBarChartForWeek(QDate::currentDate(),true);

    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, this, &Attention::on_calendarWidget_selectionChanged);

    // // 表格高度随内容自动扩展
    // ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 表格宽度随内容自动扩展
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


Attention::~Attention()
{
    delete ui;
}

void Attention::setupDatabase()
{
    QSqlQuery query;
    // Create users table
    QString createUsersTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            account TEXT,
            password TEXT
        )
    )";

    if (!query.exec(createUsersTable)) {
        qDebug() << "Error: failed to create users table -" << query.lastError();
    }

    // Create attention_records table
    QString createAttentionTable = R"(
        CREATE TABLE IF NOT EXISTS attention_records (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            account TEXT,
            start_time TEXT,
            end_time TEXT,
            average_attention REAL,
            min_attention REAL,
            max_attention REAL,
            median_attention REAL
        )
    )";

    if (!query.exec(createAttentionTable)) {
        qDebug() << "Error: failed to create attention_records table -" << query.lastError();
    }
}

void Attention::generateRandomData()
{
    QSqlQuery query;
    query.exec("DELETE FROM attention_records"); // Clear old data

    for (int i = 0; i < 10; ++i) { // Simulate 10 records
        QString account = QString::asprintf("user%02d", i + 1);
        QDateTime startTime = QDateTime::currentDateTime().addDays(-QRandomGenerator::global()->bounded(0, 7));
        QDateTime endTime = startTime.addSecs(QRandomGenerator::global()->bounded(3600, 7200)); // 1-2 hours later

        QVector<qreal> attentionValues;
        for (int j = 0; j < 10; ++j) { // Simulate 10 attention values per session
            attentionValues.append(QRandomGenerator::global()->bounded(0, 100));
        }

        std::sort(attentionValues.begin(), attentionValues.end());

        qreal averageAttention = std::accumulate(attentionValues.begin(), attentionValues.end(), 0.0) / attentionValues.size();
        qreal minAttention = attentionValues.first();
        qreal maxAttention = attentionValues.last();
        qreal medianAttention = attentionValues[attentionValues.size() / 2];

        query.prepare("INSERT INTO attention_records (account, start_time, end_time, average_attention, min_attention, max_attention, median_attention) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(account);
        query.addBindValue(startTime.toString(Qt::ISODate));
        query.addBindValue(endTime.toString(Qt::ISODate));
        query.addBindValue(averageAttention);
        query.addBindValue(minAttention);
        query.addBindValue(maxAttention);
        query.addBindValue(medianAttention);

        if (!query.exec()) {
            qDebug() << "Error: failed to insert random data -" << query.lastError();
        }
    }
}

void Attention::countData()
{ //数据统计
    QTreeWidgetItem *item;  //节点
    for(int i=COL_AVERAGE -1;i<=COL_AVERAGE -1;i++)
    {
        int cnt50=0;
        int cnt60=0;
        int cnt70=0;
        int cnt80=0;
        int cnt90=0;
        // qDebug() << dataModel->item(1,1)->text();
        // qDebug() << dataModel->item(1,2)->text();
        // qDebug() << dataModel->item(1,3)->text();
        // qDebug() << dataModel->item(1,4)->text();
        // qDebug() << dataModel->item(1,5)->text();
        // qDebug() << dataModel->item(1,0)->text();

        // qDebug() << dataModel->item(0,1)->text();
        // qDebug() << dataModel->item(0,2)->text();
        // qDebug() << dataModel->item(0,3)->text();
        // qDebug() << dataModel->item(0,4)->text();
        // qDebug() << dataModel->item(0,5)->text();
        // qDebug() << dataModel->item(0,0)->text();
        for(int j=0;j<dataModel->rowCount();j++)
        {
            int val=dataModel->item(j,i)->text().toDouble();
            qDebug() << val;
            if (val<60)
                cnt50++;
            else if ((val>=60) && (val<70))
                cnt60++;
            else if ((val>=70) && (val<80))
                cnt70++;
            else if ((val>=80) && (val<90))
                cnt80++;
            else
                cnt90++;
        }
        item=ui->treeWidget->topLevelItem(0); //<60
        item->setText(1,QString::number(cnt50));
        item->setTextAlignment(i,Qt::AlignHCenter);

        item=ui->treeWidget->topLevelItem(1); //60
        item->setText(1,QString::number(cnt60));
        item->setTextAlignment(i,Qt::AlignHCenter);

        item=ui->treeWidget->topLevelItem(2); //70
        item->setText(1,QString::number(cnt70));
        item->setTextAlignment(i,Qt::AlignHCenter);

        item=ui->treeWidget->topLevelItem(3); //80
        item->setText(1,QString::number(cnt80));
        item->setTextAlignment(i,Qt::AlignHCenter);

        item=ui->treeWidget->topLevelItem(4); //90
        item->setText(1,QString::number(cnt90));
        item->setTextAlignment(i,Qt::AlignHCenter);
    }
}

void Attention::iniBarChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Average Attention for Selected Week");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}

void Attention::loadDataFromDatabase()
{
    // 创建新的 QStandardItemModel，用于存储所有列
    dataModel = new QStandardItemModel(this);
    dataModel->setColumnCount(7); // attention_records 有 7 列
    dataModel->setHorizontalHeaderLabels({"Account", "Start Time", "End Time", "Average Attention", "Min Attention", "Max Attention", "Median Attention"}); // 更新列标题

    // 查询全部列
    QSqlQuery query("SELECT account, start_time, end_time, average_attention, min_attention, max_attention, median_attention FROM attention_records");

    while (query.next()) {
        QList<QStandardItem*> items;
        // 读取所有列的数据
        for (int i = 0; i < 7; ++i) { // 这里是 7，因为我们有 7 列
            QStandardItem *item = new QStandardItem(query.value(i).toString());
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            items.append(item);
        }
        dataModel->appendRow(items); // 添加一行数据
    }

    ui->tableView->setModel(dataModel); // 设置模型
    countData(); // 统计数据
}

void Attention::drawBarChartForWeek(const QDate &date, bool isVertical)
{
    QChart *chart = ui->chartView->chart();

    if (isVertical)
        chart->setTitle("Barchart 演示");
    else
        chart->setTitle("Horizontal BarChart 演示");

    chart->removeAllSeries(); // 移除所有序列
    removeAllAxis(chart);

    // 创建一个QLineSeries序列用于显示平均值
    QLineSeries *seriesLine = new QLineSeries();
    seriesLine->setName("平均值");
    QPen pen(Qt::red);
    pen.setWidth(2);
    seriesLine->setPen(pen);
    QFont font = seriesLine->pointLabelsFont();
    font.setPointSize(12);
    font.setBold(true);
    seriesLine->setPointLabelsFont(font);
    seriesLine->setPointLabelsVisible(true); // 显示数据点的数值
    if (isVertical)
        seriesLine->setPointLabelsFormat("@yPoint");
    else
        seriesLine->setPointLabelsFormat("@xPoint");

    // 使用QMap来记录每一天的数据
    QMap<QDate, QVector<qreal>> attentionDataMap;
    QMap<QDate, qreal> averageSumMap;
    QMap<QDate, int> countMap; // 用于记录每天的记录数

    // 查询数据库并填充数据
    QSqlQuery query("SELECT start_time, average_attention, min_attention, max_attention, median_attention FROM attention_records");
    while (query.next()) {
        QDateTime startTime = QDateTime::fromString(query.value(0).toString(), Qt::ISODate);
        QDate recordDate = startTime.date();
        if (recordDate.weekNumber() == date.weekNumber()) {
            attentionDataMap[recordDate].append(query.value(1).toDouble()); // 添加平均值
            attentionDataMap[recordDate].append(query.value(2).toDouble()); // 添加最小值
            attentionDataMap[recordDate].append(query.value(3).toDouble()); // 添加最大值
            attentionDataMap[recordDate].append(query.value(4).toDouble()); // 添加中值

            // 计算每天的累加平均值和记录数
            averageSumMap[recordDate] += query.value(1).toDouble();
            countMap[recordDate] += 1; // 增加当天的记录数
        }
    }

    QBarSeries *seriesBar = new QBarSeries();
    seriesBar->setLabelsVisible(true); // 显示棒柱的标签
    seriesBar->setLabelsFormat("@value"); // 棒柱标签格式

    QBarSet *minSet = new QBarSet("最小值");
    QBarSet *maxSet = new QBarSet("最大值");
    QBarSet *medianSet = new QBarSet("中值");

    QStringList categories;

    for (auto it = attentionDataMap.constBegin(); it != attentionDataMap.constEnd(); ++it) {
        categories << it.key().toString("yyyy-MM-dd");
        QVector<qreal> values = it.value();
        qreal minValue = values[1]; // 最小值
        qreal maxValue = values[2]; // 最大值
        qreal medianValue = values[3]; // 中值

        *minSet << minValue;
        *maxSet << maxValue;
        *medianSet << medianValue;

        // 计算每日的平均值
        qreal dailyAverage = averageSumMap[it.key()] / countMap[it.key()]; // 使用当天的记录数
        seriesLine->append(categories.size() - 1, dailyAverage);
    }

    seriesBar->append(minSet);
    seriesBar->append(maxSet);
    seriesBar->append(medianSet);

    connect(seriesBar, &QBarSeries::hovered, this, &Attention::do_barHovered);
    connect(seriesBar, &QBarSeries::clicked, this, &Attention::do_barClicked);

    chart->addSeries(seriesBar); // 添加柱状图序列
    chart->addSeries(seriesLine); // 添加折线图序列

    QBarCategoryAxis *axisStud = new QBarCategoryAxis(); // 用于柱状图的坐标轴
    axisStud->append(categories); // 添加横坐标文字列表

    QValueAxis *axisValue = new QValueAxis();
    axisValue->setRange(0, 100); // 根据数据调整范围
    axisValue->setTitleText("分数");
    axisValue->setTickCount(6);
    axisValue->setLabelFormat("%.0f"); // 标签格式
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

    chart->legend()->setAlignment(Qt::AlignBottom); // 图例显示在下方
}

void Attention::removeAllAxis(QChart *chart)
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

void Attention::on_calendarWidget_selectionChanged()
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    drawBarChartForWeek(selectedDate);
}

void Attention::on_toolBtn_GenData_clicked()
{
    generateRandomData();
    loadDataFromDatabase();
    drawBarChartForWeek(QDate::currentDate());
}

void Attention::on_btnBuildBarChart_clicked()
{
    loadDataFromDatabase();
    drawBarChartForWeek(QDate::currentDate(),true);
}

void Attention::do_pieHovered(QPieSlice *slice, bool state)
{
    slice->setExploded(state);
}

void Attention::do_barHovered(bool status, int index, QBarSet *barset)
{
    QString str= "hovered barSet="+barset->label();
    if (status)
        str += QString::asprintf(", index=%d, value=%.2f",index, barset->at(index));
    else
        str="";
    // ui->statusbar->showMessage(str);
}

void Attention::do_barClicked(int index, QBarSet *barset)
{
    QString str = "clicked barSet=" + barset->label();
    str += QString::asprintf(", index=%d, count=%d", index, barset->count());
    // ui->statusbar->showMessage(str);
}

void Attention::insertUser(const QString &account, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (account, password) VALUES (?, ?)");
    query.addBindValue(account);
    query.addBindValue(password);

    if (!query.exec()) {
        qDebug() << "Error: failed to insert user -" << query.lastError();
    }
}

void Attention::insertAttentionRecord(const QString &account, const QDateTime &startTime, const QDateTime &endTime,
                                      qreal averageAttention, qreal minAttention, qreal maxAttention, qreal medianAttention)
{
    QSqlQuery query;
    query.prepare("INSERT INTO attention_records (account, start_time, end_time, average_attention, min_attention, max_attention, median_attention) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(account);
    query.addBindValue(startTime.toString(Qt::ISODate));
    query.addBindValue(endTime.toString(Qt::ISODate));
    query.addBindValue(averageAttention);
    query.addBindValue(minAttention);
    query.addBindValue(maxAttention);
    query.addBindValue(medianAttention);

    if (!query.exec()) {
        qDebug() << "Error: failed to insert attention record -" << query.lastError();
    }
}
