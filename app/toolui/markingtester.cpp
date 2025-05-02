#include "markingtester.h"
#include "ui_markingtester.h"

#include <QDebug>

#pragma execution_character_set("utf-8")

MarkingTester::MarkingTester(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkingTester)
{
    ui->setupUi(this);
    setWindowTitle("测试打标");
    ui->comboMarkNum->addItem("180");
    ui->comboMarkNum->addItem("80");
    ui->comboMarkNum->addItem("280");
}

MarkingTester::~MarkingTester()
{
    delete ui;
}

// 点击手动打标按钮
void MarkingTester::on_manualMarkBtn_clicked()
{
    m_markflag = 1;
    int markNum = ui->comboMarkNum->currentText().toInt();
    emit emitManualMarking(markNum);
}
