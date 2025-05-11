#include "datadetail.h"
#include "ui_datadetail.h"

DataDetail::DataDetail(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataDetail)
{
    ui->setupUi(this);
}

DataDetail::~DataDetail()
{
    delete ui;
}
