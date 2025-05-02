#include "rankdialog.h"
#include "ui_rankdialog.h"

#include <QFileDialog>
#include <QMessageBox>


RankDialog::RankDialog(QWidget *parent, QString rankFile)
    : QDialog(parent)
    , ui(new Ui::RankDialog)
{
    ui->setupUi(this);
    this->rankFile = rankFile;

}

RankDialog::~RankDialog()
{
    delete ui;
}

void RankDialog::rankAndShow()
{
    QFile file(rankFile);
    if (!file.exists())
    {
        QMessageBox::information(this, "提示", "未找到排行榜文件");
        return;
    }
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(this, "提示", "排行榜文件打开失败");
        return;
    }
    QString playerName;
    int playerScore;
    QList<QString> nameList;
    QList<int> scoreList;
    QTextStream stream(&file);

    while(!stream.atEnd())                  //读出所有玩家的数据
    {
        stream >> playerName >> playerScore;
        nameList.append(playerName);
        scoreList.append(playerScore);
    }
    file.close();

    for (int i = 0; i < scoreList.size() - 1; i ++)
        for (int j = i + 1; j < scoreList.size(); j++)
            if (scoreList.at(j) > scoreList.at(i))
            {
                scoreList.swapItemsAt(i, j);
                nameList.swapItemsAt(i, j);
            }
    ui->rankList->clear();
    for (int i = 0; i < nameList.size() && i < 5; i++)
    {
        ui->rankList->addItem("第" + QString::number(i + 1) + "名："
                              + nameList.at(i) + "\t"
                              + QString::number(scoreList.at(i)) + "分");
    }
    show();
}
