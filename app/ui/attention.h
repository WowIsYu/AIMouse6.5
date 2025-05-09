#ifndef ATTENTION_H
#define ATTENTION_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QBarSet>
#include <QtCharts>
#include "databasemanager.h"
// 列编号
#define     COL_ID       0
#define     COL_ACCOUNT      1
#define     COL_START_TIME    2
#define     COL_END_TIME    3
#define     COL_AVERAGE    4

QT_BEGIN_NAMESPACE
namespace Ui { class Attention; }
QT_END_NAMESPACE

class Attention : public QMainWindow
{
    Q_OBJECT

public:
    Attention(QWidget *parent = nullptr);
    ~Attention();

    void removeAllAxis(QChart *chart);
    void countData();
    void drawBarChartForWeek(const QDate &date, bool isVertical = true);
    void loadDataFromDatabase();
private:
    Ui::Attention *ui;
    QStandardItemModel *dataModel;
    QList<HNNKData> dataList;

    void generateRandomData();
    void iniBarChart();
    void drawBarChart();
signals:
    void emitUpdateHnnkData();
public slots:
    void onHnnkData(QList<HNNKData>);

private slots:
    void on_toolBtn_GenData_clicked();
    void on_calendarWidget_selectionChanged();
    void do_barHovered(bool status, int index, QBarSet *barset);
    void do_barClicked(int index, QBarSet *barset);
    void do_pieHovered(QPieSlice *slice, bool state);
    void on_btnBuildBarChart_clicked();
    void on_pushButton_clicked();
};

#endif // ATTENTION_H
