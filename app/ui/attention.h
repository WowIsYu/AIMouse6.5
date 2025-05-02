#ifndef ATTENTION_H
#define ATTENTION_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QBarSet>
#include <QSqlTableModel>
#include <QtCharts>

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
    void insertAttentionRecord(const QString &account, const QDateTime &startTime, const QDateTime &endTime,
                                          qreal averageAttention, qreal minAttention, qreal maxAttention, qreal medianAttention);
    void insertUser(const QString &account, const QString &password);
    void loadDataFromDatabase();
private:
    Ui::Attention *ui;
    QSqlDatabase db;
    QStandardItemModel *dataModel;
    QSqlTableModel *sqlModel;

    void setupDatabase();
    void generateRandomData();
    void iniBarChart();
    void drawBarChart();

private slots:
    void on_toolBtn_GenData_clicked();
    void on_calendarWidget_selectionChanged();
    void do_barHovered(bool status, int index, QBarSet *barset);
    void do_barClicked(int index, QBarSet *barset);
    void do_pieHovered(QPieSlice *slice, bool state);
    void on_btnBuildBarChart_clicked();
};

#endif // ATTENTION_H
