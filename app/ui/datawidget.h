#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QBarSet>
#include <QtCharts>
#include "databasemanager.h"
#include "datadetail.h"
// 列编号
#define     COL_ID       0
#define     COL_ACCOUNT      1
#define     COL_START_TIME    2
#define     COL_END_TIME    3
#define     COL_AVERAGE    4

QT_BEGIN_NAMESPACE
namespace Ui { class DataWidget; }
QT_END_NAMESPACE

class DataWidget : public QMainWindow
{
    Q_OBJECT

public:
    DataWidget(QWidget *parent = nullptr);
    ~DataWidget();

    void removeAllAxis(QChart *chart);
    void countData();
    void drawBarChartForWeek(const QDate &date, bool isVertical = true);
    void loadDataFromDatabase();
private:
    Ui::DataWidget *ui;
    QStandardItemModel *dataModel;
    QList<HNNKData> dataList;
    DataDetail *tableWidget;

    void generateRandomData();
    void iniBarChart();
    void drawBarChart();
signals:
    void emitUpdateHnnkData();
public slots:
    void onHnnkData(QList<HNNKData>);

private slots:
    void on_toolBtn_GenData_clicked();
    void do_barHovered(bool status, int index, QBarSet *barset);
    void do_barClicked(int index, QBarSet *barset);
    void do_pieHovered(QPieSlice *slice, bool state);
    void on_btnBuildBarChart_clicked();
    void on_pushButton_clicked();
    void on_dateEdit_dateChanged(const QDate &date);
    void on_btn_showDetail_clicked();
};

#endif // DATAWIDGET_H
