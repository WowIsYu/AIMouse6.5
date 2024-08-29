#include "attentionshow.h"
#include "ui_attentionshow.h"

AttentionShow::AttentionShow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttentionShow)
{
    ui->setupUi(this);
    // 获取当前窗口的标志
    Qt::WindowFlags flags = windowFlags();

    // 添加Qt::Tool标志，使窗口表现为一个工具窗口。工具窗口通常没有任务栏图标，并且可能在某些情况下有不同的行为
    flags |= Qt::Tool;

    // 添加Qt::WindowStaysOnTopHint标志，使窗口总是保持在其他窗口之上
    flags |= Qt::WindowStaysOnTopHint;      // 总在最上面的窗口，置前

    // 使用更新后的flags设置窗口的标志
    setWindowFlags(flags);
    hide();
}

AttentionShow::~AttentionShow()
{
    delete ui;
}

void AttentionShow::onReceiveResult(double val)
{
    ui->lcdNumber->display(val * 100);
}
