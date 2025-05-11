#include "datadetail.h"
#include "ui_datadetail.h"

DataDetail::DataDetail(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataDetail)
{
    ui->setupUi(this);

    // 表格高度随内容自动扩展
    // ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 表格宽度随内容自动扩展
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


}

DataDetail::~DataDetail()
{
    delete ui;
}

void DataDetail::setModel(QAbstractItemModel *model)
{
    ui->tableView->setModel(model);
}
